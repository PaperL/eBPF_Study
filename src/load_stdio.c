#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

#define TEST_TIME 1000000
#define TEST_BLOCK_SIZE 128

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
//    while(1) {
        lseek(fd, 0, SEEK_SET);
        write(fd, buffer, BUFFER_SIZE);
        lseek(fd, 0, SEEK_SET);
        read(fd, buffer, BUFFER_SIZE);
    }
    free(buffer);
    close(fd);
}
