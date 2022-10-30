#pragma once
#include <string>
#include <minwindef.h>
#include <Windows.h>
#include <Psapi.h>
struct Pattern {
	const char* mask;
	const char* pattern;
};
namespace FNPatterns {
	Pattern GObjects;
}
//I had to use a guided hacking Youtube tutorial since I have no idea how it works
//Tutorial link : https://www.youtube.com/watch?v=S_SR5l_hquw
MODULEINFO GetModuleInfo() {
	MODULEINFO modinfo = {0};
	HMODULE hModule = GetModuleHandle(nullptr); //Using nullptr since NeonitePP uses this , the tutorial told me to use a char * but that didn't seem to work at all
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

//This ALSO is in the tutorial
DWORD FindPattern(Pattern patternwithmask) {
	const char* mask = patternwithmask.mask;
	const char* pattern = patternwithmask.pattern;

	MODULEINFO minfo = GetModuleInfo();
	DWORD base = (DWORD)minfo.lpBaseOfDll;
	DWORD size = (DWORD)minfo.SizeOfImage;
	DWORD patternlength = (DWORD)strlen(mask);

	for (DWORD i = 0; i < size - patternlength; i++) {
		bool found = true;
		for (DWORD j = 0; j < patternlength; j++) {
			found &= mask[j] == '? ' || pattern[j] == *(char*)(base + i + j);
		}
		if (found) {
			return base + i;
		}
	}
	return NULL;
}