#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>

typedef struct {
	int value;
	TCHAR* sequence;
} SIDret;
void FreeSidRet(SIDret*);

SIDret* ShowInitialDialog(_In_ HINSTANCE, _In_ int nCmdShow);
