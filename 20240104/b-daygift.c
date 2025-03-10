#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

int k;
int tmp=0;
unsigned char *incode[3];
unsigned char hzCode[32];
unsigned short *fb = 0;

void getHZCode(unsigned char (*incode)[3], unsigned char *hzCode, int tmp);

int main()  
{  
    system("play  1.mp3");
    system("clear");
    printf("\033[?25l");
    unsigned char incode[7][3] = {{0xb0,0xd6}, {0xb0,0xd6}, {0xc9,0xfa}, {0xc8,0xd5}, {0xbf,0xec}, {0xc0,0xd6}, {0xa3,0xa1}};
    unsigned char hzCode[32];  
    int i, n, colour;  
    int j = 0; 

    for(int again=0; again<5; again++) 
    {
        for(tmp=0; tmp<7; tmp++)
        {
            getHZCode(incode, hzCode, tmp);   
            for(i=0; i<32; i++)
            {   
                for(j=0; j<8; j++)
                {  
                    if(hzCode[i] << j & 0x80)  
                    {
                        if(again == 0)
                            printf("\033[40;37m●\033[0m");                
                        else
                        {
                            colour = 31 + (int)rand()%7;
                            printf("\033[40;%dm●\033[0m", colour);                      
                        }
                    }
                    else  
                        printf(" ");
                    if(again==0) 
                        usleep(1000);
                    else
                        usleep(1);
                }  
                if((i+1) % 2 == 0 && i != 31)  
                    printf("\n\033[%dC", (tmp*20));                 
            } 
            printf("\033[15A\033[4C");
        }
        printf("\033[15B");

        printf("\033[H");
    }
    printf("\033[15B\n");
    printf("\033[?25h");
    return 0;  
} 

void getHZCode(unsigned char (*incode)[3], unsigned char *hzCode, int tmp)
{
	long offset;
	int quCode = incode[tmp][0] - 0xa0;       
	int weiCode = incode[tmp][1] - 0xa0;
	offset = (94 * (quCode - 1) + (weiCode - 1)) * 32;     
	FILE *fp;
	fp = fopen("HZK16.bin", "rb");
	if (fp == NULL)    
	{
		printf("Can't Open HZK16\n");
		exit(0);
	}
	fseek(fp, offset, SEEK_SET);
	fread(hzCode, 1, 32, fp);
}

