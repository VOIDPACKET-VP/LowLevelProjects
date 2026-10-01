#include <Windows.h>

DWORD ret_address = 0xCCAF90;

DWORD* player_base;
DWORD* game_base;
DWORD* gold;


__declspec(naked) void codecave() {
	__asm {
		pushad
	}

	// Our Hack :
	player_base = (DWORD*)0x017EED18;
	game_base = (DWORD*)(*player_base + 0xA90);
	gold = (DWORD*)(*game_base + 4);
	*gold = 888;

	__asm {
		popad
		mov eax, dword ptr ds : [ecx]
		lea esi, dword ptr ds : [esi]
		jmp ret_address
	}
}



BOOL WINAPI DLLMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {

	// When our DLL is attached, unprotect the memory at the code we wish to write at
	DWORD old_protect;
	unsigned char* hook_location = (unsigned char*)0x00CCAF8A;

	if (fdwReason == DLL_PROCESS_ATTACH) {
		VirtualProtect((void*)hook_location, 6, PAGE_EXECUTE_READWRITE, &old_protect); // we chose 6 : cause we want to rewrite 6 bytes

		// we set the initial byte at the target location to 0xE9 (the jmp opcode) 
		*hook_location = 0xE9;

		// we calculate the 4-byte destination offset using the formula : new_location - original_location + 5
		*(DWORD*)(hook_location + 1) = (DWORD)&codecave - ((DWORD)hook_location + 5);

		// we set the sixth byte to nop (index 5)
		*(hook_location + 5) = 0x90;
	}

	return true;
}

