#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string>
#include<fstream>
#include <conio.h>
using namespace std;

int board[2][5][5]; //������ 
int first = 0, turn; //���� 
int num = 0, cnum=0,flag; //����, ����� 
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
//[��ó] C++ �۾� �� �ִ¹� | �ۼ��� ���ø����ǽ�

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//��ó: http ://tmong.tistory.com/entry/C-gotoxy [Ƽ������ ���߳�Ʈ]

void Bingocheck() {

	for (u = 0; u < 2; u++) {
		int hzero = 0, wzero = 0;

		flag = 0;

		if (board[u][0][0] == 0 && board[u][1][1] == 0 && board[u][2][2] == 0 && board[u][3][3] == 0 && board[u][4][4] == 0) {
			++flag; //�밢��
			Sleep(1000);
		}
		if (board[u][0][4] == 0 && board[u][1][3] == 0 && board[u][2][2] == 0 && board[u][3][1] == 0 && board[u][4][0] == 0) {
			++flag; //�밢��
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

void numcheck() { //ĭ 0���� �ٲ��ֱ�
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[0][i][j] == num) { //�� ������ num�� 0���� ����
				board[0][i][j] = 0;
			} //if
		} //for
	} //for

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[1][i][j] == num) { //ai������ num�� 0���� ����
				board[1][i][j] = 0;
			} //if
		} //for
	} //for
}

void cnumcheck() {
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[1][i][j] == cnum) { //num�� 0���� ����
				board[1][i][j] = 0;
				break;
			} //if
		} //for
	} //for

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[0][i][j] == cnum) { //num�� 0���� ����
				board[0][i][j] = 0;
				break;
			} //if
		} //for
	} //for

}

void overnum() {
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[1][i][j] == 0 && board[1][i][j] == cnum) { //�ߺ�
				over = 1;
				break;
			} //if
		} //for
	} //for
}

void Makecnum() {
	//who�� �ʱ�ȭ
	for (i = 0; i < 12; i++) {
		who[i] = 0;
	} //for

	//�� ĭ ã��
	for (cnt1 = 0; cnt1 < 5; cnt1++) {
		for (cnt2 = 0; cnt2 < 5; cnt2++) {
			if (board[1][cnt1][cnt2] == 0) { //üũ������
				if (cnt1 == cnt2) who[10]++; //���ʴ밢��
				else if (cnt1 + cnt2 == 4) who[11]++; //�����ʴ밢��
				who[cnt1]++; //����
				who[cnt2 + 5]++; //����
			} //if
		}
	}
	max = 0;

	//ä�� ĭ ã��
	for (i = 0; i < 12; i++) {
		//cout << i << " " << who[i] << endl;
		if (who[i] < 5 && who[i+1] <5) {
			if (who[i] < who[i +1]) {
						max = i+1; //���� ���� üũ�� ��
			}
		}
	}

	//cnum �ֱ�
	if (max < 5) {//����
		for (i = 0; i < 5; i++) {
			if (board[1][max][i] != 0) {
				cnum = board[1][max][i];
				overnum();
				if (over == 1) {  continue; }
			}
		}
	}

	else if (max > 4 && max <10) {//����
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

	for (i = 0, y=4, x=10; i < 5; i++) { //���
		gotoxy(x, y);
		for (j = 0; j < 5; j++) {
			cout << "| ";
			if (board[turn][i][j] == 0)	{
				color(14); //�����
				printf("%2d ", board[turn][i][j]);
			}
			else {
				color(15); //���
				printf("%2d ", board[turn][i][j]);
			}
			color(15); //������� �ٽ� ����
		}
		cout << "|" << endl;

		y += 1;
		gotoxy(10, y);
		cout << "--------------------------" << endl;
		y += 1;
	}

	gotoxy(90, 8);
	cout << "AI�� �� : " << cnum;
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

	for (i = 0, y = 4, x = 80; i < 5; i++) { //���
		gotoxy(x, y);
		for (j = 0; j < 5; j++) {
			cout << "| ";
			if (board[turn][i][j] == 0)	{
				color(9); //�Ķ���
				printf("%2d ", board[turn][i][j]);
			}
			else {
				color(15); //���
				printf("%2d ", board[turn][i][j]);
			}
			color(15); //������� �ٽ� ����
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
		cout << "���ڴ� AI !!" << endl;
	}
	else if (u = 0) {
		printbingo();
		cout << "���ڴ� user1 !!" << endl;
	}
	exit(1);
}



void game() {
	do {
		if (first == 0) { //����ڰ� �¸�
		
			printbingo();
			gotoxy(7, 17);
			cout << "���ڸ� �����ϼ���(1~25) : ";
			cin >> num;
			numcheck();
			Bingocheck();
			cnumcheck();
			Bingocheck();

			
			cprintbingo();
			gotoxy(77, 17);
			cout << "��ǻ�� �����Դϴ�.";
			Makecnum();
			numcheck();
			Bingocheck();
			cnumcheck();
			Bingocheck();

		}

		else { //��ǻ�Ͱ� �¸�
			
			cprintbingo();
			gotoxy(77, 17);
			cout << "��ǻ�� �����Դϴ�.";
			Makecnum();
			numcheck();
			Bingocheck();
			cnumcheck();
			Bingocheck();

			printbingo();
			gotoxy(7, 17);
			cout << "���ڸ� �����ϼ���(1~25) : ";
			cin >> num;
			numcheck();
			Bingocheck();
			cnumcheck();
			Bingocheck();

		}
	} while (!(flag >= 3)); //���� 3���� ����� ����

}//game()



void makebingo() {
	int cnt = 1, a = 0, n = 5, ranx, rany;

	srand(time(NULL));

	cout << "������ ������ . . ." << endl;  //	cin >> n;
	Sleep(1000); //��� ���
	for (u = 0; u < 2; u++) {
		cnt = 1;
		for (i = 0; i < n; i++) { //���� �ֱ�
			for (j = 0; j < n; j++) {
				board[u][i][j] = cnt++;
			}
		}

		for (i = 0; i < n; i++) { //�������� �ٽ� �ֱ�
			for (j = 0; j < n; j++) {
				ranx = rand() % n; //����
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
	char* position[3] = { "����", "����", "��" };
	char* result[3][3] = { "���", "�й�", "�¸�", "�¸�", "���", "�й�", "�й�", "�¸�", "���" };
	srand(time(NULL));
	system("cls");

	gotoxy(45, 5);
	cout << "������������ ������ ���մϴ�.\n";

	while (1) {
		gotoxy(40, 7);
		cout << "����(0) | ����(1) | ��(2) �� �����ּ��� : ";
		cin >> answer;

		com = rand() % 3;

		if (!(answer >= 0 && answer < 3)) { //�Է¹��� �� Ȯ��
			gotoxy(47, 2);
			//y += 2;
			cout << "�ٽ� �Է����ּ���Ф�\n";
			continue;
		}

		gotoxy(40, 11 + y);
		cout << "��ǻ�� : " << position[com] << ", ����� : " << position[answer] << ", ��� : " << result[answer][com];

		if (answer == com) 	{
			y += 2;
			continue;
		}
		else if (result[answer][com] == "�¸�") {
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
	cout << "���� �������� user, ������ �������� ��ǻ���Դϴ�~!";
	gotoxy(40, 11);
	cout << "AI���� ���� ���� 3���� ���߸� ����Դϴ�!";
	gotoxy(40, 15);
	cout << "������ �����Ϸ��� �ƹ��ų� �����ּ���.";
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
		cout << "������ ã�� �� �����ϴ�." << endl;
	}
	cout << "\n\n\n" << endl;
	gotoxy(45, 27);
	cout << " ���� ������ 2�� !";
	gotoxy(40, 29);
	cout << "�����Ϸ��� �ƹ� Ű�� �������� ! : ";
	num = _getch();

	if (num == '2') 
		intro(); //����

	rsp(); //����
	makebingo(); //������ ����
	game(); //���� ����


	//Result();	
}
