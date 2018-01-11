#include <windows.h> // console functions
#include <cstdio> // std::printf, std::size_t

#define MAX_INPUT_LENGTH 255	/* fixed length (handle input limit separately)
                            	if console input buffer data > MAX_INPUT_LENGTH
                            	ReadConsole will read the rest on the next call */

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	
	wchar_t w_str[MAX_INPUT_LENGTH];
	char mb_str[MAX_INPUT_LENGTH * 3 + 1]; // to be on the safe side
	unsigned long n_read;
	void *console = GetStdHandle(STD_INPUT_HANDLE);

	ReadConsole(console, w_str, MAX_INPUT_LENGTH, &n_read, NULL);

	int ch_size = WideCharToMultiByte(CP_UTF8, 0, w_str, n_read, mb_str, sizeof(mb_str), NULL, NULL);
	mb_str[ch_size] = 0;

	std::printf("ENTERED: %s\n", mb_str);  // because std::cout prints gibberish

	return 0;
}