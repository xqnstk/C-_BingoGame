#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;

int board[5][5]; //내 빙고판
int cboard[5][5]; //컴퓨터 빙고판
int first = 0; //순서
int num = 0;

void Bingocheck() {
	int zero;

	for (int i = 0; i < 5; i++) {
		zero = 0;
		for (int j = 0; j < 5; j++) {
			if (board[i][j] == 0) {
				zero++;
				if (zero == 5){
					cout << "빙고다 !";
				}
			}
		} //for j
	} //for i



} //Bingocheck()


void numcheck() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (board[i][j] == num) { //num을 0으로 대입
				board[i][j] = 0;
			} //if
		} //for
	} //for

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (cboard[i][j] == num) { //num을 0으로 대입
				cboard[i][j] = 0;
			} //if
		} //for
	} //for
}

void cnumcheck() {
	int cnum = rand() % 25 + 1;

	cout << "컴퓨터의 수 : " << cnum <<endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (cboard[i][j] == cnum) { //num을 0으로 대입
				cboard[i][j] = 0;
			} //if
		} //for
	} //for

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (board[i][j] == cnum) { //num을 0으로 대입
				board[i][j] = 0;
			} //if
		} //for
	} //for
}

void printbingo() {
	cout << "--------------------------" << endl;

	for (int i = 0; i < 5; i++) { //출력
		for (int j = 0; j < 5; j++) {
			printf("| %2d ", board[i][j]);
		}
		cout << "|" << endl;
		cout << "--------------------------" << endl;
	}
}

void game() {
	int bingo = 0, cbingo = 0;

	while (!(bingo ==3) || (cbingo==3)) {

		cout << "숫자를 선택하세요(1~25) : ";
		cin >> num;

		numcheck();
		Bingocheck();
		printbingo();

		cout << "컴퓨터 차례입니다." << endl;
		Sleep(1000);
		cnumcheck();
		printbingo();

		

	}//while

}//game()



void makebingo() {
	int cnt = 1, a = 0, n = 5, ranx, rany;

	srand(time(NULL));

	cout << "빙고판 생성중 . . ." << endl;  //	cin >> n;
	Sleep(2000); //잠시 대기

	for (int i = 0; i < n; i++) { //숫자 넣기
		for (int j = 0; j < n; j++) {
				board[i][j] = cnt++;
				cboard[i][j] = cnt;
		}
	}

	for (int i = 0; i < n; i++) { //랜덤으로 다시 넣기
		for (int j = 0; j < n; j++) {
			ranx = rand() % n; //내꺼
			rany = rand() % n;
					
			a = board[i][j];
			board[i][j] = board[ranx][rany];
			board[ranx][rany] = a;

			ranx = rand() % n; //컴퓨터꺼
			rany = rand() % n;
				
			a = cboard[i][j];
			cboard[i][j] = cboard[ranx][rany];
			cboard[ranx][rany] = a;
		} //j for
	} //i for

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
			continue;
		}

		cout << "컴퓨터 : " <<position[com] << ", 사용자 : " << position[answer] << "\n결과 : " << result[answer][com] << "\n";

		if (answer == com) 	continue;
		else if (result[answer][com] == "이김") {
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
	cout << "설명";

	if ("게임을 시작하려면 아무거나 눌러주세요.");
	//get

	Sleep(3000);
}

int main() {
	int num = 0;

	cout << "\n\n\n\n\n\n\n\n\n\n" << endl;

	cout << "시작하려면 1을, 게임방법은 2를 눌러주세요 : ";
	cin >> num;

	if (num == 2) 
		intro(); //설명

	rsp(); //시작
	
	makebingo(); //빙고판 생성
	
	game(); //게임 시작
	
}
