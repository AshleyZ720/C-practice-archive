#include <stdio.h>
#include <stdlib.h>

// 定义字库文件路径
#define FONT_FILE_PATH "font.dat"

// 定义字模的宽度和高度
#define FONT_WIDTH 16
#define FONT_HEIGHT 16
// 提取汉字的点阵字模
void extractFont(char ch, unsigned char *fontData) {
    FILE *fontFile = fopen(FONT_FILE_PATH, "rb");
    if (fontFile == NULL) {
        printf("无法打开字库文件\n");
        return;
    }

    // 计算汉字在字库文件中的偏移量
    int offset = (ch - 0x4E00) * FONT_WIDTH * FONT_HEIGHT / 8;

    // 定位到汉字的偏移位置
    fseek(fontFile, offset, SEEK_SET);

    // 读取字模数据
    fread(fontData, FONT_WIDTH * FONT_HEIGHT / 8, 1, fontFile);

    fclose(fontFile);
}

int main() {
    // 要提取的汉字
    char ch = '中';

    // 计算字模数据的大小
    int dataSize = FONT_WIDTH * FONT_HEIGHT / 8;

    // 分配存储字模数据的内存空间
    unsigned char *fontData = (unsigned char *)malloc(dataSize);

    // 提取汉字的点阵字模
    extractFont(ch, fontData);

    // 打印字模数据
    for (int i = 0; i < dataSize; i++) {
        for (int j = 0; j < 8; j++) {
            if (fontData[i] & (1 << j)) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    // 释放内存空间
    free(fontData);

    return 0;
}