#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>

int setcc(int min, int timeout);
int setlflag(int flags, int enable);
int main()
{
    int attr = 1;
    int len = 0;
    int total = 0;
    char buf[128];
    memset(buf, 0, sizeof(buf));
    ioctl(STDIN_FILENO, FIONBIO, &attr);
    setlflag(ECHO | ICANON, 0);
    while(1)
    {
    len = read(STDIN_FILENO, &buf[0], 1);
    //setcc(0, 10);
    printf("%d\n",len);
    //fread(&c, 1, stdin);
    if (len > 0) 
    {
    
           
            printf("buf = %s\n", buf);     

            memset(buf, 0, sizeof(buf));
        
    }
    else printf("no\n");
    usleep(50000);
    }
    #if 0
    if(*c == 65)
    {
        printf("          %s\n", c);
    }
    else printf("no\n");
    usleep(50000);
    }
    #endif
    return 0;
}

int setcc(int min, int timeout)
{
    struct termios attr;
    tcgetattr(STDIN_FILENO, &attr);
    attr.c_cc[VMIN] = min;
    attr.c_cc[VTIME] = timeout;
    return tcsetattr(STDIN_FILENO, TCIFLUSH, &attr);
}

int setlflag(int flags, int enable)
{
    struct termios attr;
    tcgetattr(STDIN_FILENO, &attr);
    if (enable) {
        attr.c_lflag |= flags; 
    } else {
        attr.c_lflag &= ~flags; 
    }
    return tcsetattr(STDIN_FILENO, TCIFLUSH, &attr);
}