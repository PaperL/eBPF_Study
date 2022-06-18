from bcc import BPF
from ctypes import *

b = BPF(src_file = "kprobe.c")


# info = b.get_table("info")
# start[c_uint(0)] = c_ulonglong(int(input('Input PID:')))
# print(type(b['start']))

start = b['start']
pid = int(input('Input PID:'))
start[c_uint64(0)] = c_uint64(pid)

b.attach_kprobe(event = b.get_syscall_fnname("read"), fn_name="stdio_in");
b.attach_kretprobe(event = b.get_syscall_fnname("read"), fn_name="stdio_out");

b.attach_kprobe(event = b.get_syscall_fnname("write"), fn_name="stdio_in");
b.attach_kretprobe(event = b.get_syscall_fnname("write"), fn_name="stdio_out");

input('Press Any Key to Stop...')

# b["dist"].print_linear_hist("usecs")
# b.trace_print()

print(b['total'].values())

