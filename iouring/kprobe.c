BPF_HASH(start, u32);
BPF_HISTOGRAM(dist);

int read_in(void *ctx) {
    u32 pid;
    u64 tm;

    pid = bpf_get_current_pit_tgid();
    tm = bpf_ktime_get_ns();

    start.update(&pid, &tm);

    return 0;
}

int read_out(void *ctx) {
    u32 pid;
    u64 *tm, duration;

    pid = bpf_get_current_pit_tgid();
    tm = start.lookup(&pid);

    duration = bpf_ktime_get_ns() - *tsp;
    dist.increment(delta / 1000);

    start.delete(&pid);
    return 0;
}