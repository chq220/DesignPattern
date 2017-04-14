#include"stdio.h"	//为了使用 FILE,代表文件类型
#include"stdlib.h"	//为了使用INT_MAX, INT_MIN

//修改函数，使其可以返回非int值
typedef struct FileReaderContext
{
	const char* const pFname;
	void(*const processor)(struct FileReaderContext *pThis, FILE *fp);
}FileReaderContext;

typedef struct {
	FileReaderContext base;
	int result;
} MyFileReaderContext;

int read_file(FileReaderContext *pCtx)
{
	FILE *fp = fopen(pCtx->pFname, "r");
	if (fp == NULL)
	{
		return -1;
	}

	pCtx->processor(pCtx, fp);

	fclose(fp);
	return 0;
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

static void calc_range(FileReaderContext *p, FILE *fp)
{
	MyFileReaderContext *pCtx = (MyFileReaderContext *)p;
	pCtx->result = range_processor(fp);
}

int range(const char *pFname) {
	MyFileReaderContext	ctx = { {pFname, calc_range}, 0 };

	if (read_file(&ctx.base) != 0)
	{
		fprintf(stderr, "无法打开文件 '%s'。\n", pFname);
	}
	return ctx.result;
}