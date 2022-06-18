from bcc import BPF

b = BPF(src_file = "kprobe.c")
b.attach_kprobe(event = "read", fn_name="read_in");
b.attach_kretprobe(event = "read", fn_name="read_out");

input('')

b["dist"].print_linear_hist("usecs")