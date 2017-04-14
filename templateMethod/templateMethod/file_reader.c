#include"stdio.h"	//Ϊ��ʹ�� FILE,�����ļ�����
#include"stdlib.h"	//Ϊ��ʹ��INT_MAX, INT_MIN

int read_file(const char *pFname, int(*processor)(FILE *fp))
	//int (*processor)(FILE *fp)����ָ�룺
	//���˺���ָ�룬�Ϳ��Խ�������Ϊ��������
	//int������ֵ����Ϊint
	//��*processor)����ָ����Ϊprocessor,ǰ���*��������һ������ָ��
	//(FILE *fp)������Ĳ�������
{
	FILE* fp = fopen(pFname, "r");	//��һ����ΪpFname���ļ��������ļ�ָ��
	if (fp == NULL)					//��ʧ���򷵻�-1
	{
		return -1;
	}

	int ret = processor(fp);			//ͨ������ָ����ú���processor,����״ֵ̬ret

	fclose(fp);						//�ر��ļ�
	return ret;
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

int range(const char* pFname)
{
	return read_file(pFname, range_processor);
}