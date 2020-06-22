#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <mycon.h>
#pragma pack(2)

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned char BYTE;

typedef struct BMP_FILE_HEADER
{
    WORD bType;
    DWORD bSize;
    WORD bReserved1;
    WORD bReserved2;
    DWORD bOffset;
} BMPFILEHEADER;

typedef struct BMP_INFO
{
    DWORD bInfoSize;
    DWORD bWidth;
    DWORD bHeight;
    WORD bPlanes;
    WORD bBitCount;
    DWORD bCompression;
    DWORD bmpImageSize;
    DWORD bXPelsPerMeter;
    DWORD bYPelsPerMeter;
    DWORD bClrUsed;
    DWORD bClrImportant;
} BMPINFO;

typedef struct BGR_INFO
{
    BYTE blue;
    BYTE green;
    BYTE red;
} BGRINFO;

#define NUM_CHAR 25

BMPFILEHEADER bmpFileHeader;
BMPINFO bmpInfo;
BGRINFO bgrinfoTest;
char ch[NUM_CHAR + 1] = "$&#80+;: =~-*^\"`',. ";

int main(int argc, char *argv[])
{
    FILE *fp;
    if ((fp = fopen("1.bmp", "rb")) == NULL)
    {
        printf("要转换的图片不存在");
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0, 0);
    fread(&bmpFileHeader, sizeof(BMPFILEHEADER), 1, fp);
    fread(&bmpInfo, sizeof(BMPINFO), 1, fp);

    BGRINFO bgrinfo[bmpInfo.bWidth][bmpInfo.bHeight];
    int color[bmpInfo.bWidth][bmpInfo.bHeight];
    int grey;
    int useless = (bmpInfo.bWidth * 3 % 4 == 0) ? 0 : (4 - bmpInfo.bWidth * 3 % 4);
    for (int j = 0; j < bmpInfo.bHeight; j++)
    {
        for (int i = 0; i < bmpInfo.bWidth; i++)
        {
            fread(&bgrinfo[i][j], sizeof(BGRINFO), 1, fp);
            grey = (bgrinfo[i][j].blue * 11 + bgrinfo[i][j].green * 59 + bgrinfo[i][j].red * 30 + 50) / 100;
            // grey = (bgrinfo[i][j].blue + bgrinfo[i][j].green  + bgrinfo[i][j].red) ;
            color[i][bmpInfo.bHeight - j - 1] = grey;
        }
        fseek(fp, useless, SEEK_CUR);
    }
    set_title("test 鸣人");
    set_size(bmpInfo.bWidth*3, bmpInfo.bHeight);
    gotoxy(0, 0);
    for (int j = 0; j < bmpInfo.bHeight; j++)
    {
        for (int i = 0; i < bmpInfo.bWidth; i++)
        {
             printf("%c%c", ch[(NUM_CHAR - 1) * color[i][j] / 255], ch[8 * color[i][j] / 255]);
        }
        printf("\n");
    }

    fclose(fp);
    system("pause");
    return 0;
}