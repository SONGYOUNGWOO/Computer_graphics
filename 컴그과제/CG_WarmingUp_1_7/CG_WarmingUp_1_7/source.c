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

//����Ʈ�󿡼� ������ �ٷ� ���� ��� ����, ��尡 ������ NULL ����
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

//����Ʈ tail�� �ڿ� ������ ��� ����(�ش� ��尡 tail�� ��)
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

//����Ʈ�� �����Ҵ� ��.
list* make_list() {
	list* tmp = (list*)malloc(sizeof(list));

	tmp->n = 0;
	tmp->head = NULL;
	tmp->tail = NULL;

	return tmp;
}

//����Ʈ�� ��ü ��� ����
void delete_list(list* del) {
	if (del->n != 0) {
		node* target = del->tail;
		while (target = delete_last_node(del)) {}
	}
	//del->n = 0;	
}

//��ĭ �� �����鼭 ��Ʈ�� ����Ʈ�� �����.
list* make_route(list* route_list,int start_col,int start_row) {
	list* list = route_list;
	char pass[board_len][board_len];
	//(i,j)�� �鸮�� '0', �ȵ鸮�� '1'
	for (int i = 0; i < board_len; i++) {
		for (int j = 0; j < board_len; j++) {
			pass[i][j] = '1';
		}
	}	


	//ó�� �����ϴ� ��ǥ
	node* now = append_node(list, start_col, start_row);
	node* bf = NULL;

	//�ѹ������� 5ĭ �̻� ���ѿ� ����
	int last_move = 0;			//������ �̵��� ����
	int direction_continue = 0;	//������������ �� Ƚ��	

	//ù ������ǥ ����
	now->col = start_col;
	now->row = start_row;
	pass[start_col][start_row] = '0';

	//�����Ҷ� ���� �ݺ��ϵ���.
	while (!(now->col == board_len - 1&& now->row == board_len - 1)) {	
		node* last_node = now;
		//printf("��Ʈ ����: %d\n", list->n);
		//printf("���� ��ġ : (%d,%d)\n", now->col, now->row);
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
		//���� �̵� ���ɼ� üũ
		if (now->col - 1 >= 0 && pass[now->col - 1][now->row] == '1' && now->col - 1 != bf->col && !(last_move == 0 && direction_continue > 3) && !(last_move == 3 && direction_continue == 1) && !(last_move == 1 && direction_continue == 1)) {
			possible[possible_len++] = 0;			
		}		
		//�������� �̵� ���ɼ� üũ
		if (now->row + 1 <= board_len - 1 && pass[now->col][now->row + 1] == '1' && now->row + 1 != bf->row && !(last_move == 1 && direction_continue > 3) && !(last_move == 0 && direction_continue == 1) && !(last_move == 2 && direction_continue == 1)) {
			possible[possible_len++] = 1;
		}
		//�Ʒ��� �̵� ���ɼ� üũ
		if (now->col + 1 <= board_len - 1 && pass[now->col + 1][now->row] == '1' && now->col + 1 != bf->col && !(last_move == 2 && direction_continue > 3) && !(last_move == 1 && direction_continue == 1) && !(last_move == 3 && direction_continue == 1)) {
			possible[possible_len++] = 2;
		}
		//�������� �̵� ���ɼ� üũ
		if (now->row - 1 >= 0 && pass[now->col][now->row - 1] == '1' && now->row - 1 != bf->row && !(last_move == 3 && direction_continue > 3) && !(last_move == 2 && direction_continue == 1) && !(last_move == 0 && direction_continue == 1)) {
			possible[possible_len++] = 3;
		}
		//�̵� ������ ��ΰ� ������
		if (possible_len != 0) {
			int roll = rand() % possible_len;
			switch (possible[roll]) {
			case 0:	//��
				apply_col = -1;
				apply_row = 0;
				break;
			case 1:	//��
				apply_col = 0;
				apply_row = 1;
				break;
			case 2:	//��
				apply_col = 1;
				apply_row = 0;
				break;
			case 3:	//��
				apply_col = 0;
				apply_row = -1;
				break;
			}

			//�������� Ƚ�� �Ǵ�
			if (last_move == possible[roll]) {
				direction_continue++;
			}
			else {				
				direction_continue = 1;
			}		

			//���� ���� �ֽ�ȭ
			last_move = possible[roll];
			bf = now;
			now = append_node(list, now->col + apply_col, now->row + apply_row);
			pass[now->col][now->row] = '0';
		}
		//�̵���ΰ� ������
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

//���忡 ��Ʈ �׸���
void draw_route(char board[][board_len],list* list, node* obj) {
	node* route = list->head;
	//�� �ʱ�ȭ
	for (int i = 0; i < board_len; i++) {
		for (int j = 0; j < board_len; j++) {
			board[i][j] = '1';
		}
	}
	//����Ʈ�� ������ȸ�ϸ� ���� �׸�
	while (route != NULL) {
		board[route->col][route->row] = '0';
		route = route->next;
	}
	//������Ʈ �߰�
	if (obj != NULL) {
		board[obj->col][obj->row] = '*';
	}
}

//������Ʈ�� 1 - ������ , -1 - �ڷ�(����ġ�� ������)
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

//��Ʈ�� ȭ�鿡 �����.
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

//���� �ܼ�
void console() {
	srand(time(NULL));
	list* list = make_list(); // �����Ҵ�
	node* obj = NULL;	// �������� �ٴϴ� ���� ǥ���� ��ġ ������

	list = make_route(list, 0, 0); // �� �Լ��� ���� �տ�

	char board[board_len][board_len]; //��¿� ��(����)
	draw_route(board, list, obj); // ��¿� ������ �׸�

	while (1) {
		system("cls"); //�ܼ� â ����
		display_route(board); //�ֿܼ� ���� ���

		printf("��ɾ� ��� - enter : �� ��� Ž��, r: ��ο� ������Ʈ ����, +/- : ��ü�� ��ο� ���� ��/�ڷ� �̵�, q : ���α׷� ����\n");

		char ch = getch(); // enter�ʿ���� , ���۸� �����ʰ� �ٷ� �Է¹���
		switch (ch) {
		case '\r': // ����
			delete_list(list); // �����Ҵ��ѳ� �����
			list = make_route(list, 0, 0); // ��հ�
			obj = NULL;	//������Ʈ �ʱ�ȭ
			draw_route(board, list, obj); // ���� �׸���
			break;
		case 'r': case 'R': //������Ʈ ���� �� ������Ʈ ���ĭ����
			obj = list->head; // ���ĭ���� ����
			draw_route(board, list, obj); //������Ʈ�� ������ ���� �ٽñ׸�
			break;
		case '+': //�� ���� ��ĭ ����
			if (obj != NULL) {		//������Ʈ�� �������
				obj_move(board, &obj, 1);
			}
			break;
		case '-': //�� ���� ��ĭ ����
			if (obj != NULL) {		//������Ʈ�� �������
				obj_move(board, &obj, -1);
			}
			break;
		case 'q': case 'Q':
			return;			//main �����ٷ�
			break;
		}		
	}

}

int main() {
	console();
	return 0;
}