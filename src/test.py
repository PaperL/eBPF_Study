from bcc import BPF
from ctypes import *

b = BPF(src_file='kprobe.c')


# info = b.get_table('info')
# start[c_uint(0)] = c_ulonglong(int(input('Input PID:')))
# print(type(b['start']))

start = b['start']
total = b['total']

#=================================

print('Begin testing stdio...')
pid = int(input('Input PID:'))
start[c_uint64(0)] = c_uint64(pid)

b.attach_kprobe(event=b.get_syscall_fnname('read'), fn_name='timer_start')
b.attach_kretprobe(event=b.get_syscall_fnname('read'), fn_name='timer_stop')

b.attach_kprobe(event=b.get_syscall_fnname('write'), fn_name='timer_start')
b.attach_kretprobe(event=b.get_syscall_fnname('write'), fn_name='timer_stop')

input('Enter to finish test')
print(total.values())
total.clear()

#=================================

print('Begin testing iouring...')
pid = int(input('Input PID:'))
start.clear()
start[c_uint64(0)] = c_uint64(pid)

b.attach_kprobe(event=b.get_syscall_fnname('io_uring_enter'), fn_name='timer_start')
b.attach_kretprobe(event=b.get_syscall_fnname('io_uring_enter'), fn_name='timer_stop')

b.attach_kprobe(event=b.get_syscall_fnname('io_uring_register'), fn_name='timer_start')
b.attach_kretprobe(
    event=b.get_syscall_fnname('io_uring_register'), fn_name='timer_stop'
)

b.attach_kprobe(event=b.get_syscall_fnname('io_uring_setup'), fn_name='timer_start')
b.attach_kretprobe(event=b.get_syscall_fnname('io_uring_setup'), fn_name='timer_stop')

input('Enter to finish test')
print(b['total'].values())

# b['dist'].print_linear_hist('usecs')
# b.trace_print()
