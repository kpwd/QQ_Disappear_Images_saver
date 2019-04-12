# QQ_Disappear_Images_saver
安卓QQ闪照破解（原图级破解，非二次截图！）

《公安部门QQ闪照取证程序》  
由于本程序过于邪恶QwQ，老衲在这里郑重说明一下咕咕估。  
这个程序是用来公安部门取证使用，用来干坏坏的事情我不会管的！！！>_<  
你们啊，不要喜欢弄个大新闻，说我的程序侵犯了别人的隐私，就把我批判一番，naive!  
编程时使用的参考资料：  
https://blog.csdn.net/u010155023/article/details/51969513  
https://www.jiangmiao.org/blog/2179.html  
https://www.ibm.com/developerworks/cn/linux/l-ubuntu-inotify/  
https://www.cnblogs.com/sky-heaven/p/5884475.html  
 
让我们隆重感谢楼上大佬的无偿滋瓷！  

--------------------------------------------------------------------------------------------------------------------------------
那么这个鳖孙玩意到底咋破解啊？  
PS：如果不想gcc编译可以去/bin/里找我的编译版本，这样就无需安装clang了  
  
   
首先吧，把这个神奇的c文件放到/sdcard/ （什么？不知道sdcard？你咋来的github混蛋！）  
然后在/sdcard/下创建一个目录/sdcard/bak  
然后，手机要安装termux，然后执行  
pkg install clang  
cp /sdcard/shanzhao_crack.c ~  
gcc shanzhao_crack.c  


这时程序已经编译完成，别忙着执行，切换到QQ的界面，然后到闪照附近（别点闪照）  
执行下面的  
./a.out /sdcard/tencent/MobileQQ/diskcache /sdcard/bak  

（个别使用存储重定向的可能需要稍微变通一下路径，比如我的是  
/sdcard/VirtualXposed/vsdcard/0/tencent/MobileQQ/diskcache  
当然，一般情况下还是不变的。）  

这时进入监听模式，切换到QQ界面，点击闪照，然后不出意外的话  
 /sdcard/bak 会产生一些文件（也有一些垃圾文件），其中就有闪照的原图。  
