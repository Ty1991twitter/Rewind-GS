#pragma once
#include <Windows.h>
// Another guided hacking tutorial for this one , https://www.youtube.com/watch?v=jTl3MFVKSUM
class Hooks {
	bool Hook(void* tohook, void* ourfunct, uintptr_t len) {
		if (len < 5) {
			return false;
		}
		DWORD curProtection;
		VirtualProtect(tohook, len, PAGE_EXECUTE_READWRITE, &curProtection);

		memset(tohook, 0x90, len);

		DWORD relativeAddress = ((DWORD)ourfunct - (DWORD)tohook) - 5;

		*(BYTE*)tohook = 0xE9;
		*(DWORD*)((DWORD)tohook + 1) = relativeAddress;

		DWORD temp;
		VirtualProtect(tohook, len, curProtection, &temp);

		return true;
	}
};