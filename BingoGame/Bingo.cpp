#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
using namespace std;

int board[5][5]; //�� ������
int cboard[5][5]; //��ǻ�� ������
int first = 0; //����
int num = 0;

void Bingocheck() {
	int zero;

	for (int i = 0; i < 5; i++) {
		zero = 0;
		for (int j = 0; j < 5; j++) {
			if (board[i][j] == 0) {
				zero++;
				if (zero == 5){
					cout << "����� !";
				}
			}
		} //for j
	} //for i



} //Bingocheck()


void numcheck() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (board[i][j] == num) { //num�� 0���� ����
				board[i][j] = 0;
			} //if
		} //for
	} //for

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (cboard[i][j] == num) { //num�� 0���� ����
				cboard[i][j] = 0;
			} //if
		} //for
	} //for
}

void cnumcheck() {
	int cnum = rand() % 25 + 1;

	cout << "��ǻ���� �� : " << cnum <<endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (cboard[i][j] == cnum) { //num�� 0���� ����
				cboard[i][j] = 0;
			} //if
		} //for
	} //for

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (board[i][j] == cnum) { //num�� 0���� ����
				board[i][j] = 0;
			} //if
		} //for
	} //for
}

void printbingo() {
	cout << "--------------------------" << endl;

	for (int i = 0; i < 5; i++) { //���
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

		cout << "���ڸ� �����ϼ���(1~25) : ";
		cin >> num;

		numcheck();
		Bingocheck();
		printbingo();

		cout << "��ǻ�� �����Դϴ�." << endl;
		Sleep(1000);
		cnumcheck();
		printbingo();

		

	}//while

}//game()



void makebingo() {
	int cnt = 1, a = 0, n = 5, ranx, rany;

	srand(time(NULL));

	cout << "������ ������ . . ." << endl;  //	cin >> n;
	Sleep(2000); //��� ���

	for (int i = 0; i < n; i++) { //���� �ֱ�
		for (int j = 0; j < n; j++) {
				board[i][j] = cnt++;
				cboard[i][j] = cnt;
		}
	}

	for (int i = 0; i < n; i++) { //�������� �ٽ� �ֱ�
		for (int j = 0; j < n; j++) {
			ranx = rand() % n; //����
			rany = rand() % n;
					
			a = board[i][j];
			board[i][j] = board[ranx][rany];
			board[ranx][rany] = a;

			ranx = rand() % n; //��ǻ�Ͳ�
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
			continue;
		}

		cout << "��ǻ�� : " <<position[com] << ", ����� : " << position[answer] << "\n��� : " << result[answer][com] << "\n";

		if (answer == com) 	continue;
		else if (result[answer][com] == "�̱�") {
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
	cout << "����";

	if ("������ �����Ϸ��� �ƹ��ų� �����ּ���.");
	//get

	Sleep(3000);
}

int main() {
	int num = 0;

	cout << "\n\n\n\n\n\n\n\n\n\n" << endl;

	cout << "�����Ϸ��� 1��, ���ӹ���� 2�� �����ּ��� : ";
	cin >> num;

	if (num == 2) 
		intro(); //����

	rsp(); //����
	
	makebingo(); //������ ����
	
	game(); //���� ����
	
}
