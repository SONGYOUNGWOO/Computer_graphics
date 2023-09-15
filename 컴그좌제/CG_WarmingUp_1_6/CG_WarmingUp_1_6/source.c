#include<stdio.h>
#include<stdlib.h>

#define board_size 30

typedef struct coord {
	int x, y, length, height;
}coord;
//보드 초기화
void reset_board(char board[][board_size]) {	
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			board[i][j] = '.';
		}
	}
}

void input_coord(coord* coord) {
	printf("Input coord value: ");
	while (1) {
		scanf("%d %d %d %d", &coord->x, &coord->y, &coord->length, &coord->height);
		while (getchar() != '\n');
		if (coord->height != 0) {
			//가로
			if (coord->x > coord->length) {
				coord->length = coord->x - coord->length;
			}
			else {
				coord->length -= coord->x;
			}
			//세로
			if (coord->y > coord->height) {				
				coord->height = coord->y - coord->height;
			}
			else {
				coord->height -= coord->y;
			}
			break;
		}
		
	}
}

void board_display(coord* coord) {
	int left = coord->x;
	int top = coord->y;
	int right = left;
	for (int i = 0; i < coord->length; i++) {
		right++;
		right %= board_size;
	}
	int bottom = top;	
	for (int i = 0; i < coord->height; i++) {
		bottom++;
		bottom %= board_size;
	}


	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			if (left < right) {
				if (top < bottom) {
					if (left <= j && j <= right && top <= i && i <= bottom) {
						printf("%2c", '0');
					}
					else {
						printf("%2c", '.');	//default
					}
				}
				else if (top > bottom) {
					if (left <= j && j <= right && (top <= i || i <= bottom)) {
						printf("%2c", '0');
					}
					else {
						printf("%2c", '.');	//default
					}
				}		
				else {
					if (left <= j && j <= right && (top == i)) {
						printf("%2c", '0');
					}
					else {
						printf("%2c", '.');	//default
					}
				}
			}
			else if (left > right) {
				if (top < bottom) {
					if ((left <= j || j <= right) && top <= i && i <= bottom) {
						printf("%2c", '0');
					}
					else {
						printf("%2c", '.');	//default
					}
				}
				else if (top > bottom) {
					if ((left <= j || j <= right) && (top < i || i < bottom)) {
						printf("%2c", '0');
					}
					else {
						printf("%2c", '.');	//default
					}
				}
				else {
					if ((left <= j || j <= right) && (top == i)) {
						printf("%2c", '0');
					}
					else {
						printf("%2c", '.');	//default
					}
				}
			}
			else {
				if (top < bottom) {
					if (left == j && top <= i && i <= bottom) {
						printf("%2c", '0');
					}
					else {
						printf("%2c", '.');	//default
					}
				}
				else if (top > bottom) {
					if (left == j && (top < i || i < bottom)) {
						printf("%2c", '0');
					}
					else {
						printf("%2c", '.');	//default
					}
				}
				else {
					if (left == j && (top == i)) {
						printf("%2c", '0');
					}
					else {
						printf("%2c", '.');	//default
					}
				}
			}
			//printf("%2c", '.');	//default
		}
		printf("\n");
	}
}

void console() {	
	coord coord;	
	char input;
	input_coord(&coord);
	while (1) {
		board_display(&coord);
		printf("명령어 입력:");
		scanf(" %c", &input);
		switch (input) {
		case 'x':
			if (coord.x < board_size - 1) {
				coord.x++;
			}
			else {
				coord.x = 0;
			}
			break;
		case 'X':
			if (coord.x > 0) {
				coord.x--;
			}
			else {
				coord.x = board_size - 1;
			}
			break;
		case 'y':
			if (coord.y < board_size - 1) {
				coord.y++;
			}
			else {
				coord.y = 0;
			}
			break;
		case 'Y':
			if (coord.y > 0) {
				coord.y--;
			}
			else {
				coord.y = board_size - 1;
			}
			break;
		case 's':			
			if(coord.length > 0)
				coord.length--;
			if (coord.height > 0)
				coord.height--;
			break;
		case 'S':
			if (coord.x + coord.length < board_size - 1)
				coord.length++;
			if (coord.y + coord.height < board_size - 1)
				coord.height++;
			break;
		case 'i':
			if (coord.length > 0)
				coord.length--;			
			break;
		case 'j':
			if (coord.height > 0)
				coord.height--;
			break;
		case 'k':
			if (coord.x + coord.length < board_size - 1)
				coord.length++;			
			break;
		case 'l':
			if (coord.y + coord.height < board_size - 1)
				coord.height++;
			break;
		case 'r': case 'R':	//리셋
			input_coord(&coord);
			break;		
		case 'q': case 'Q':	//종료
			return;
			break;
		}

	}

}

int main() {
	console();
	return 0;
}