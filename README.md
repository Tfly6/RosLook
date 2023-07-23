# RosLook

*RosLook* 是一个基于 *QT C++* 的 gui 程序，用于调试 ros 程序。虽然 ros 官方已经提供了 `rqt` ，但是谁不想做一个属于自己的小工具呢😏 

## 简介
*RosLook* 是通过使用 QT 自带的 *QProcess* 库来实现它的功能，其根本就是用 *QProcess* 来启动一些 ros 命令，大家可以查看 `mycommand.cpp` 文件，获取更多详细信息。

**目前实现的命令**

|     命令      | 描述                                           |
| :-----------: | ---------------------------------------------- |
| rostopic list | 列出所有现在正在通信的通信话题名称             |
| rostopic info | 查看通过指定topic话题相互通信的双方的信息      |
| rostopic echo | 显示发布到指定话题的消息  （目前不支持自定义） |
| rostopic pub  | 使用指定的话题名称发布消息  （可自定义命令）   |
| rosnode  list | 列出正在运行中的所有节点  |
| rosnode  info | 检查指定节点的信息  |
| rosnode  ping | 与指定的节点进行连接测试  |
| rosnode  kill | 终止指定节点的运行  |



## 使用方法

[RosLook —— 基于QT的ROS调试小工具](https://blog.csdn.net/weixin_55944949/article/details/131480750?spm=1001.2014.3001.5502)

## 安装

目前 *RosLook* 只支持 *Linux、ROS1* 平台，且只在Ubuntu 16.04、Ubuntu 18.04、Ubuntu 20.04 进行测试过，不过这并不代表在其他发行版上运行不了，大家可以在自己使用的发行版上安装、测试，如有什么问题可以在 *issues* 中提问。

### 直接安装

1. 先从 **Releases** 中下载安装包 （目前只发行了 v0.1，也就是只有 rostopic 命令，想要体验最新功能需要自己下载源码编译）
2. 运行

```shell
chmod +x ./roslook-x86_64.AppImage
./roslook-x86_64.AppImage  (or 双击)
```

### 编译安装

1. 下载

```bash
git clone https://github.com/Tfly6/RosLook.git
```

2. qtCreator 编译

我是基于 *qt 5.12.12* 编译的，直接用 *qt creator* 打开 *.pro* 文件，直接编译。

![image-20.png](https://github.com/Tfly6/myImage/blob/main/image-20.png)
