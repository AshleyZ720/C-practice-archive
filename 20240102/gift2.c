#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE* fphzk = NULL;
    int i, j, k, offset;
    int flag;
    unsigned char buffer[32];
    unsigned char word[2] = {0xCE, 0xD2}; // 改成你的转码后的汉字编码
    unsigned char key[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
    fphzk = fopen(".\\HZK16.bin", "rb");
    if(fphzk == NULL){
        fprintf(stderr, "error hzk16\n");
        return 1;
    }

    offset = (94*(unsigned int)(word[0]-0xa0-1)+(word[1]-0xa0-1))*32;
    fseek(fphzk, offset, SEEK_SET);
    fread(buffer, 1, 32, fphzk);
    for(k=0; k<16; k++){
        for(j=0; j<2; j++){
            for(i=0; i<8; i++){
                flag = buffer[k*2+j]&key[i];
                printf("%s", flag?"●":"○");
            }
        }
        printf("\n");
    }

    for(k=0; k<31; k++){
        printf("0x%02X,", buffer[k]);
    }

    printf("\n");

    fclose(fphzk);
    fphzk = NULL;
    return 0;
}