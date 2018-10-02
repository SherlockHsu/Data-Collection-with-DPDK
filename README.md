Version
==============================
2.1

Function
==============================
Collect data from Bee7 by DPDK

DPDK Configuration
==============================

### 硬件要求
64位、多于4逻辑核心CPU

支持dpdk的网卡(http://dpdk.org/doc/nics)

### 软件要求
linux操作系统(推荐centos或ubuntu)，kernel内核版本高于2.6.33

dpdk开发包(http://dpdk.org/download)推荐latest stable

### 安装dpdk开发包
1. 解压缩至$(HOME)/dpdk目录

2. 编译开发包
    > cd ~/dpdk/usertools

    > sudo ./dpdk-setup.sh

    > 13

### 配置运行dpdk程序所需要的软件操作系统环境
1. 配置hugepage

    > sudo vim /boot/grub/grub.cfg

    > 在148行handoff后添加default_hugepagesz=1G hugepagesz=1G hugepages=4

    > reboot

2. 启用DPDK用户空间I/O的模块(重启后重新配置)

    > sudo modprobe uio_pci_generic

3. 为网卡分配DPDK驱动(重启后重新配置)

    > sudo ~/dpdk/usertools/dpdk-devbind.py -b uio_pci_generic 0000:07:00.0

    > sudo ~/dpdk/usertools/dpdk-devbind.py -b uio_pci_generic 0000:07:00.1

Build and Execution Instructions
==============================

### Build:
> make

### Execution:
> sudo ./build/main

### Clean:
> make clean