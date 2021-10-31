![](/4.3D Model/holocubic1.jpg)

# HoloCubic--多功能透明显示屏桌面站

**视频介绍：** https://www.bilibili.com/video/BV1VA411p7MD/

## 0. 关于本项目

本项目是从[稚晖君](https://github.com/peng-zhihui/HoloCubic)的基础上编写的，程序写的很乱。以下内容有所删改。

本项目的硬件方案是基于`ESP32PICO-D4`的，乐鑫的一个很实用的MCU芯片，由于采用了SiP封装是的PCBA整板面积能做到一个硬币大小；软件方面主要是基于`lvgl-GUI`库，我移植了ST7789 1.3寸`240x240`分辨率屏幕的显示屏驱动，同时将`MPU6050`作为输入设备通过感应的方式模拟编码器键值来交互。

## 1. 硬件打样说明

**PCB打样的话暂时没发现有啥需要特别注意的。** PCB文件可以直接拿去工厂打样，两层板很便宜，器件BOM的话也都是比较常用的，整板成本在50元以内。

**本项目里只有metal版本的PCB和模型**。我使用了这个版本的模型故删掉了其他版本的模型。

**我觉得RGB没有用就把RGB给去掉了，还把环境光传感器放在了前面，**不过最后我也没用环境光传感器，感觉用途不大，~~我终于知道为什么稚晖君把环境光传感器给去掉了。~~

## 2. 固件编译说明

固件框架主要基于Arduino开发完成，玩过Arduino的基本没有上手难度了，把Firmware/Libraries里面的库安装到Arduino库目录（如果你用的是Arduino IDE的话）即可。

> 我使用的是Visual Studio Code里的platformIO插件。

**然后这里需要修改一个官方库文件才能正常使用：**

首先肯定得安装ESP32的Arduino支持包（百度有海量教程），然后在安装的支持包的`esp32\hardware\esp32\1.0.4\libraries\SPI\src\SPI.cpp`文件中，**修改以下代码中的MISO为26**：

    if(sck == -1 && miso == -1 && mosi == -1 && ss == -1) {
        _sck = (_spi_num == VSPI) ? SCK : 14;
        _miso = (_spi_num == VSPI) ? MISO : 12; // 需要改为26
        _mosi = (_spi_num == VSPI) ? MOSI : 13;
        _ss = (_spi_num == VSPI) ? SS : 15;
这是因为，硬件上连接屏幕和SD卡分别是用两个硬件SPI，其中HSPI的默认MISO引脚是12，而12在ESP32中是用于上电时设置flash电平的，上电之前上拉会导致芯片无法启动，因此我们将默认的引脚替换为26。

> 也可以通过设置芯片熔丝的方式解决这个问题，不过那样的操作是一次性不可逆的，不建议这么玩。

**天气API**用的是心知天气，key我是保存在内存卡里然后读出来。

**内存卡**里具体要放哪些文件可以从程序中看出，内容太多就不放到GitHub上了。

**字体文件**是使用外部字库，可以找自己喜欢的字体用[LvglFontTool](http://www.lfly.xyz/forum.php)转换为bin文件。

## 3. Visual Studio模拟器 & 图片转换脚本

在`Software`文件夹中包含了一个Visual Studio的工程，用VS打开（需要安装C++开发组件）后可以在电脑上模拟LVGL的界面效果，改好之后代码粘贴到Arduino固件那边就可以完成界面移植。

> 这样省的每次修改都要重新交叉编译Arduino的固件，提升开发效率。

`HoloCubic`文件夹下是我用Qt6写的一个上位机软件，可以改WiFi密码等。

> release文件夹里有打包好的软件。

## 4. 关于分光棱镜

我用的时25.4mm x 25.4mm x 25.4mm的棱镜，淘宝应该可以搜到，单个价格80元左右。

分光棱镜的固定比较麻烦，OCA胶水太难粘了，揭下来的时候还弄坏了一个屏幕，我推荐使用UV胶，可以保证没有气泡。

## 5.实物图

![](/5.Docs/images/1.jpg)

![](\5.Docs\images\2.jpg)
