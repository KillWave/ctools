
#include <stdio.h>
#include <stdlib.h>
typedef unsigned short WORD; /*����WORDΪ�����ֽڵ�����*/
typedef unsigned long DWORD; /*����DWORDΪe�ĸ��ֽڵ�����*/
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

//�����ļ�ͷ
int ReadFileHeader(char *filepath, BITMAPFILEHEADER *bmfh)
{
    FILE *fp;
    //���ļ�
    fp = fopen(filepath, "rb");
    if (!fp)
    { //�����ʧ��
        printf("Can not open the file:%s\n", filepath);
        return -1;
    }
    //����bfType
    if (fread(&bmfh->bfType, sizeof(WORD), 1, fp) != 1)
    {
        printf("Can not read bfType in the file header.\n");
        fclose(fp);
        return -1;
    }
    //����bfSize
    if (fread(&bmfh->bfSize, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read bfSize in the file header.\n");
        fclose(fp);
        return -1;
    }
    //����bfReserved1
    if (fread(&bmfh->bfReserved1, sizeof(WORD), 1, fp) != 1)
    {
        printf("Can not read bfReserved1 in the file header.\n");
        fclose(fp);
        return -1;
    }
    //����bfReserved2
    if (fread(&bmfh->bfReserved2, sizeof(WORD), 1, fp) != 1)
    {
        printf("Can not read bfReserved2 in the file header.\n");
        fclose(fp);
        return -1;
    }
    //����bfOffBits
    if (fread(&bmfh->bfOffBits, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read bfOffBits in the file header.\n");
        fclose(fp);
        return -1;
    }
    //�ر��ļ�ָ��
    fclose(fp);
    return 0;
}

//������Ϣͷ
int ReadInfoHeader(char *filepath, BITMAPINFOHEADER *bmih)
{
    FILE *fp;
    //���ļ�
    fp = fopen(filepath, "rb");
    if (!fp)
    {
        printf("Can not open the file:%s\n", filepath);
        return -1;
    }
    //ʹ�ļ�ָ�������ļ�ͷ��14�ֽڣ�
    fseek(fp, 14, SEEK_SET);
    //����biSize
    if (fread(&bmih->biSize, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read biSize in the info header.\n");
        fclose(fp);
        return -1;
    }
    //����biWidth
    if (fread(&bmih->biWidth, sizeof(long), 1, fp) != 1)
    {
        printf("Can not read biWidth in the info header.\n");
        fclose(fp);
        return -1;
    }
    //����biHeight
    if (fread(&bmih->biHeight, sizeof(long), 1, fp) != 1)
    {
        printf("Can not read biHeight in the info header.\n");
        fclose(fp);
        return -1;
    }
    //����biPlanes
    if (fread(&bmih->biPlanes, sizeof(WORD), 1, fp) != 1)
    {
        printf("Can not read biPlanes in the info header.\n");
        fclose(fp);
        return -1;
    }
    //����biBitCount
    if (fread(&bmih->biBitCount, sizeof(WORD), 1, fp) != 1)
    {
        printf("Can not read biBitCount in the info header.\n");
        fclose(fp);
        return -1;
    }
    //����biCompression
    if (fread(&bmih->biCompression, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read biCompression in the info header.\n");
        fclose(fp);
        return -1;
    }
    //����biSizeImage
    if (fread(&bmih->biSizeImage, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read biSizeImage in the info header.\n");
        fclose(fp);
        return -1;
    }
    //����biXPelsPerMeter
    if (fread(&bmih->biXPelsPerMeter, sizeof(long), 1, fp) != 1)
    {
        printf("Can not read biXPelsPerMeter in the info header.\n");
        fclose(fp);
        return -1;
    }
    //����biYPelsPerMeter
    if (fread(&bmih->biYPelsPerMeter, sizeof(long), 1, fp) != 1)
    {
        printf("Can not read biYPelsPerMeter in the info header.\n");
        fclose(fp);
        return -1;
    }
    //����biClrUsed
    if (fread(&bmih->biClrUsed, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read biClrUsed in the info header.\n");
        fclose(fp);
        return -1;
    }
    //����biClrImportant
    if (fread(&bmih->biClrImportant, sizeof(DWORD), 1, fp) != 1)
    {
        printf("Can not read biClrImportant in the info header.\n");
        fclose(fp);
        return -1;
    }
    //�ر��ļ�
    fclose(fp);
    return 0;
}

//��ȡ��������
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
    //�����ļ�ͷ
    n = ReadFileHeader(filepath, &bmfh);
    if (n == -1)
    {
        printf("Can not read the file header of BMP file.\n");
        return -1;
    }
    //������Ϣͷ
    n = ReadInfoHeader(filepath, &bmih);
    if (n == -1)
    {
        printf("Can not read the info header of BMP file.\n");
        return -1;
    }
    //��ȡ��Ϣͷ������Ϣ
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
        fseek(fp, bmfh.bfOffBits, SEEK_SET); //ֱ��������������
    }
    else
    {
        printf("we%d!", bitCount);
        printf("8 || 24");
        fclose(fp);
        return -1;
    }

    //��imgdata�����ڴ�
    imgdata = (WORD *)malloc(dwLineBytes * height * sizeof(WORD));
    if (!imgdata)
    {
        printf("Can not allocate memory for the pixel data.\n");
        return -1;
    }

    //�����������ݣ���СΪ�߶ȳ���ÿ����ռ�ֽ���
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

    //��ȡλͼ����ֵ
    if (bitCount == 8)
    {
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                //��ȡ�Ҷ�ֵ
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
                //��ȡ��ɫ����
                p = *(imgdata + dwLineBytes * (height - 1 - i) + j);
                // printf("%d,", p);
                j++;
                //��ȡ��ɫ����
                p = *(imgdata + dwLineBytes * (height - 1 - i) + j);
                // printf("%d,", p);
                j++;
                //��ȡ��ɫ����
                p = *(imgdata + dwLineBytes * (height - 1 - i) + j);
                // printf("%d,", p);
                // printf(")");
            }
            printf("\n");
        }
    }
    else
    {
        printf("ֻ֧��8��24λ");
    }
    free(imgdata);
    fclose(fp);
    printf("ͳ�ƽ�����£�\n");
    for (i = 0; i < 256; i++)
    {
        printf("wei%3dis%ld\n", i, a[i]);
    }

    return 0;
}

DWORD GetLineBytes(int width, int bitCount)
{
    //����bitCount��ָλͼ��ÿ��������ռ�Ķ�����λ���������ֽ�����
    //��Σ�windows��λͼÿ����ռ���ֽ�������Ϊ4�ı�����
    //����Ҷ�ͼ��ÿ��200������ռ��200���ֽڣ����ÿ����201�����ؾ�ռ��204���ֽڡ�
    //return ((width*bitCount/8+3)/4)*4;
    return (width * bitCount + 31) / 32 * 4;
}