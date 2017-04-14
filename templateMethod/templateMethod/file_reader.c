#include"stdio.h"	//Ϊ��ʹ�� FILE,�����ļ�����
#include"stdlib.h"	//Ϊ��ʹ��INT_MAX, INT_MIN

//�޸ĺ�����ʹ����Է��ط�intֵ
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

static int range_processor(FILE *fp)		//��̬������ֻ�ڱ��ļ��пɼ�
{
	int min = INT_MAX;
	int max = INT_MIN;
	char buf[256];

	while ((fgets(buf, sizeof(buf), fp)) != NULL)
	{
		if (buf[0] == '\n')	//��⵽���оͷ���-1
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
		fprintf(stderr, "�޷����ļ� '%s'��\n", pFname);
	}
	return ctx.result;
}