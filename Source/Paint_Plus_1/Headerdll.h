#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

namespace libdll
{
	class myclass{// buil hộ t cái
	public:
		__declspec(dllexport) bool Open();
		__declspec(dllexport) bool Save();
		__declspec(dllexport) void Paint(HDC, POINT  ListPoint[10000], int LoaiHinh[3], int i);
		__declspec(dllexport) void Move(LPARAM lParam, WPARAM wParam, POINT ListPoint[10000], int pos);
	};
}