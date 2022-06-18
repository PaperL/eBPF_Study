#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "liburing.h"

#define BUFFER_SIZE 4096

#define TEST_TIME 1000000
#define TEST_BLOCK_SIZE 128

#define BATCH_SIZE 16

int main() {
    printf("PID: %d\nEnter to start", getpid());

    getchar();

    const char* fileName = "temp";
    int fd = open(fileName, O_RDWR | O_CREAT | O_DIRECT);
    truncate(fileName, BUFFER_SIZE);
    char* buffer;
    posix_memalign((void**)&buffer, TEST_BLOCK_SIZE, BUFFER_SIZE);

    for (int i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = ((i ^ 12345) >> 2) ^ ((i ^ 98765) << 6);

    for (int i = 0; i < TEST_TIME; i++) {
        struct io_uring ring;
        int ret = io_uring_queue_init(BATCH_SIZE << 1, &ring, 0);
        if (ret != 0) exit(1);
        struct io_uring_sqe *sqe;
        struct io_uring_cqe *finish_sqe[BATCH_SIZE];
        
        for(int j = 0;j < BATCH_SIZE; j++) {
            sqe = io_uring_get_sqe(&ring);
            if(j % 2) io_uring_prep_read(sqe,fd,buffer,BUFFER_SIZE,0);
            else io_uring_prep_write(sqe,fd,buffer,BUFFER_SIZE,0);
        }
        for(int j = 0;j < BATCH_SIZE; j+=io_uring_submit(&ring));
        for(int j = 0;j < BATCH_SIZE; ){
            int finish = io_uring_peek_batch_cqe(&ring, finish_sqe, BATCH_SIZE);
            if(finish) {
                io_uring_cq_advance(&ring, finish);
                j += finish;
            }
        }
    }
    free(buffer);
    close(fd);
    
    return 0;
}
