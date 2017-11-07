#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string>
#include<fstream>
#include <conio.h>
using namespace std;

int board[2][5][5]; //빙고판 
int first = 0, turn; //순서 
int num = 0, cnum=0,flag; //숫자, 빙고수 
int i = 0, j = 0, u, c = 0;
int who[11], max = 0;
int cnt1, cnt2, over=0;
void Result();
void numcheck();
void cnumcheck();

void color(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}
//[출처] C++ 글씨 색 넣는법 | 작성자 마늘맛쿨피스

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//출처: http ://tmong.tistory.com/entry/C-gotoxy [티몽구니 개발노트]

void Bingocheck() {

	for (u = 0; u < 2; u++) {
		int hzero = 0, wzero = 0;

		flag = 0;

		if (board[u][0][0] == 0 && board[u][1][1] == 0 && board[u][2][2] == 0 && board[u][3][3] == 0 && board[u][4][4] == 0) {
			++flag; //대각선
			Sleep(1000);
		}
		if (board[u][0][4] == 0 && board[u][1][3] == 0 && board[u][2][2] == 0 && board[u][3][1] == 0 && board[u][4][0] == 0) {
			++flag; //대각선
			Sleep(1000);


		}

		for (i = 0; i < 5; i++) {
			wzero = 0;
			hzero = 0;

			for (j = 0; j < 5; j++) {
				if (board[u][i][j] == 0) {
					++wzero;
					if (wzero == 5){
						++flag;
						if (flag == 3) {
							numcheck();
							cnumcheck();
							turn = u;
							cout << u;
							Sleep(2000);

							Result();

						}
					}
				}
			}

			for (j = 0; j < 5; j++) {
				if (board[u][j][i] == 0) {
					++hzero;
					if (hzero == 5){
						++flag;
						if (flag == 3) {
							numcheck();
							cnumcheck();
							turn = u;
							cout << u;
							Sleep(2000);
							Result();
						}
					}
				}
			}
		} //for i

		
	} //for u
} //Bingocheck()

void numcheck() { //칸 0으로 바꿔주기
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[0][i][j] == num) { //내 빙고판 num을 0으로 대입
				board[0][i][j] = 0;
			} //if
		} //for
	} //for

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[1][i][j] == num) { //ai빙고판 num을 0으로 대입
				board[1][i][j] = 0;
			} //if
		} //for
	} //for
}

void cnumcheck() {
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[1][i][j] == cnum) { //num을 0으로 대입
				board[1][i][j] = 0;
				break;
			} //if
		} //for
	} //for

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[0][i][j] == cnum) { //num을 0으로 대입
				board[0][i][j] = 0;
				break;
			} //if
		} //for
	} //for

}

void overnum() {
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[1][i][j] == 0 && board[1][i][j] == cnum) { //중복
				over = 1;
				break;
			} //if
		} //for
	} //for
}

void Makecnum() {
	//who방 초기화
	for (i = 0; i < 12; i++) {
		who[i] = 0;
	} //for

	//빈 칸 찾기
	for (cnt1 = 0; cnt1 < 5; cnt1++) {
		for (cnt2 = 0; cnt2 < 5; cnt2++) {
			if (board[1][cnt1][cnt2] == 0) { //체크됬으면
				if (cnt1 == cnt2) who[10]++; //왼쪽대각선
				else if (cnt1 + cnt2 == 4) who[11]++; //오른쪽대각선
				who[cnt1]++; //가로
				who[cnt2 + 5]++; //세로
			} //if
		}
	}
	max = 0;

	//채울 칸 찾기
	for (i = 0; i < 12; i++) {
		//cout << i << " " << who[i] << endl;
		if (who[i] < 5 && who[i+1] <5) {
			if (who[i] < who[i +1]) {
						max = i+1; //제일 많이 체크된 줄
			}
		}
	}

	//cnum 넣기
	if (max < 5) {//가로
		for (i = 0; i < 5; i++) {
			if (board[1][max][i] != 0) {
				cnum = board[1][max][i];
				overnum();
				if (over == 1) {  continue; }
			}
		}
	}

	else if (max > 4 && max <10) {//세로
		for (i = 0; i < 5; i++) {
			if (board[1][i][max-5] != 0) {
				cnum = board[1][i][max - 5];
				overnum();
				if (over == 1) { continue; }
			}
		}
	}

	else if (max == 10) {
		for (i = 0; i < 5; i++) {
			if (board[1][i][i] != 0) {
				cnum = board[1][i][i];
				overnum();
				if (over == 1) {continue; }
			}
		}
	}

	else if(max==11){
		for (i = 0; i < 5; i++) {
			if (board[1][i][4 - i] != 0) {
				cnum = board[1][i][4 - i];
				overnum();
				if (over == 1) { continue; }
			}
		}
	}

} //Makecnum



void printbingo() {
	turn = 0;
	int x = 10, y;
	Sleep(500);
	system("cls");

	gotoxy(20, 2);
	cout << "user 1";

	for (int y = 0; y < 25; y++) {
		gotoxy(60, y);
		cout << "|";
	}

	gotoxy(10, 3);
	cout << "--------------------------" << endl;

	for (i = 0, y=4, x=10; i < 5; i++) { //출력
		gotoxy(x, y);
		for (j = 0; j < 5; j++) {
			cout << "| ";
			if (board[turn][i][j] == 0)	{
				color(14); //노란색
				printf("%2d ", board[turn][i][j]);
			}
			else {
				color(15); //흰색
				printf("%2d ", board[turn][i][j]);
			}
			color(15); //흰색으로 다시 설정
		}
		cout << "|" << endl;

		y += 1;
		gotoxy(10, y);
		cout << "--------------------------" << endl;
		y += 1;
	}

	gotoxy(90, 8);
	cout << "AI의 수 : " << cnum;
}

void cprintbingo() {
	turn = 1;
	int x=80, y;
	Sleep(500);
	system("cls");
	gotoxy(90, 2);
	cout << "user 2";

	for (int y = 0; y < 25; y++) {
		gotoxy(60, y);
		cout << "|";
	}

	gotoxy(80, 3);
	cout << "--------------------------" << endl;

	for (i = 0, y = 4, x = 80; i < 5; i++) { //출력
		gotoxy(x, y);
		for (j = 0; j < 5; j++) {
			cout << "| ";
			if (board[turn][i][j] == 0)	{
				color(9); //파란색
				printf("%2d ", board[turn][i][j]);
			}
			else {
				color(15); //흰색
				printf("%2d ", board[turn][i][j]);
			}
			color(15); //흰색으로 다시 설정
		}

		cout << "|";
		
		y += 1;
		gotoxy(80, y);
		cout << "--------------------------" << endl;
		y += 1;
	}
	Sleep(1000);
}

void Result() {
	
	if (u = 1){
		cprintbingo();
		cout << "승자는 AI !!" << endl;
	}
	else if (u = 0) {
		printbingo();
		cout << "승자는 user1 !!" << endl;
	}
	exit(1);
}



void game() {
	do {
		if (first == 0) { //사용자가 승리
		
			printbingo();
			gotoxy(7, 17);
			cout << "숫자를 선택하세요(1~25) : ";
			cin >> num;
			numcheck();
			Bingocheck();
			cnumcheck();
			Bingocheck();

			
			cprintbingo();
			gotoxy(77, 17);
			cout << "컴퓨터 차례입니다.";
			Makecnum();
			numcheck();
			Bingocheck();
			cnumcheck();
			Bingocheck();

		}

		else { //컴퓨터가 승리
			
			cprintbingo();
			gotoxy(77, 17);
			cout << "컴퓨터 차례입니다.";
			Makecnum();
			numcheck();
			Bingocheck();
			cnumcheck();
			Bingocheck();

			printbingo();
			gotoxy(7, 17);
			cout << "숫자를 선택하세요(1~25) : ";
			cin >> num;
			numcheck();
			Bingocheck();
			cnumcheck();
			Bingocheck();

		}
	} while (!(flag >= 3)); //빙고가 3개면 우승자 배출

}//game()



void makebingo() {
	int cnt = 1, a = 0, n = 5, ranx, rany;

	srand(time(NULL));

	cout << "빙고판 생성중 . . ." << endl;  //	cin >> n;
	Sleep(1000); //잠시 대기
	for (u = 0; u < 2; u++) {
		cnt = 1;
		for (i = 0; i < n; i++) { //숫자 넣기
			for (j = 0; j < n; j++) {
				board[u][i][j] = cnt++;
			}
		}

		for (i = 0; i < n; i++) { //랜덤으로 다시 넣기
			for (j = 0; j < n; j++) {
				ranx = rand() % n; //내꺼
				rany = rand() % n;

				a = board[u][i][j];
				board[u][i][j] = board[u][ranx][rany];
				board[u][ranx][rany] = a;

			} //j for
		} //i for
	}
}

int rsp() {
	int answer = 0, com = 0, x=0, y = 0;
	char* position[3] = { "가위", "바위", "보" };
	char* result[3][3] = { "비김", "패배", "승리", "승리", "비김", "패배", "패배", "승리", "비김" };
	srand(time(NULL));
	system("cls");

	gotoxy(45, 5);
	cout << "가위바위보로 순서를 정합니다.\n";

	while (1) {
		gotoxy(40, 7);
		cout << "가위(0) | 바위(1) | 보(2) 를 눌러주세요 : ";
		cin >> answer;

		com = rand() % 3;

		if (!(answer >= 0 && answer < 3)) { //입력받은 값 확인
			gotoxy(47, 2);
			//y += 2;
			cout << "다시 입력해주세요ㅠㅠ\n";
			continue;
		}

		gotoxy(40, 11 + y);
		cout << "컴퓨터 : " << position[com] << ", 사용자 : " << position[answer] << ", 결과 : " << result[answer][com];

		if (answer == com) 	{
			y += 2;
			continue;
		}
		else if (result[answer][com] == "승리") {
			first = 0;
			break;
		}
		else {
			first = 1;
			break;
		}
		Sleep(1000);
		system("cls");

		
	}
	Sleep(2000);
	system("cls");

	return first;

}


void intro() {
	system("cls");
	gotoxy(40, 10);
	cout << "왼쪽 빙고판이 user, 오른쪽 빙고판이 컴퓨터입니다~!";
	gotoxy(40, 11);
	cout << "AI보다 먼저 빙고 3줄을 맞추면 우승입니다!";
	gotoxy(40, 15);
	cout << "게임을 시작하려면 아무거나 눌러주세요.";
	_getch();
	Sleep(3000);
}

int main() {
	char num;

	cout << "\n\n\n\n\n" << endl;

	ifstream in("bingos.txt");
	string s;

	if (in.is_open()) {
		in.seekg(0, ios::end);

		int size = in.tellg();
		s.resize(size);
		in.seekg(0, ios::beg);

		in.read(&s[0], size);
		cout << s << endl;
	}
	else {
		cout << "파일을 찾을 수 없습니다." << endl;
	}
	cout << "\n\n\n" << endl;
	gotoxy(45, 27);
	cout << " 게임 설명은 2번 !";
	gotoxy(40, 29);
	cout << "시작하려면 아무 키나 누르세요 ! : ";
	num = _getch();

	if (num == '2') 
		intro(); //설명

	rsp(); //시작
	makebingo(); //빙고판 생성
	game(); //게임 시작


	//Result();	
}
