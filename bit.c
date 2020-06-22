#include <stdio.h>
#include <string.h>
int Judge(int n);
int Detection(void);

int main(void)
{

	int n = Detection();//输入数据检查再赋值
	int k = Judge(n);//检测数组需要的长度
	int y[k];//创建数组储存十六进制数
	memset(y,'\0',sizeof(y));//清空数组

	int i,j;
	j = 0;
	while( n >= 16 )//把转换好的十六进制数依次输入数组
	{
		i = (n % 16);//先是求余
		y[j] = i;//把得到的余数转为十六进制数（例如“11”转“b”）
		j++;//数组下标移位
		n /= 16;//求商再赋值给它自己（方便下个循环再除）
		if(n < 16)
			y[j] = n;
	}

	while(j >= 0)//把储存了十六进制数的数组倒着输出
	{
		if(j > 0)//判断是不是最后一个，是的话换行
			printf("%d", y[j]);
		else
			printf("%d\n",y[j]);
		j--;
	}

	return 0;
}

int Judge(int n)//这个函数的作用是用来判断需要定义的数组大小的
{
	int k = 1;
	int m = n;
	while(m > 16)//如果小于16，那么1位就行了
	{
		m /= 16;//如果大于16先除与16
		k++;//加一位
	}
	return k;
}

int Detection(void)//这个是第一篇博客里面的那个代码的封装版，用来保证输入的数为合法
{
	int n;
	while(1)
	{
		if(scanf("%d", &n) != 1 || getchar() != '\n')
		{
			printf("你输入的数据有误，请再输一遍:");
			while(getchar() != '\n');
		}else
			break;
	}
	return n;
}