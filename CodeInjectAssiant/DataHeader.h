#ifndef _DATA_HEADER_H_
#define _DATA_HEADER_H_

typedef struct _proc_info_{
	unsigned long pid;
	char procName[256];
	char procPath[1024];
}proc_info,*pproc_info;


#endif