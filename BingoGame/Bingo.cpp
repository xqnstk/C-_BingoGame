#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string>
#include<fstream>
using namespace std;

int board[2][5][5]; //빙고판
int first = 0; //순서
int num = 0, flag; //숫자, 빙고수
int i = 0, j = 0, u = 0;

void color(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}
//[출처] C++ 글씨 색 넣는법 | 작성자 마늘맛쿨피스

int Bingocheck() {
	int hzero, wzero;
	
	for (u = 0; u < 2; u++) {
		flag = 0;

		if (board[u][0][0] == 0 && board[u][1][1] == 0 && board[u][2][2] == 0 && board[u][3][3] == 0 && board[u][4][4] == 0) {
			flag++; //대각선
			//cout << "bingo!";
		}
		if (board[u][0][4] == 0 && board[u][1][3] == 0 && board[u][2][2] == 0 && board[u][3][1] == 0 && board[u][4][0] == 0) {
			flag++; //대각선
			//cout << "bingo!";
		}

		for (i = 0; i < 5; i++) { //세로
			hzero = 0;
			for (j = 0; j < 5; j++) {
				if (board[u][j][i] == 0) {
					hzero++;
					if (hzero == 5){
						//cout << "h빙고다 !";
						flag++;
					}
				}
			} //for j
		} //for i

		for (i = 0; i < 5; i++) { //가로
			wzero = 0;
			for (j = 0; j < 5; j++) {
				if (board[u][i][j] == 0) {
					wzero++;
					if (wzero == 5){
						//cout << "w빙고다 !";
						flag++;
					}
				}
			} //for j
		} //for i
		if (flag == 3) {
			break;
		}
	} //for u
	return flag;
} //Bingocheck()


void numcheck() {
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[0][i][j] == num) { //num을 0으로 대입
				board[0][i][j] = 0;
			} //if
		} //for
	} //for

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[1][i][j] == num) { //num을 0으로 대입
				board[1][i][j] = 0;
			} //if
		} //for
	} //for
}

void cnumcheck() {
	int cnum = rand() % 25 + 1;

	cout << "컴퓨터의 수 : " << cnum <<endl;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[1][i][j] == cnum) { //num을 0으로 대입
				board[1][i][j] = 0;
			} //if
		} //for
	} //for

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[0][i][j] == cnum) { //num을 0으로 대입
				board[0][i][j] = 0;
			} //if
		} //for
	} //for
}

void printbingo() {
	Sleep(1000);
	system("cls");
	cout << "--------------------------" << endl;

	for (i = 0; i < 5; i++) { //출력
		for (j = 0; j < 5; j++) {
			cout << "| ";
			if (board[0][i][j] == 0)	{
				color(14); //노란색
				printf("%2d ", board[0][i][j]);
			}
			else {
				color(15); //흰색
				printf("%2d ", board[0][i][j]);
			}
			
			color(15); //흰색으로 다시 설정
		}
		cout << "|" << endl;
		cout << "--------------------------" << endl;
	}
}

void game() {
	do {
		cout << first <<endl;
		if (first == 0) { //사용자가 승리
			cout << "숫자를 선택하세요(1~25) : ";
			cin >> num;

			numcheck();
			Bingocheck();
			printbingo();

			if (flag == 3) break;

			cout << "컴퓨터 차례입니다." << endl;
			Sleep(1000);
			cnumcheck();
			printbingo();
		}

		else { //컴퓨터가 승리

			cout << "컴퓨터 차례입니다." << endl;
			Sleep(1000);
			cnumcheck();
			printbingo();

			if (flag == 3) break;

			cout << "숫자를 선택하세요(1~25) : ";
			cin >> num;
			numcheck();
			Bingocheck();
			printbingo();
		}
	} while (!(flag >= 3)); //빙고가 3개면 우승자 배출

}//game()



void makebingo() {
	int cnt = 1, a = 0, n = 5, ranx, rany;

	srand(time(NULL));

	cout << "빙고판 생성중 . . ." << endl;  //	cin >> n;
	Sleep(1000); //잠시 대기
	for (u = 0; u < 2; u++) {
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
	printbingo();
}

int rsp() {
	int answer = 0, com = 0;
	char* position[3] = { "가위", "바위", "보" };
	char* result[3][3] = { "비김", "패배", "승리", "승리", "비김", "패배", "패배", "승리", "비김" };
	srand(time(NULL));
	system("cls");

	cout << "게임 시작! \n";
	cout << "가위바위보로 순서를 정합니다.\n";

	while (1) {
		cout << "가위(0) | 바위(1) | 보(2) 를 눌러주세요 : ";
		cin >> answer;

		com = rand() % 3 ;

		if (!(answer>=0 && answer<3)) { //입력받은 값 확인
			cout << "잘못 입력하셨습니다. 다시 입력해주세요.\n";
			cout << "--------------------------" << endl;
			continue;
		}

		cout << "컴퓨터 : " <<position[com] << ", 사용자 : " << position[answer] << "\n결과 : " << result[answer][com] << "\n";
		Sleep(500);
		system("cls");

		if (answer == com) 	continue;
		else if (result[answer][com] == "승리") {
			first = 0;
			break;
		}
		else {
			first = 1;
			break;
		}
	}
	Sleep(2000);
	system("cls");

	return first;

}


void intro() {
	system("cls");
	cout << "설명" <<endl;

	cout << "게임을 시작하려면 아무거나 눌러주세요.";

	Sleep(3000);
}

int main() {
	int num = 0;

	cout << "\n\n\n\n\n\n\n\n\n\n" << endl;

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

	cout << "시작하려면 1을, 게임방법은 2를 눌러주세요 : ";
	cin >> num;

	if (num == 2) 
		intro(); //설명

	rsp(); //시작
	
	makebingo(); //빙고판 생성
	
	game(); //게임 시작


	
}
