#ifndef header
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <string>
using namespace std;
#define MAX 100

void goto_xy(int x, int y, bool clreol);
void goto_xy(int x, int y, int text_size);
void text_color(int color);
void resize_Console(int width, int height);
void print_heart(int index);
void print_text(int x, int y, int color, wstring mess, bool clreol);
void print_loop(int x, int y, const int arr[][MAX]);

const int heart[12][25] = {
    {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
}, i[5][6] = {
    {1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1}
}, l[6][7] = {
    {0, 1, 1, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0}
}, u[5][6] = {
    {1, 1, 0, 0, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {0, 1, 1, 1, 1, 0}
}, mgs[13] = {1, 2, 1, 2, 3, 3, 2, 3, 2, 2, 3, 2, 3};

const wstring message[100] = {
    L"Cũng đã lâu rồi chúng ta chưa liên lạc nhỉ",//0
    L"Cậu à, tớ có điều muốn nói với cậu",//15
    L"Không biết bây giờ cậu đã có người thương chưa, hay vẫn bận bịu với sự nghiệp",//21
    L"Tớ thì vẫn như năm nào, vẫn khùng khùng , điên điên, ... và vẫn một mình",
    L"Mọi người thường nói tớ nên mở lòng với một cô gái khác, nhưng nó thật khó",//26
    L"Mỗi khi định mở lòng với ai đó thì thâm tâm tớ tự hỏi ...",//35
    L"Liệu có khi nào sau này cậu cho tớ cơ hội hay không, thế là tớ lại khép lòng mình lại",
    L"Khi xưa tớ vẫn cứ thắc mắc một điều, tại sao lại ...",//41
    L"Nhưng giờ càng lớn tớ cũng dần nhận ra được đáp án và cũng phần nào đoán ra tâm trạng của cậu",
    L"Việc đó thật khó, xin lỗi vì đã vô tình đưa cậu vào tình thế khó xử như vậy",
    L"Từ trước đến nay tớ đã cố mọi cách để quên cậu nhưng đều thất bại",//49
    L"Cái tớ nhận được là nhớ nhung, tương tư, lo lắng, ... và những suy nghĩ về cậu",
    L"\t",
    L"Nhưng dù thế nào thì tớ vẫn hi vọng cậu cho tớ một lần cơ hội nếu có thể",//55
    L"Có lẽ sẽ không đâu nhỉ, chí ít là ở kiếp này",
    L"Nhưng nếu nó sảy ra như một phép màu diệu kỳ thì sao nhỉ?",//61
    L"Tớ không dám hứa sẽ giàu có như Bill Gates, tài giỏi như David Beckham, ...",
    L"Điều tớ có thể hứa và chắc chắn sẽ làm được bằng mọi khả năng là luôn giữ nụ cười trên môi cậu",
    L"Cậu thì quá hoàn hảo, còn tớ thì như những mảnh ghép chấp vá tạm bợ vậy",//68
    L"Tớ cũng không dám quá mơ mộng đâu, mọi thứ nếu được thì mong trở lại như trước kia là quá đủ rồi",
    L"Vì thế tớ sẽ không \"thái quá\" như trước đâu, đơn phương như hiện tại cũng ổn mà",//85
    L"Nó thú vị lắm nhé, không bắt đầu cũng chẳng có kết thúc, ...",
    L"Cảm ơn cậu vì đã xuất hiện trong cuộc đời tới, nói thật lòng đấy",//93
    L"Có rất nhiều chuyện đã sảy ra, nếu không có cậu làm động lực có lẽ tớ đã bỏ cuộc",
    L"Có thể nói cậu là ngọn đền soi sáng cuộc đời tớ cũng không sai",
    L"Hãy thật hạnh phúc bên người cậu chọn nhé",//99
    L"Với con mắt nhìn người tinh tường cùng tính cẩn thận, tỷ mỹ của cậu chắc chắn sẽ không sai đâu",
    L"Nhưng nếu như cậu bị phản bội thì tớ sẽ dùng mọi \"thủ đoạn\" để giành cậu lại đấy",//100
    L"Tớ nói bằng tận đáy con tim mình, dù cho phải trả cái giá nào",
    L"Vì thế hãy thật hạnh phúc nhé, bạn của tôi"
}, loading[14] = {
	L"Loading......10%%",
    L"Loading......15%%",
    L"Loading......21%%",
    L"Loading......26%%",
    L"Loading......35%%",
    L"Loading......41%%",
    L"Loading......49%%",
    L"Loading......55%%",
    L"Loading......61%%",
    L"Loading......68%%",
    L"Loading......85%%",
    L"Loading......93%%",
    L"Loading......99%%",
    L"Loading......100%%"
};
#endif // !header
