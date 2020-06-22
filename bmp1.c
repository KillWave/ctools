
#include <stdio.h>
#include <stdlib.h>
typedef unsigned short WORD; /*定义WORD为两个字节的类型*/
typedef unsigned long DWORD; /*定义DWORD为e四个字节的类型*/
typedef struct
{ // bmfh
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER;
typedef struct
{ // bmih
    DWORD biSize;
    long biWidth;
    long biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER;
typedef struct tagRGBQUAD
{ // rgbq
    WORD rgbBlue;
    WORD rgbGreen;
    WORD rgbRed;
    WORD rgbReserved;
} RGBQUAD;
typedef struct tagBITMAPINFO
{
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[1];
} BITMAPINFO;

int ReadFileHeader(char *filepath, BITMAPFILEHEADER *bmfh);
int ReadInfoHeader(char *filepaht, BITMAPINFOHEADER *bmih);
int ReadPixelData(char *filepath);
DWORD GetLineBytes(int width, int bitCount);
int main(int argc, char *argv[])
{

    int i = ReadPixelData("1.bmp");
    scanf("%d");
    return 0;
}

//读入文件头
int ReadFileHeader(char *filepath, BITMAPFILEHEADER *bmfh)
{
    FILE *fp;
    //打开文件
    fp = fopen(filepath, "rb");
    if (!fp)
    { //如果打开失败
        printf("Can not open the file:%s\n", filepath);
        return -1;
    }
    //读入bfType
    if (fread(&bmfh->bfType, sizeof(WORD), 1, fp) != 1)
    {
        printf("Can not read bfType in the file header.\n");
        fclose(fp);
        return -1;
    }
    //读入bfSize
    if (fread(&bmfh->bfSize, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read bfSize in the file header.\n");
        fclose(fp);
        return -1;
    }
    //读入bfReserved1
    if (fread(&bmfh->bfReserved1, sizeof(WORD), 1, fp) != 1)
    {
        printf("Can not read bfReserved1 in the file header.\n");
        fclose(fp);
        return -1;
    }
    //读入bfReserved2
    if (fread(&bmfh->bfReserved2, sizeof(WORD), 1, fp) != 1)
    {
        printf("Can not read bfReserved2 in the file header.\n");
        fclose(fp);
        return -1;
    }
    //读入bfOffBits
    if (fread(&bmfh->bfOffBits, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read bfOffBits in the file header.\n");
        fclose(fp);
        return -1;
    }
    //关闭文件指针
    fclose(fp);
    return 0;
}

//读入信息头
int ReadInfoHeader(char *filepath, BITMAPINFOHEADER *bmih)
{
    FILE *fp;
    //打开文件
    fp = fopen(filepath, "rb");
    if (!fp)
    {
        printf("Can not open the file:%s\n", filepath);
        return -1;
    }
    //使文件指针跳过文件头（14字节）
    fseek(fp, 14, SEEK_SET);
    //读入biSize
    if (fread(&bmih->biSize, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read biSize in the info header.\n");
        fclose(fp);
        return -1;
    }
    //读入biWidth
    if (fread(&bmih->biWidth, sizeof(long), 1, fp) != 1)
    {
        printf("Can not read biWidth in the info header.\n");
        fclose(fp);
        return -1;
    }
    //读入biHeight
    if (fread(&bmih->biHeight, sizeof(long), 1, fp) != 1)
    {
        printf("Can not read biHeight in the info header.\n");
        fclose(fp);
        return -1;
    }
    //读入biPlanes
    if (fread(&bmih->biPlanes, sizeof(WORD), 1, fp) != 1)
    {
        printf("Can not read biPlanes in the info header.\n");
        fclose(fp);
        return -1;
    }
    //读入biBitCount
    if (fread(&bmih->biBitCount, sizeof(WORD), 1, fp) != 1)
    {
        printf("Can not read biBitCount in the info header.\n");
        fclose(fp);
        return -1;
    }
    //读入biCompression
    if (fread(&bmih->biCompression, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read biCompression in the info header.\n");
        fclose(fp);
        return -1;
    }
    //读入biSizeImage
    if (fread(&bmih->biSizeImage, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read biSizeImage in the info header.\n");
        fclose(fp);
        return -1;
    }
    //读入biXPelsPerMeter
    if (fread(&bmih->biXPelsPerMeter, sizeof(long), 1, fp) != 1)
    {
        printf("Can not read biXPelsPerMeter in the info header.\n");
        fclose(fp);
        return -1;
    }
    //读入biYPelsPerMeter
    if (fread(&bmih->biYPelsPerMeter, sizeof(long), 1, fp) != 1)
    {
        printf("Can not read biYPelsPerMeter in the info header.\n");
        fclose(fp);
        return -1;
    }
    //读入biClrUsed
    if (fread(&bmih->biClrUsed, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read biClrUsed in the info header.\n");
        fclose(fp);
        return -1;
    }
    //读入biClrImportant
    if (fread(&bmih->biClrImportant, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read biClrImportant in the info header.\n");
        fclose(fp);
        return -1;
    }
    //关闭文件
    fclose(fp);
    return 0;
}

//读取像素数据
int ReadPixelData(char *filepath)
{
    BITMAPINFOHEADER bmih;
    BITMAPFILEHEADER bmfh;
    WORD *imgdata;
    FILE *fp;
    int n;
    int width;
    int height;
    int bitCount;
    long biSizeImage;
    int i;
    int j;
    long a[256] = {0};
    int p;
    DWORD dwLineBytes;
    //读入文件头
    n = ReadFileHeader(filepath, &bmfh);
    if (n == -1)
    {
        printf("Can not read the file header of BMP file.\n");
        return -1;
    }
    //读入信息头
    n = ReadInfoHeader(filepath, &bmih);
    if (n == -1)
    {
        printf("Can not read the info header of BMP file.\n");
        return -1;
    }
    //获取信息头有用信息
    width = bmih.biWidth;
    height = bmih.biHeight;
    bitCount = bmih.biBitCount;
    biSizeImage = bmih.biSizeImage;
    dwLineBytes = GetLineBytes(width, bitCount);
    //printf("%ld\n",dwLineBytes);
    printf("width:%ld\n", width);
    printf("height:%ld\n", height);
    printf("wei%d\n", bitCount);
    printf("ch%ld\n", biSizeImage);
    fp = fopen(filepath, "rb");
    if (!fp)
    {
        printf("Can not open the file:%s\n", filepath);
        return -1;
    }
    if (bitCount == 8 || bitCount == 24)
    {
        fseek(fp, bmfh.bfOffBits, SEEK_SET); //直接跳到像素数据
    }
    else
    {
        printf("we%d!", bitCount);
        printf("8 || 24");
        fclose(fp);
        return -1;
    }

    //给imgdata分配内存
    imgdata = (WORD *)malloc(dwLineBytes * height * sizeof(WORD));
    if (!imgdata)
    {
        printf("Can not allocate memory for the pixel data.\n");
        return -1;
    }

    //读入像素数据，大小为高度乘上每行所占字节数
    n = fread(imgdata, dwLineBytes * height * sizeof(WORD), 1, fp);
    if (n == 0)
    {
        if (ferror(fp))
        {
            printf("Can not read the pixel data.\n");
            free(imgdata);
            fclose(fp);
            return -1;
        }
    }
    printf("addr:%ld\n", imgdata);

    //读取位图像素值
    if (bitCount == 8)
    {
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                //读取灰度值
                p = *(imgdata + dwLineBytes * (height - 1 - i) + j);
                a[p]++;
                //printf("%d,",p);
            }
        }
        printf("\n");
    }
    else if (bitCount == 24)
    {
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width * 3; j++)
            {
                // printf("(");
                //读取蓝色分量
                p = *(imgdata + dwLineBytes * (height - 1 - i) + j);
                // printf("%d,", p);
                j++;
                //读取绿色分量
                p = *(imgdata + dwLineBytes * (height - 1 - i) + j);
                // printf("%d,", p);
                j++;
                //读取红色分量
                p = *(imgdata + dwLineBytes * (height - 1 - i) + j);
                // printf("%d,", p);
                // printf(")");
            }
            printf("\n");
        }
    }
    else
    {
        printf("只支持8或24位");
    }
    free(imgdata);
    fclose(fp);
    printf("统计结果如下：\n");
    for (i = 0; i < 256; i++)
    {
        printf("wei%3dis%ld\n", i, a[i]);
    }

    return 0;
}

DWORD GetLineBytes(int width, int bitCount)
{
    //首先bitCount是指位图的每个像素所占的二进制位数，不是字节数；
    //其次，windows中位图每行所占的字节数必须为4的倍数，
    //例如灰度图中每行200个像素占用200个字节，如果每行有201个像素就占用204个字节。
    //return ((width*bitCount/8+3)/4)*4;
    return (width * bitCount + 31) / 32 * 4;
}