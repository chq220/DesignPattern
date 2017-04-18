#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct FileAccessorContext {
	const char * const pFname;
	const char * const pMode;
	void(*const processor)(struct FileAccessorContext *pThis, FILE * fp);
}FileAccessorContext;