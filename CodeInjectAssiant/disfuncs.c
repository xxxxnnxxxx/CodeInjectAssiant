#include "disfuncs.h"
#include <Windows.h>
#include "disasm.h"

int get_opcodefromasminst(DWORD baseaddr,char* asminst,char * outbuf)
{
	int j;
	t_asmmodel am;
	char errtext[TEXTLEN];
	j=Assemble(asminst,baseaddr,&am,0,0,errtext);
	memcpy(outbuf,am.code,j);
	return j;
}