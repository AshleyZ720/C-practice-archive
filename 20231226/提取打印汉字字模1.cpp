#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int dataIdx;
    unsigned char word[3];
    unsigned long Qcode, Wcode;
    unsigned long offset = 139;
    unsigned long word_num;
    FILE * fp = NULL;
    fp = fopen(".\\HZK16.bin", "rb");
    int zhChrNum = 0;
    unsigned char dat[32];
    char zhString[256 * 2 + 1];
    char systemSetting[64];
    while(1)
    {
        printf("请输入纯中文字符串(输入quit退出):\n");
        scanf("%s", zhString);
        if(strstr(zhString, "quit") != NULL)break; 
        zhChrNum = strlen(zhString) / 2;
        sprintf(systemSetting, "mode con: cols=%d lines=%d", zhChrNum*32, 35);
        system(systemSetting);
        system("cls");
        unsigned char DisBuf1[zhChrNum * 16 * 2 * 16];
		unsigned char DisBuf2[zhChrNum * 16 * 16];
        for(int ZhChrIdx = 0; ZhChrIdx < zhChrNum; ZhChrIdx++)
        {
            word[0] = zhString[ZhChrIdx * 2];
            word[1] = zhString[ZhChrIdx * 2 + 1];
            word[2] = 0;
            printf("%s", word);
            Qcode = word[0] - 0xa0;
            Wcode = word[1] - 0xa0;
            word_num = (Qcode - 1) * 94 + (Wcode - 1);
            fseek(fp, word_num * 32, SEEK_SET);
            for(dataIdx = 0; dataIdx < 32; dataIdx++)
            {
				fscanf(fp, "%c", &dat[dataIdx]);
				for (int bits = 0; bits < 8; bits++)
				{
					if (dat[dataIdx] >> (7 - bits) & 0x01 == 1) {
						DisBuf1[(dataIdx / 2)*zhChrNum * 32 + (bits * 2) + ((dataIdx % 2) + ZhChrIdx * 2) * 16] = "█"[0];
						DisBuf1[(dataIdx / 2)*zhChrNum * 32 + (bits * 2 + 1) + ((dataIdx % 2) + ZhChrIdx * 2) * 16] = "█"[1];
						DisBuf2[(dataIdx / 2)*zhChrNum * 16 + bits + ((dataIdx % 2) + ZhChrIdx * 2) * 8] = 'O';
					}
					else {
						DisBuf1[(dataIdx / 2)*zhChrNum * 32 + (bits * 2) + ((dataIdx % 2) + ZhChrIdx * 2) * 16] = ' ';
						DisBuf1[(dataIdx / 2)*zhChrNum * 32 + (bits * 2 + 1) + ((dataIdx % 2) + ZhChrIdx * 2) * 16] = ' ';
						DisBuf2[(dataIdx / 2)*zhChrNum * 16 + bits + ((dataIdx % 2) + ZhChrIdx * 2) * 8] = ' ';
					}
				}
            }
        }
        for(dataIdx = 0; dataIdx < (zhChrNum * 32) * 16; dataIdx++)
        {
            if(dataIdx % (zhChrNum * 32) == 0)printf("\n");
            printf("%c", DisBuf1[dataIdx]);
        }
		for (dataIdx = 0; dataIdx < (zhChrNum * 16) * 16; dataIdx++)
		{
			if (dataIdx % (zhChrNum * 16) == 0)printf("\n");
			printf("%c", DisBuf2[dataIdx]);
		}
		printf("\n");
    }
    fclose(fp);
    
    return 0;
}


