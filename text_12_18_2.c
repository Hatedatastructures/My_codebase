#include <stdio.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
int main()
{
    /*读取文件*/
    FILE*pr=fopen("W:\\text.bmp","rb");
    if(pr==NULL)
    {
        printf("打开文件失败\n");
        printf("%s\n",strerror(errno));
        return 1;
    }
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    /*2进制修改*/
    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pr);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pr);
    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    printf("width=%d,height=%d\n", width, height);
    fseek(pr, 0, SEEK_END);
    /*定位文件指针*/
    long fileSize = ftell(pr);
    printf("file size: %ld bytes\n", fileSize);
    /*输出*/
    /*写入文件*/
    FILE*pw=fopen("W:\\text1.txt","wb");
    if(pw==NULL)
    {
        printf("打开文件失败\n");
        printf("%s\n",strerror(errno));
        return 1;
    }
   for (int i = 0; i < width; i++)
    {
    for (int j = 0; j < height; j++)
    {
        unsigned char pixel[3];
        fseek(pr, fileHeader.bfOffBits + (j * width + i) * 3, SEEK_SET);
        fread(pixel, 3, 1, pr);
        fprintf(pw, "%d %d %d\n", pixel[0], pixel[1], pixel[2]);
    }
    }
    fclose(pw);
    pw=NULL;
    fclose(pr);
    pr=NULL;
    return 0;
}