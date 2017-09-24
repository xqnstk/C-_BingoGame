#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string>
#include<fstream>
using namespace std;

int board[2][5][5]; //������
int first = 0; //����
int num = 0, flag; //����, �����
int i = 0, j = 0, u = 0;

void color(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}
//[��ó] C++ �۾� �� �ִ¹� | �ۼ��� ���ø����ǽ�

int Bingocheck() {
	int hzero, wzero;
	
	for (u = 0; u < 2; u++) {
		flag = 0;

		if (board[u][0][0] == 0 && board[u][1][1] == 0 && board[u][2][2] == 0 && board[u][3][3] == 0 && board[u][4][4] == 0) {
			flag++; //�밢��
			//cout << "bingo!";
		}
		if (board[u][0][4] == 0 && board[u][1][3] == 0 && board[u][2][2] == 0 && board[u][3][1] == 0 && board[u][4][0] == 0) {
			flag++; //�밢��
			//cout << "bingo!";
		}

		for (i = 0; i < 5; i++) { //����
			hzero = 0;
			for (j = 0; j < 5; j++) {
				if (board[u][j][i] == 0) {
					hzero++;
					if (hzero == 5){
						//cout << "h����� !";
						flag++;
					}
				}
			} //for j
		} //for i

		for (i = 0; i < 5; i++) { //����
			wzero = 0;
			for (j = 0; j < 5; j++) {
				if (board[u][i][j] == 0) {
					wzero++;
					if (wzero == 5){
						//cout << "w����� !";
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
			if (board[0][i][j] == num) { //num�� 0���� ����
				board[0][i][j] = 0;
			} //if
		} //for
	} //for

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[1][i][j] == num) { //num�� 0���� ����
				board[1][i][j] = 0;
			} //if
		} //for
	} //for
}

void cnumcheck() {
	int cnum = rand() % 25 + 1;

	cout << "��ǻ���� �� : " << cnum <<endl;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[1][i][j] == cnum) { //num�� 0���� ����
				board[1][i][j] = 0;
			} //if
		} //for
	} //for

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (board[0][i][j] == cnum) { //num�� 0���� ����
				board[0][i][j] = 0;
			} //if
		} //for
	} //for
}

void printbingo() {
	Sleep(1000);
	system("cls");
	cout << "--------------------------" << endl;

	for (i = 0; i < 5; i++) { //���
		for (j = 0; j < 5; j++) {
			cout << "| ";
			if (board[0][i][j] == 0)	{
				color(14); //�����
				printf("%2d ", board[0][i][j]);
			}
			else {
				color(15); //���
				printf("%2d ", board[0][i][j]);
			}
			
			color(15); //������� �ٽ� ����
		}
		cout << "|" << endl;
		cout << "--------------------------" << endl;
	}
}

void game() {
	do {
		cout << first <<endl;
		if (first == 0) { //����ڰ� �¸�
			cout << "���ڸ� �����ϼ���(1~25) : ";
			cin >> num;

			numcheck();
			Bingocheck();
			printbingo();

			if (flag == 3) break;

			cout << "��ǻ�� �����Դϴ�." << endl;
			Sleep(1000);
			cnumcheck();
			printbingo();
		}

		else { //��ǻ�Ͱ� �¸�

			cout << "��ǻ�� �����Դϴ�." << endl;
			Sleep(1000);
			cnumcheck();
			printbingo();

			if (flag == 3) break;

			cout << "���ڸ� �����ϼ���(1~25) : ";
			cin >> num;
			numcheck();
			Bingocheck();
			printbingo();
		}
	} while (!(flag >= 3)); //���� 3���� ����� ����

}//game()



void makebingo() {
	int cnt = 1, a = 0, n = 5, ranx, rany;

	srand(time(NULL));

	cout << "������ ������ . . ." << endl;  //	cin >> n;
	Sleep(1000); //��� ���
	for (u = 0; u < 2; u++) {
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
	printbingo();
}

int rsp() {
	int answer = 0, com = 0;
	char* position[3] = { "����", "����", "��" };
	char* result[3][3] = { "���", "�й�", "�¸�", "�¸�", "���", "�й�", "�й�", "�¸�", "���" };
	srand(time(NULL));
	system("cls");

	cout << "���� ����! \n";
	cout << "������������ ������ ���մϴ�.\n";

	while (1) {
		cout << "����(0) | ����(1) | ��(2) �� �����ּ��� : ";
		cin >> answer;

		com = rand() % 3 ;

		if (!(answer>=0 && answer<3)) { //�Է¹��� �� Ȯ��
			cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n";
			cout << "--------------------------" << endl;
			continue;
		}

		cout << "��ǻ�� : " <<position[com] << ", ����� : " << position[answer] << "\n��� : " << result[answer][com] << "\n";
		Sleep(500);
		system("cls");

		if (answer == com) 	continue;
		else if (result[answer][com] == "�¸�") {
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
	cout << "����" <<endl;

	cout << "������ �����Ϸ��� �ƹ��ų� �����ּ���.";

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
		cout << "������ ã�� �� �����ϴ�." << endl;
	}

	cout << "�����Ϸ��� 1��, ���ӹ���� 2�� �����ּ��� : ";
	cin >> num;

	if (num == 2) 
		intro(); //����

	rsp(); //����
	
	makebingo(); //������ ����
	
	game(); //���� ����


	
}
