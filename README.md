# eBPF_Study
> 大二操作系统课程大作业

## 实验过程

概括：使用 BCC kprobe 将计时函数挂于指定 syscall 执行前与返回后，通过 BCC Hash Table 实现探针代码与测试程序的通信

- 实验平台 Ubuntu 20.04 LTS 虚拟机（VMWare Workstation）
- 在 src 目录下 `make all`
- 运行测试脚本 `python3 test.py`
- 运行 stdio 负载程序 `./load_stdio`
- 将 stdio 程序所示 PID 序号输入至测试脚本
- 开始负载程序运行
- 结束测试脚本 stdio 测试
- 运行 iouring 负载程序 `./load_iouring`，以下步骤类似

## 实验结论

|               | stdio | iouring |
| ------------- | ----- | ------- |
| Time Cost (s) | 1.606 | 13.301  |

## 笔记 / 参考

- 安装指令 `*sudo apt-get install bpfcc-tools*`

- O_DIRECT 对齐

- [eBPF & bcc实例分析](https://blog.csdn.net/qq_34258344/article/details/104531060)

- [宋宝华：用eBPF/bcc分析系统性能的一个简单案例](https://cloud.tencent.com/developer/article/1560609)

- [bcc Reference Guide](https://github.com/iovisor/bcc/blob/master/docs/reference_guide.md) (官方 Repo 文档)

- [一篇文章带你读懂 io_uring 的接口与实现](https://zhuanlan.zhihu.com/p/380726590)

- [Linux syscall 列表](https://man7.org/linux/man-pages/man2/syscalls.2.html)

- [How to make a system call in C](https://jameshfisher.com/2018/02/19/how-to-syscall-in-c/)

- [Linux Extended BPF (eBPF) Tracing Tools](https://www.brendangregg.com/ebpf.html#bccprogramming)

- [bcc python table 源代码](https://github.com/iovisor/bcc/blob/master/src/python/bcc/table.py)

- ```shell
  # 配置 liburing 库
  $ git clone https://github.com/axboe/liburing.git
  $ cd liburing && make
  $ sudo cp src/liburing.so.2.2 /usr/lib/aarch64-linux-gnu/liburing.so
  $ sudo cp src/liburing.so.2.2 /usr/lib/aarch64-linux-gnu/liburing.so.2
  # 如本 Repo，参考 Makefile 内容将 include 文件夹移至 make 相对路径
  ```

- 感谢 RainyMemory、YGX 等人的讨论与帮助

