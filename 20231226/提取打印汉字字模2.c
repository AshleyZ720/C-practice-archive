#include <stdio.h>
#include <stdlib.h>

//#include<graphics.h>

/* x,y为显示坐标，s为显示字符串，colour为颜色 */
void hanzi16(int x,int y,char *s,int colour)
{
FILE *fp;
char buffer[32]; /* 32字节的字模缓冲区 */
int i,j,k;
unsigned char qh,wh;
unsigned long location;
if((fp=fopen("hzk16","rb"))==NULL)
{
printf("Can't open hzk16!");
getc();
exit(0);
}
while(*s)
{
qh=*s-0xa0;
wh=*(s+1)-0xa0;
location=(94*(qh-1)+(wh-1))*32L; /* 计算汉字字模在文件中的位置 */
fseek(fp,location,SEEK_SET);
fread(buffer,1,32,fp);
for(i=0;i<16;i++)
for(j=0;j<2;j++)
for(k=0;k<8;k++)
if(((buffer[i*2+j]>>(7-k))&0x1)!=NULL)
putpixel(x+8*j+k,y+i,colour);
s+=2;
x+=16; /* 汉字间距 */
}
fclose(fp);
}

int main(){
int gd=DETECT,gm;
initgraph(&gd,&gm,"");

hanzi16(246,200,"大学生计算机",BROWN);

getch();
closegraph();    
}

