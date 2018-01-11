#include <windows.h> // console functions
#include <cstdio> // std::printf, std::size_t
#include <string> // std::string, std::wstring
#include <memory> // std::unique_ptr, std::make_unique

#define DEFAULT_INPUT_LENGTH 255 // any length > 0 really

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	WCHAR w_str[DEFAULT_INPUT_LENGTH];
	DWORD n_read;
	HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
	std::wstring ws;

	while (ReadConsoleW(console, w_str, DEFAULT_INPUT_LENGTH, &n_read, NULL))
	{
		ws += std::wstring(w_str, static_cast<std::size_t>(n_read));
		if (ws.find_last_of(L"\r\n") != std::wstring::npos)
			break;
	}

	int mb_size = WideCharToMultiByte(CP_UTF8, 0, ws.data(), ws.length(), NULL, 0, NULL, NULL);
	std::unique_ptr<CHAR[]> mb_str = std::make_unique<CHAR[]>(static_cast<std::size_t>(mb_size));

	WideCharToMultiByte(CP_UTF8, 0, ws.data(), ws.length(), mb_str.get(), mb_size, NULL, NULL);
	std::string s(mb_str.get(), static_cast<std::size_t>(mb_size));


	std::printf("ENTERED: %s\n", s.c_str()); // because std::cout prints gibberish

	return 0;
}