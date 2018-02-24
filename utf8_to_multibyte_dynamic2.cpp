#include <windows.h> // console functions
#include <cstdio> // std::printf, std::size_t
#include <string> // std::string, std::wstring

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
		if (ws.find_first_of(L"\r\n") != std::wstring::npos)
			break;
	}

	int mb_size = WideCharToMultiByte(CP_UTF8, 0, ws.data(), static_cast<int>(ws.length()), NULL, 0, NULL, NULL);
	std::string mb_str(static_cast<std::size_t>(mb_size), 0);

	//since C++17 mb_str.data() is mutable, since C++11 &(mb_str[0]) is ok instead
	WideCharToMultiByte(CP_UTF8, 0, ws.data(), static_cast<int>(ws.length()), &(mb_str[0]), mb_size, NULL, NULL);

	std::printf("ENTERED: %s\n", mb_str.data()); // because std::cout prints gibberish

	return 0;
}