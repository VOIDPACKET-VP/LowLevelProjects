#include <Windows.h>
#include <tchar.h> // we need it for the _T macro 

int main(int argc, char** argv) {

	HWND wesnoth_window = FindWindow(NULL, _T("The Battle for Wesnoth - 1.14.9"));

	DWORD process_id = 0;
	GetWindowThreadProcessId(wesnoth_window, &process_id);

	HANDLE wesnoth_process = OpenProcess(PROCESS_ALL_ACCESS, TRUE, process_id);


	DWORD gold_value = 0;
	SIZE_T bytes_read = 0;

	ReadProcessMemory(wesnoth_process, reinterpret_cast<LPCVOID>(0x017EED18), &gold_value, 4, &bytes_read);

	gold_value += 0xA90;

	ReadProcessMemory(wesnoth_process, reinterpret_cast<LPCVOID>(gold_value), &gold_value, 4, &bytes_read);

	gold_value += 4;


	DWORD new_gold_value = 555;
	SIZE_T bytes_written = 0;

	WriteProcessMemory(wesnoth_process, reinterpret_cast<LPVOID>(gold_value), &new_gold_value, 4, &bytes_written);

	return 0;
}