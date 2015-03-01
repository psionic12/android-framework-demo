此代码实现了由applications层->Framework层->HAL->kernel drive的调用。代码路径与android源码路径一致，直接覆盖即可。由于kernel层建立的cde设备（char_device_example)的可读权限较高，因此需要在解压ramdisk.img，在ramdisk.img文件中的ueventd.rc文件中添加一行

/dev/cde	0666	root	root

然后再重新打包

最后在android源代码根目录中执行make，在linux kernel中执行make。


					刘亚飞
					der.weaf@163.com