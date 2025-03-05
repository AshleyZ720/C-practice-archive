#include <stdio.h>

// 定义汉字点阵数组
char chinese[][16] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 汉字1的点阵信息
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 汉字2的点阵信息
    // 其他汉字的点阵信息
};

// 打印汉字点阵
void printChinese(char chinese[][16]) {
    for (int i = 0; i < sizeof(chinese) / sizeof(chinese[0]); i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 8; k++) {
                if (chinese[i][j] & (0x80 >> k)) {
                    printf("*"); // 可以根据需要修改为其他字符或者输出到屏幕
                } else {
                    printf(" "); // 可以根据需要修改为其他字符或者输出到屏幕
                }
            }
        }
        printf("\n");
    }
}

int main() {
    // 输入汉字的索引
    int index;
    printf("请输入汉字的索引：");
    scanf("%d", &index);

    // 打印汉字点阵
    printChinese(chinese[index]);

    return 0;
}