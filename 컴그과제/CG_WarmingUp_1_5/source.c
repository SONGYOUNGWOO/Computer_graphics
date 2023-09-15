#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>

typedef struct board {
	char character;
	int open;
}board;

typedef struct cursor {
	int col, row;	
}cursor;

void board_display(board board[][4],cursor cursor) {
	printf("%2c%2c%2c%2c%2c\n", ' ', 'a', 'b', 'c', 'd');
	for (int i = 0; i < 4; i++) {
		printf("%2d",i+1);
		for (int j = 0; j < 4; j++) {
			if (cursor.col == i && cursor.row == j) {
				if (board[i][j].open) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), board[i][j].character - 'A' + 1);
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
				printf("%2c", 'o');
			}
			else if (board[i][j].open) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), board[i][j].character-'A' + 1);
				printf("%2c", board[i][j].character);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("%2c", '*');
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("\n");
}

void board_opendisplay(board board[][4]) {
	printf("%2c%2c%2c%2c%2c\n", ' ', 'a', 'b', 'c', 'd');
	for (int i = 0; i < 4; i++) {
		printf("%2d", i+1);
		for (int j = 0; j < 4; j++) {						
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), board[i][j].character - 'A' + 1);
			printf("%2c", board[i][j].character);			
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("\n");
}

void reset_board(board board[][4]) {
	char Alpha[8] = { 'A' , 'B' ,  'C' ,  'D' ,  'E' ,  'F' ,  'G' ,  'H' };

	int count[8];
	for (int i = 0; i < 8; i++) {
		count[i] = 0;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int tmp = rand() % 8;
			while (1) {
				if (count[tmp] < 2) {
					board[i][j].character = Alpha[tmp];
					board[i][j].open = 0;
					count[tmp]++;
					break;
				}
				else {
					tmp++;
					tmp %= 8;
				}
			}
		}
	}
}

void curcpy(cursor* Destination, cursor* source) {
	Destination->col = source->col;
	Destination->row = source->row;
}

void reset_cursor(cursor* source) {
	source->col = 0;
	source->row = 0;
}

int comparecard(board board[][4],cursor* card1, cursor* card2) {
	if (board[card1->col][card1->row].character == board[card2->col][card2->row].character) {
		return 1;
	}
	else {
		return 0;
	}
}

void console() {
	board board[4][4];
	int turn = 0;
	int score = 0;
	cursor tmp = { -1,-1 };
	cursor blank = { -1,-1 };
	cursor select1;
		select1.col = 0;
		select1.row = 0;
	cursor select2;
		select2.col = 0;
		select2.row = 0;
	cursor* cursor = &select1;	
	int selectcard = 0;
	srand(time(NULL));

	reset_board(board);	

	while (1) {
		while (turn < 12 && score < 800) {
			system("cls");
			//보드 출력
			board_display(board, *cursor);
			//첫번째 카드 관련
			printf("input card 1: %c%d", select1.row + 'a', select1.col + 1);
			if (selectcard == 0)
				printf("  <<");
			printf("\n");
			//두번째 카드 관련
			printf("input card 2: %c%d", select2.row + 'a', select2.col + 1);
			if (selectcard == 1)
				printf("  <<");
			printf("\n");
			//조작키 및 남은 기회와 점수 출력
			printf("Move key: w - up, a - left, s - down, d - right/ r - restart, q - quit\n");
			printf("현재 턴: %d, 남은 턴: %d\n", turn + 1, 11 - turn);
			printf("현재 점수: %d\n", score);

			//현재 선택한 카드수 조건문
			if (selectcard != 2) {	//두 격자를 고르기 전이라면
				char ch = getch();	//입력받는다.
				if (ch == 'w' || ch == 'W') {
					if (cursor->col > 0)
						cursor->col--;
				}
				if (ch == 'a' || ch == 'A') {
					if (cursor->row > 0)
						cursor->row--;
				}
				if (ch == 's' || ch == 'S') {
					if (cursor->col < 3)
						cursor->col++;
				}
				if (ch == 'd' || ch == 'D') {
					if (cursor->row < 3)
						cursor->row++;
				}
				if (ch == '\r' && board[cursor->col][cursor->row].open != 1) {
					if (selectcard == 0) {
						board[cursor->col][cursor->row].open = 1;
						if (cursor->col == 0 && cursor->row == 0)
							select2.row++;
						curcpy(&select2, &select1);
						cursor = &select2;

					}
					else if (selectcard == 1) {
						board[cursor->col][cursor->row].open = 1;
						curcpy(&tmp, &select2);
						cursor = &blank;
					}
					selectcard++;
				}
				if (ch == 'r' || ch == 'R') {
					turn = 0;
					score = 0;
					reset_board(board);
					//기존 커서 초기화
					reset_cursor(&select1);
					reset_cursor(&select2);
					cursor = &select1;
					selectcard = 0;
				}
				if (ch == 'q' || ch == 'Q') {
					return;
				}
			}
			else {	//두 격자를 선택한다면
				if (comparecard(board, &select1, &select2)) {	//두 격자의 글자가 같다면.
					score += 100;
				}
				else {
					_sleep(1000);
					board[select1.col][select1.row].open = 0;
					board[select2.col][select2.row].open = 0;
				}
				//기존 커서 초기화
				reset_cursor(&select1);
				reset_cursor(&select2);
				curcpy(&select1, &tmp);
				cursor = &select1;
				selectcard = 0;

				//turn 증가
				turn++;
			}			
		}
		system("cls");

		if (score < 800) {
			printf("--------정답지--------\n");
			board_opendisplay(board);
			printf("----------------------\n");
		}

		//보드 출력
		board_display(board, *cursor);

		printf("남은 턴: %d, 최종 점수: %d점\n", 12 - turn, score);
		printf("카드 짝 맞추기 게임을 다시 하시겠습니까? (R - 재시작/ Q - 종료):");
		char input;
		scanf(" %c", &input);
		if (input == 'r' || input == 'R') {
			turn = 0;
			score = 0;
			reset_board(board);		

			//기존 커서 초기화
			reset_cursor(&select1);
			reset_cursor(&select2);
			cursor = &select1;
			selectcard = 0;
		}
		if (input == 'q' || input == 'Q') {
			break;
		}
	}
}


int main() {
	console();
	return 0;
}