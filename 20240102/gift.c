#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h> 
#include <string.h>
#include <stdlib.h>
#define FONT_COLOR 0xf100 //红色
int k;
unsigned char hzCode[16];
unsigned short *fb = 0;
 
void getHZCode(unsigned char incode[], unsigned char hzCode[16])
{
	long offset;//相对于字库起始位置的偏移字节数  
	int quCode = incode[0] - 0xa0;//区码:该汉字的区号       
	int weiCode = incode[1] - 0xa0;//位码:该汉字的位号
	offset = (94 * (quCode - 1) + (weiCode - 1)) * 32;//32:一个汉字需要32字节（16*16=256个点，256/8=32）     
	FILE *HZK;
	HZK = fopen(".\\HZK16.bin", "rb");
	if (HZK == NULL)    
	{
		printf("Can't Open HZK16\n");
		exit(0);
	}
    //fseek(FILE *stream, long offset, int fromwhere);函数设置文件指针stream的位置    
    //如果执行成功，stream将指向以fromwhere为基准，偏移offset（指针偏移量）个字节的位置,函数返回0    
    //偏移起始位置：文件头0(SEEK_SET)，当前位置1(SEEK_CUR)，文件尾2(SEEK_END)  
	fseek(HZK, offset, SEEK_SET);
 		//size_t fread ( void *buffer, size_t size, size_t count, FILE *stream)    
    //从一个文件流中读数据，最多读取count个项，每个项size个字节，如果调用成功返回实际读取到的项个数（小于或等于count）,如果不成功或读到文件末尾返回 0    
    //buffer:用于接收数据的内存地址    
    //size:要读的每个数据项的字节数，单位是字节    
    //count:要读count个数据项，每个数据项size个字节    
    //stream:输入流    
	fread(hzCode, 1, 32, HZK);//读取表示此汉字的32字节数到hzCode中    
}
 
void PrintLCD(int top, int left) 
{
	int i, j, k;
		for (j = 0; j < 16; j++) 
        {
			for (i = 0; i < 2; i++)
            {
				for (k = 0; k < 8; k++) 
                {
					if (hzCode[j][i] & (0x80 >> k))
						*(fb + (j + top) * 240 + left + i * 8 + k) = FONT_COLOR;
				}
			}
		}
 
}

int main()  
{  
    //http://www.qqxiuzi.cn/bianma/zifuji.php 可以查询汉字相应的GB2312编码
    unsigned char incode[2] = {0xce,0xd2};//要显示的汉字  
    //unsigned char incode[2] = "我";//要显示的汉字  
    unsigned char hzCode[32];  
    int i;  
    int j = 0;  
  
    getHZCode(incode, hzCode);  
    for(i=0; i<32; i++){  
        for(j=0; j<8; j++){  
            if(hzCode[i] << j & 0x80)  
                printf("●");  
            else  
                printf("○");  
        }  
        if((i+1) % 2 == 0)  
            printf("\n");  
    }  
    return 0;  
} 

#if 0
int main()
{	
	int i,j;
	int fd_fb = 0;
	unsigned char incode[2];//存储区码和位码
	int strLength = 0;//字符串长度
	char testStr[] = {0xB1, 0xB1,
			0xBE, 0xA9,
			0xD3, 0xCA,
			0xB5, 0xE7,
			0xB4, 0xF3,
			0xD1, 0xA7
			};
	strLength = strlen(testStr);
	
	fd_fb = open("/dev/fb0", O_RDWR);//打开FrameBuffer驱动
	fb = (unsigned short *)mmap(0, 240 * 320 * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);//映射显示存储器，2:2Bytes
	memset(fb,0,240 * 320 * 2); //清屏  
	for (k = 0; k < strLength; k += 2) {
		incode[0] = testStr[k];//区码
		incode[1] = testStr[k++];//位码
		getHZCode(incode, hzCode);		
		PrintLCD(90, (k / 2) * (16 + 5));//显示点阵
	}
}
#endif
 
 
 
 