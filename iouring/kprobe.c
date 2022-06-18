#include <uapi/linux/ptrace.h>

BPF_HASH(start);
BPF_HASH(total);
// BPF_HISTOGRAM(dist);

int stdio_in(void *ctx) {
    u64 pid, tm;

    pid = bpf_get_current_pid_tgid();
    tm = bpf_ktime_get_ns();
    start.update(&pid, &tm);

    return 0;
}

int stdio_out(void *ctx) {
    u64 pid, *tm, duration;
 
    pid = bpf_get_current_pid_tgid();
    tm = start.lookup(&pid);

    if(tm){
      duration = (bpf_ktime_get_ns() - *tm) / 1000;
      u64 zero = 0;
      u64 *targetPid = start.lookup(&zero);
      
     //   bpf_trace_printk("%d\n",pid);
      
      if(targetPid){
          u32 d = (*targetPid)-pid;
        if (!d){
        
         //     total.update(&pid, &duration);
//          dist.increment(duration / 1000);
//          bpf_trace_printk("hit\n");
          
          u64* totalTime;
          totalTime = total.lookup(&pid);
          if (totalTime)
              duration += *totalTime;
          total.update(&pid, &duration);
          
          start.delete(&pid);
        }
      }
    }
    return 0;
}
