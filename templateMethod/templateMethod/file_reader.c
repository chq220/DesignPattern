#include"stdio.h"	//为了使用 FILE,代表文件类型
#include"stdlib.h"	//为了使用INT_MAX, INT_MIN

int read_file(const char *pFname, int(*processor)(FILE *fp))
	//int (*processor)(FILE *fp)函数指针：
	//有了函数指针，就可以将函数作为参数传入
	//int：返回值类型为int
	//（*processor)函数指针名为processor,前面加*代表这是一个函数指针
	//(FILE *fp)代表传入的参数类型
{
	FILE* fp = fopen(pFname, "r");	//打开一个名为pFname的文件，返回文件指针
	if (fp == NULL)					//打开失败则返回-1
	{
		return -1;
	}

	int ret = processor(fp);			//通过函数指针调用函数processor,返回状态值ret

	fclose(fp);						//关闭文件
	return ret;
}


static int range_processor(FILE *fp)		//静态函数，只在本文件中可见
{
	int min = INT_MAX;
	int max = INT_MIN;
	char buf[256];

	while ((fgets(buf, sizeof(buf), fp)) != NULL)
	{
		if (buf[0] == '\n')	//检测到空行就返回-1
		{
			return -1;
		}
		int value = atoi(buf);
		min = min > value ? value : min;
		max = max < value ? value : max;
	}

	return max - min;
}

int range(const char* pFname)
{
	return read_file(pFname, range_processor);
}