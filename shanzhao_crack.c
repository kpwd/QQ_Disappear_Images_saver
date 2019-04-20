#include <sys/inotify.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
/*
《公安部门QQ闪照取证程序》
由于本程序过于邪恶QwQ，老衲在这里郑重说明一下咕咕估。
这个程序是用来公安部门取证使用，用来干坏坏的事情我不会管的！！！>_<
你们啊，不要喜欢弄个大新闻，说我的程序侵犯了别人的隐私，就把我批判一番，naive!
参考资料：
https://blog.csdn.net/u010155023/article/details/51969513
https://www.jiangmiao.org/blog/2179.html
https://www.ibm.com/developerworks/cn/linux/l-ubuntu-inotify/
https://www.cnblogs.com/sky-heaven/p/5884475.html

让我们隆重感谢楼上大佬的无偿滋瓷！
*/
/*
struct inotify_event {
	int wd; //watch descriptor 
	uint32_t mask;  //mask of events 
	uint32_t cookie;  //unique cookie 
	uint32_t len;  //size of 'name' field 
	char name[]; //nul-terminated name 
};

--------------------------------------------------------------------------------------------------------------------------------
那么这个鳖孙玩意到底咋破解啊？
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
*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
int main(int argc, char *argv[]){
	char *TargetDir;  
	char *DestnationDir;  
	char buffer[BUF_LEN];
	unsigned int filenumber=0;
	int length,i=0;
	if (argc == 1) {
		printf("**********HELP ME!!************\n");
		printf("YOU: I can't use your shit program !! :(\n");
		printf("I :I am so sorry to here that,and help you immediately! >_<\n");
		printf("Execute 'Program diskcache /sdcard/bak' \n");
		return 0;
	}
	if (argc == 2) {
		TargetDir = malloc(3);
		strcat(TargetDir,"./");
	}else {
		TargetDir=malloc(strlen(argv[1])+1);
		DestnationDir=malloc(strlen(argv[2])+1);
		*(TargetDir)='\0';
		*(DestnationDir)='\0';
		strcat(TargetDir,argv[1]);
		strcat(DestnationDir,argv[2]);
		if(DestnationDir[strlen(DestnationDir)-1]!='/'){//if last char is not /
			strcat(DestnationDir,"/"); // add /
		}
		if(TargetDir[strlen(TargetDir)-1]!='/'){
			strcat(TargetDir,"/");
		}
	} 
	int fd=inotify_init();
	if (fd == -1)
	{
		perror("I can not be inited! :(\n");
		exit(EXIT_FAILURE);
	}
	int wd = inotify_add_watch(fd,TargetDir, IN_CLOSE_WRITE);
	if (wd == -1)
	{
		perror("There can not be watched! :(\n");
		exit(EXIT_FAILURE);
	}else{
		printf("I am watching this dir: [%s] \n and immediately copy new image to [%s] if it exits.\n",TargetDir,DestnationDir);
	}
	while(1){
		//printf("Waiting...\n");
		length=read( fd,buffer,BUF_LEN );  
		while ( i < length ) {
			struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
			i += EVENT_SIZE + event->len;
			if ( event->len ) {
				char head[9]={0};
				char *TargetFileName;
				TargetFileName=(char *)malloc(strlen(TargetDir)+event->len+1);
				*(TargetFileName)='\0';
				strcat(TargetFileName,TargetDir);
				strcat(TargetFileName,event->name);
				//memcpy(EventFileName,event->name,event->len);
				printf("TargetFileName: %s\n",TargetFileName);
				FILE* rfile=fopen(TargetFileName,"r");
				if(!(rfile&&fread(head,1,8,rfile)==8)){
					printf("Can't open TargetFileName!\n");
					goto CLEAR;
				}
				if(strcmp("ENCRYPT:",head)==0){
					//printf("Pass it!\n");
					goto CLEAR_AND_CLOSE_FILES;
					//This file was ENCRYPTED so I can do nothing
				}else{
					//Catched it! it was decrypted so I must immediately copy it to destnation
					char *DestnationFileName;
					unsigned int DestnationFileReadSize;
					char DestnationFileReadData[1024];
					DestnationFileName=(char *)malloc(strlen(DestnationDir)+event->len+4+1);//+4=strlen(".jpg")
					*(DestnationFileName)='\0';
					strcat(DestnationFileName,DestnationDir);
					strcat(DestnationFileName,event->name);
					strcat(DestnationFileName,".jpg");
					if(access(DestnationFileName,F_OK)!=-1){
						//printf("Pass it!\n");
						goto CLEAR_AND_CLOSE_FILES;
					}
					printf("SaveFileName: %s\n",DestnationFileName);
					FILE* DestnationFileNameP=fopen(DestnationFileName,"w");
					fwrite(head,1,8,DestnationFileNameP);
					while(DestnationFileReadSize=fread(DestnationFileReadData,1,1024,rfile)){
						fwrite(DestnationFileReadData,1,DestnationFileReadSize,DestnationFileNameP);
					}
					fclose(DestnationFileNameP);
					//printf("DestnationFileName: %s\n",DestnationFileName);
					
					//fread(rfile,sizeof(char),1024,filedata);
				}
				CLEAR_AND_CLOSE_FILES:
				fclose(rfile);
				CLEAR:
				free(TargetFileName);
			}
		}
		i=0;
	}
	close(fd);
	free(TargetDir);
	free(DestnationDir);
	return 0;
}
