#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>

#define board_len 50

typedef struct node {
	int col, row;
	struct node* next;
	struct node* prior;
}node;

typedef struct list {
	node* head;
	node* tail;
	int n;
}list;

//리스트상에서 마지막 바로 직전 노드 리턴, 노드가 없을시 NULL 리턴
node* delete_last_node(list* list) {	
	struct node* del = list->tail;
	struct node* last = del;
	if (last->prior != NULL) {
		last = last->prior;
		list->tail = last;
		last->next = NULL;
	}
	else {
		list->head = NULL;
		list->tail = NULL;
		last = NULL;
	}
	free(del);
	list->n--;
	return last;
}

//리스트 tail의 뒤에 생성된 노드 리턴(해당 노드가 tail이 됨)
node* append_node(list* list,int col, int row) {
	node* tmp = (node*)malloc(sizeof(node));
	tmp->col = col;
	tmp->row = row;

	if (list->head == NULL) {
		list->head = tmp;
		list->tail = tmp;
		tmp->prior = NULL;
		tmp->next = NULL;
	}
	else {
		tmp->prior = list->tail;
		tmp->next = NULL;
		list->tail->next = tmp;
		list->tail = tmp;
	}
	list->n++;

	return tmp;
}

//리스트를 동적할당 함.
list* make_list() {
	list* tmp = (list*)malloc(sizeof(list));

	tmp->n = 0;
	tmp->head = NULL;
	tmp->tail = NULL;

	return tmp;
}

//리스트속 전체 노드 삭제
void delete_list(list* del) {
	if (del->n != 0) {
		node* target = del->tail;
		while (target = delete_last_node(del)) {}
	}
	//del->n = 0;	
}

//한칸 씩 지나면서 루트를 리스트에 기록함.
list* make_route(list* route_list,int start_col,int start_row) {
	list* list = route_list;
	char pass[board_len][board_len];
	//(i,j)에 들리면 '0', 안들리면 '1'
	for (int i = 0; i < board_len; i++) {
		for (int j = 0; j < board_len; j++) {
			pass[i][j] = '1';
		}
	}	


	//처음 시작하는 좌표
	node* now = append_node(list, start_col, start_row);
	node* bf = NULL;

	//한방향으로 5칸 이상 제한용 변수
	int last_move = 0;			//직전에 이동항 방향
	int direction_continue = 0;	//같은방향으로 간 횟수	

	//첫 시작좌표 설정
	now->col = start_col;
	now->row = start_row;
	pass[start_col][start_row] = '0';

	//도착할때 까지 반복하도록.
	while (!(now->col == board_len - 1&& now->row == board_len - 1)) {	
		node* last_node = now;
		//printf("루트 길이: %d\n", list->n);
		//printf("현재 위치 : (%d,%d)\n", now->col, now->row);
		int possible[4] = { 0,0,0,0 };
		int possible_len = 0;
		int apply_col = 0;
		int apply_row = 0;
		node tmp;
			tmp.col = -1;
			tmp.row = -1;
		if (bf == NULL) { 
			bf = &tmp;
		}
		//위로 이동 가능성 체크
		if (now->col - 1 >= 0 && pass[now->col - 1][now->row] == '1' && now->col - 1 != bf->col && !(last_move == 0 && direction_continue > 3) && !(last_move == 3 && direction_continue == 1) && !(last_move == 1 && direction_continue == 1)) {
			possible[possible_len++] = 0;			
		}		
		//우측으로 이동 가능성 체크
		if (now->row + 1 <= board_len - 1 && pass[now->col][now->row + 1] == '1' && now->row + 1 != bf->row && !(last_move == 1 && direction_continue > 3) && !(last_move == 0 && direction_continue == 1) && !(last_move == 2 && direction_continue == 1)) {
			possible[possible_len++] = 1;
		}
		//아래로 이동 가능성 체크
		if (now->col + 1 <= board_len - 1 && pass[now->col + 1][now->row] == '1' && now->col + 1 != bf->col && !(last_move == 2 && direction_continue > 3) && !(last_move == 1 && direction_continue == 1) && !(last_move == 3 && direction_continue == 1)) {
			possible[possible_len++] = 2;
		}
		//좌측으로 이동 가능성 체크
		if (now->row - 1 >= 0 && pass[now->col][now->row - 1] == '1' && now->row - 1 != bf->row && !(last_move == 3 && direction_continue > 3) && !(last_move == 2 && direction_continue == 1) && !(last_move == 0 && direction_continue == 1)) {
			possible[possible_len++] = 3;
		}
		//이동 가능한 경로가 있을시
		if (possible_len != 0) {
			int roll = rand() % possible_len;
			switch (possible[roll]) {
			case 0:	//상
				apply_col = -1;
				apply_row = 0;
				break;
			case 1:	//우
				apply_col = 0;
				apply_row = 1;
				break;
			case 2:	//하
				apply_col = 1;
				apply_row = 0;
				break;
			case 3:	//좌
				apply_col = 0;
				apply_row = -1;
				break;
			}

			//같은방향 횟수 판단
			if (last_move == possible[roll]) {
				direction_continue++;
			}
			else {				
				direction_continue = 1;
			}		

			//각종 변수 최신화
			last_move = possible[roll];
			bf = now;
			now = append_node(list, now->col + apply_col, now->row + apply_row);
			pass[now->col][now->row] = '0';
		}
		//이동경로가 없을시
		else {
			pass[now->col][now->row] = '2';
			now = delete_last_node(list);
			if (bf != NULL) {
				if (bf->prior != NULL)
					bf = bf->prior;
				else {
					bf = NULL;
				}
			}

			if (list->head == NULL)	{
				for (int i = 0; i < board_len; i++) {
					for (int j = 0; j < board_len; j++) {
						pass[i][j] = '1';
					}
				}
				now = append_node(list, start_col, start_row);

				pass[start_col][start_row] = '0';
				bf = NULL;
				now->col = start_col;
				now->row = start_row;
			}			
		}

		if (list->n == 0) {
			int a = 0;
		}

	}
	return list;
}

//보드에 루트 그리기
void draw_route(char board[][board_len],list* list, node* obj) {
	node* route = list->head;
	//맵 초기화
	for (int i = 0; i < board_len; i++) {
		for (int j = 0; j < board_len; j++) {
			board[i][j] = '1';
		}
	}
	//리스트를 순차순회하며 길을 그림
	while (route != NULL) {
		board[route->col][route->row] = '0';
		route = route->next;
	}
	//오브젝트 추가
	if (obj != NULL) {
		board[obj->col][obj->row] = '*';
	}
}

//오브젝트를 1 - 앞으로 , -1 - 뒤로(맵위치도 조정됨)
void obj_move(char board[][board_len], node** obj, int direction) {
	node* object = *obj;
	if (direction == 1) {
		if (object->next != NULL) {
			board[object->col][object->row] = '#';
			object = object->next;
			board[object->col][object->row] = '*';
		}
	}
	if (direction == -1) {
		if (object->prior != NULL) {
			board[object->col][object->row] = '0';
			object = object->prior;
			board[object->col][object->row] = '*';
		}
	}
	*obj = object;
}

//루트를 화면에 출력함.
void display_route(char board[][board_len]) {
	printf("----------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < board_len; i++) {
		for (int j = 0; j < board_len; j++) {	
			if (board[i][j] == '*') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			}
			else if (board[i][j] == '0') {				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (board[i][j] == '#') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

			}
			printf("%2c", board[i][j]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		printf("\n");
	}
	printf("----------------------------------------------------------------------------------------------------\n");
	printf("\n");
}

//통제 콘솔
void console() {
	srand(time(NULL));
	list* list = make_list(); // 동적할당
	node* obj = NULL;	// 길을따라 다니는 놈을 표현할 위치 포인터

	list = make_route(list, 0, 0); // 이 함수가 길을 뚫움

	char board[board_len][board_len]; //출력용 길(지도)
	draw_route(board, list, obj); // 출력용 지도를 그림

	while (1) {
		system("cls"); //콘솔 창 비우기
		display_route(board); //콘솔에 지도 출력

		printf("명령어 목록 - enter : 새 경로 탐색, r: 경로에 오브젝트 생성, +/- : 객체를 경로에 따라 앞/뒤로 이동, q : 프로그램 종료\n");

		char ch = getch(); // enter필요없이 , 버퍼를 쓰지않고 바로 입력받음
		switch (ch) {
		case '\r': // 엔터
			delete_list(list); // 동적할당한놈 지우기
			list = make_route(list, 0, 0); // 길뚫고
			obj = NULL;	//오브젝트 초기화
			draw_route(board, list, obj); // 지도 그리고
			break;
		case 'r': case 'R': //오브젝트 생성 및 오브젝트 출발칸으로
			obj = list->head; // 출발칸으로 세팅
			draw_route(board, list, obj); //오브젝트를 포함한 지도 다시그림
			break;
		case '+': //길 따라서 한칸 전진
			if (obj != NULL) {		//오브젝트가 있을경우
				obj_move(board, &obj, 1);
			}
			break;
		case '-': //길 따라서 한칸 후진
			if (obj != NULL) {		//오브젝트가 있을경우
				obj_move(board, &obj, -1);
			}
			break;
		case 'q': case 'Q':
			return;			//main 다음줄로
			break;
		}		
	}

}

int main() {
	console();
	return 0;
}