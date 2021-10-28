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

void print_loop(int x, int y, int type_arr)
{
    int row, column;
	switch (type_arr)
    {
        case 1:
            row = 12;
            column = 15;
            break;
	    case 2:
		case 4:
		    row = 5;
            column = 6;
            break;
	    case 3:
		    row = 6;
            column = 7;
            break;
        default:
            break;
    }
    for(int ii = 0; ii < 12; ii++)
    {
        for(int jj = 0; jj < 25; jj++)
        {
            Sleep(100);
            goto_xy(jj + x, ii + y, false);
            switch (type_arr)
            {
                case 1:
				    if(heart[ii][jj])
                        wcout << L"*";
				    else
                        wcout << L" ";
                    break;
			    case 2:
				    if(i[ii][jj])
                        wcout << L"*";
				    else
                        wcout << L" ";
                    break;
			    case 3:
				    if(l[ii][jj])
                        wcout << L"*";
				    else
                        wcout << L" ";
                    break;
			    case 4:
				    if(u[ii][jj])
                        wcout << L"*";
				    else
                        wcout << L" ";
                    break;
                default:
                    break;
            }
        }
        wcout << endl;
    }
}

void print_heart()
{
    int index = 0;
    while (true)
    {
        text_color(index % 14 + 1);
        if (index == 0 || index % 2 == 0)
        {
            print_loop(30, 5, 1);
            print_loop(55, 5, 1);
            print_loop(80, 5, 1);
        }

        print_loop(38, 8, 2);
        print_loop(61, 8, 3);
		print_loop(87, 8, 4);
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
    while (load < 14)
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
