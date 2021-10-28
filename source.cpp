#include "header.h"

void goto_xy(int x, int y, bool clreol)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD g = {(short)x, (short)y};
    if (clreol == true)// Delete character line
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
        DWORD written;
        FillConsoleOutputCharacter(handle, ' ', info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, g, &written);
		Sleep(500);
    }
	SetConsoleCursorPosition(handle, g);
}

void text_color(int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

void resize_Console(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void print_text(int x, int y, int color, wstring mess, bool clreol = true)
{
	goto_xy(x, y, clreol);
    text_color(color);
    wcout << mess;
}

void print_loop(int x, int y)
{
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            Sleep(10);
            goto_xy(j + x, i + y, false);
            if(heart[i][j])
                wcout << L"*";
            else
                wcout << L" ";
        }
        wcout << endl;
    }
}

void print_heart()
{
    int index = 0;
	const int y = 8, color = 12;
    const bool clreol = false;
    while (true)
    {
        text_color(index % 14 + 1);
        if (index == 0 || index % 2 == 0)
        {
            print_loop(30, 5);
            print_loop(55, 5);
            print_loop(80, 5);
        }

        print_text(38, y + 0, color, L"1 1 1 1 1 1", clreol);
		print_text(38, y + 1, color, L"    1 1    ", clreol);
		print_text(38, y + 2, color, L"    1 1    ", clreol);
		print_text(38, y + 3, color, L"    1 1    ", clreol);
		print_text(38, y + 4, color, L"1 1 1 1 1 1", clreol);

		print_text(61, y + 0, color, L"  1 1   1 1  ", clreol);
		print_text(61, y + 1, color, L"1 1 1 1 1 1 1", clreol);
		print_text(61, y + 2, color, L"1 1 1 1 1 1 1", clreol);
		print_text(61, y + 3, color, L"  1 1 1 1 1  ", clreol);
		print_text(61, y + 4, color, L"    1 1 1    ", clreol);
		print_text(61, y + 5, color, L"      1      ", clreol);

		print_text(87, y + 0, color, L"1 1     1 1", clreol);
		print_text(87, y + 1, color, L"1 1     1 1", clreol);
		print_text(87, y + 2, color, L"1 1     1 1", clreol);
		print_text(87, y + 3, color, L"1 1 1 1 1 1", clreol);
		print_text(87, y + 4, color, L" 1 1 1 1 1 ", clreol);
        index++;
    }
}
/*Read file with UTF-8
wstring ? read_file(string path) {
    wstring list[MAX], line;
    int index = 0;
	locale::global(locale(""));
	cout.imbue(locale());
    ifstream input(path);
    if (!input.is_open())
    {
        wcout << L"Đọc file lỗi, vui lòng kiểm tra lại";
        system("pause");
    }
	while(!input.eof())
	{
		//TODO ???
	}
    return list;
}*/

void begin(wstring load)
{
    print_text(55, 2, 12, L"CONNECTING FROM LOVE SEVER");
    /*Simulate download
    srand((unsigned int) time(NULL));
    for (int i = 0; i < 100; i++)
    {
		goto_xy(58, 4, false);
        text_color(color);
        wcout << L"Loading......" << (i + 1) << "%%";
        Sleep(rand() % 300 + 700);
    }*/
    print_text(48, 4, 12, L"Gửi tới: Người con gái tôi thầm thương");
    print_text(58, 6, 12, load, false);
    print_text(44, 7, 12, L"____________________________________________");
}
int main()
{
    _setmode(_fileno(stdin), _O_WTEXT);     //needed for input
    _setmode(_fileno(stdout), _O_WTEXT);    //needed for output

    int mess = 0, load = 0;
    const int millisecond = 10000;
	resize_Console(1300, 500);
   	begin(loading[load++]);
    print_text(10, 9, 15, message[mess++]);
    Sleep(3000);
    while (load < size(loading))
    {
        print_text(58, 6, 13, loading[load++], false);
		print_text(10, 9, 15, message[mess++]);
        for (int i = 1; i < mgs[load - 2]; i++)
        {
			print_text(10, 9 + i * 2, 15, message[mess++]);
        }
		Sleep(millisecond);
    }
   	//Sleep(15000);
   	system("cls");
    print_heart();
	wcout << endl;
    system("pause");
	return 0;
}
