#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct spot {
	int x, y, z;
	int vaild;	//1: ���� �������.
}spot;

//�������� �Ÿ� ����
float distance(spot* spot) {
	return sqrt((spot->x) * (spot->x) + (spot->y) * (spot->y) + (spot->z) * (spot->z));
}

//����Ʈ ���
void Display_list(spot list[]) {
	printf("--------------------------------------------- \n");
	for (int i = 9; i >= 0 ; i--) {
		printf("%d : ", i);
		if (list[i].vaild) {
			printf("%d %d %d", list[i].x, list[i].y, list[i].z);
		}
		printf("\n");
	}
}
//��ɾ� ��� ���
void orderlist_output() {
	printf("--------------------------------------------- \n");
	printf("+ x y z: ����Ʈ�� �� ���� �Է� (x, y, z: ����) \n");
	printf("-: ����Ʈ�� �� ������ �����Ѵ�.\n");
	printf("e x y z: ����Ʈ�� �� �Ʒ��� �Է� (��ɾ� +�� �ݴ��� ��ġ, ����Ʈ�� ����� �����Ͱ��� ���� �ö󰣴�.)\n");
	printf("d: ����Ʈ�� �� �Ʒ����� �����Ѵ�. (����Ʈ���� ������ ĭ�� ����ִ�.)\n");
	printf("l: ����Ʈ�� ����� ���� ������ ����Ѵ�.\n");
	printf("c: ����Ʈ�� ����. ����Ʈ�� ��� �� �ٽ� �Է��ϸ� 0������ ����ȴ�.\n");
	printf("m: �������� ���� �� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�,\n");
	printf("n: �������� ���� ����� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�.\n");
	printf("a: �������� �Ÿ��� �����Ͽ� ������������ �����Ͽ� ����Ѵ�. �ε��� 0������ �� ĭ���� �����Ͽ� ����Ѵ�.\n");
	printf("s: �������� �Ÿ��� �����Ͽ� ������������ �����Ͽ� ����Ѵ�. (�ٽ� a �Ǵ� s�� ������ ������ �ε��� ��ġ�� ����Ѵ�.)\n");
	printf("q: ���α׷��� �����Ѵ�.\n");
	printf("--------------------------------------------- \n");
}
//���� ����Ʈ ����
void save_origin_list(spot* destination, spot* origin) {
	for (int i = 0; i < 10; i++) {
		destination[i].x = origin[i].x;
		destination[i].y = origin[i].y;
		destination[i].z = origin[i].z;
		destination[i].vaild = origin[i].vaild;
	}
}

//����Ʈ ����(1: ��������, 2: ��������)
void sort_list(spot* list, int option, int* num) {
	spot sub_list[10];
	save_origin_list(sub_list,list);

	int count = 0;
	int index[10];
	float len[10];
	for (int i = 0; i < 10; i++) {
		if (list[i].vaild) {
			index[count] = i;
			len[count] = distance(&list[i]);
			count++;
		}
	}
	
	if (option == 1) {	//��������
		for (int i = 0; i < count; i++) {
			for (int j = i + 1; j < count; j++) {
				if (len[i] > len[j]) {
					int tmp = index[i];
					index[i] = index[j];
					index[j] = tmp;

					float tmp2 = len[i];
					len[i] = len[j];
					len[j] = tmp2;
				}
			}
		}
	}
	
	if (option == 2) {	//��������
		for (int i = 0; i < count; i++) {
			for (int j = i + 1; j < count; j++) {
				if (len[i] < len[j]) {
					int tmp = index[i];
					index[i] = index[j];
					index[j] = tmp;

					float tmp2 = len[i];
					len[i] = len[j];
					len[j] = tmp2;
				}
			}
		}
	}

	for (int i = 0; i < 10; i++) {		
		if (i < count) {
			list[i].x = sub_list[index[i]].x;
			list[i].y = sub_list[index[i]].y;
			list[i].z = sub_list[index[i]].z;
			list[i].vaild = sub_list[index[i]].vaild;
		}
		else {
			list[i].vaild = 0;
		}
	}


	*num = count;
}



void console() {
	//list* list = NULL;
	spot list[10];
	spot origin[10];
	int num = 0;
	int origin_num = 0;
	//����Ʈ ����
	int sorttype = 0;
	//for input
	char input;
	int x, y, z;	

	for (int i = 0; i < 10; i++) {
		list[i].x = -1;
		list[i].y = -1;
		list[i].z = -1;
		list[i].vaild = 0;
	}

	while (1) {
		printf("----------------------------------------------------------------------------------------\n");
		printf("+ x y z: ����Ʈ�� �� ���� �Է� (x, y, z: ����)\n");
		printf("- : ����Ʈ�� �� ������ �����Ѵ�.\n");
		printf("e x y z : ����Ʈ�� �� �Ʒ��� �Է�(��ɾ� + �� �ݴ��� ��ġ, ����Ʈ�� ����� �����Ͱ��� ���� �ö󰣴�.\n");
		printf("d : ����Ʈ�� �� �Ʒ����� �����Ѵ�. (����Ʈ���� ������ ĭ�� ����ִ�.)\n");
		printf("l : ����Ʈ�� ����� ���� ������ ����Ѵ�.\n");
		printf("c : ����Ʈ�� ����.����Ʈ�� ��� �� �ٽ� �Է��ϸ� 0������ ����ȴ�.\n");
		printf("m : �������� ���� �� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�.\n");
		printf("n : �������� ���� ����� �Ÿ��� �ִ� ���� ��ǥ���� ����Ѵ�.\n");
		printf("a : �������� �Ÿ��� �����Ͽ� ������������ �����Ͽ� ����Ѵ�.�ε��� 0������ �� ĭ���� �����Ͽ� ����Ѵ�.\n");
		printf("s : �������� �Ÿ��� �����Ͽ� ������������ �����Ͽ� ����Ѵ�. (�ٽ� a �Ǵ� s�� ������ ������ �ε��� ��ġ�� ����Ѵ�.)\n");
		printf("q : ���α׷��� �����Ѵ�.\n");		
		printf("----------------------------------------------------------------------------------------\n");

		printf("��ɾ� �Է�:");

		scanf(" %c", &input);
		switch (input) {
		case '+':
			scanf("%d %d %d", &x, &y, &z);		
			int vari = -1;
			int write = 0;
			for (int i = 9; i >= 0; i--) {
				if (list[i].vaild) {					
					if (vari != -1) {
						list[vari].x = x;
						list[vari].y = y;
						list[vari].z = z;
						list[vari].vaild = 1;
						num++;
						write = 1;
						break;
					}					
				}		
				else {
					vari = i;
				}
			}		
			if (vari == 0 && write == 0) {
				list[vari].x = x;
				list[vari].y = y;
				list[vari].z = z;
				list[vari].vaild = 1;
				num++;
			}
			orderlist_output();
			break;
		case '-':		
			for (int i = 9; i >= 0; i--) {
				if (list[i].vaild) {
					list[i].vaild = 0;
					num--;
					break;
				}
			}		
			orderlist_output();
			break;
		case 'e': case 'E':
			scanf("%d %d %d", &x, &y, &z);
			for (int i = 8; i >= 0; i--) {
				list[i + 1].x = list[i].x;
				list[i + 1].y = list[i].y;
				list[i + 1].z = list[i].z;
				list[i + 1].vaild = list[i].vaild;
				
			}
			list[0].x = x;
			list[0].y = y;
			list[0].z = z;
			list[0].vaild = 1;
			num++;
			orderlist_output();
			break;
		case 'd': case 'D':
			for (int i = 0; i <= 9; i++) {
				if (list[i].vaild) {
					list[i].vaild = 0;
					num--;
					break;
				}
			}			
			orderlist_output();
			break;
		case 'l': case 'L':
			x = 0;
			for (int i = 0; i <= 9; i++) {
				if (list[i].vaild) {
					x++;
					break;
				}
			}
			printf("����Ʈ ����: %d\n", x);
			break;
		case 'c': case 'C':
			for (int i = 0; i <= 9; i++) {				
				list[i].vaild = 0;				
			}
			num = 0;
			orderlist_output();
			break;
		case 'm': case 'M':
			x = distance(&list[0]);
			for (int i = 1; i <= 9; i++) {
				if (list[i].vaild) {
					if (distance(&list[i]) > x) {
						x = i;
					}
				}
			}
			printf("�������� ���� �� �Ÿ��� �ִ� ���� ��ǥ��: (%d, %d, %d)\n", list[x].x, list[x].y, list[x].z);
			break;
		case 'n': case 'N':
			x = distance(&list[0]);
			for (int i = 1; i <= 9; i++) {
				if (list[i].vaild) {
					if (distance(&list[i]) < x) {
						x = i;
					}
				}
			}
			printf("�������� ���� ����� �Ÿ��� �ִ� ���� ��ǥ��: (%d, %d, %d)\n", list[x].x, list[x].y, list[x].z);		
			break;
		case 'a': case 'A':
			if (sorttype == 0) {
				save_origin_list(origin, list);
				origin_num = num;
				sort_list(list, 1, &num);
				sorttype = 1;
			}
			else if (sorttype == 1) {
				save_origin_list(list, origin);
				num = origin_num;
				sorttype = 0;
			}
			else {
				sort_list(list, 1, &num);
				sorttype = 1;
			}
			break;
		case 's': case 'S':
			if (sorttype == 0) {
				save_origin_list(origin, list);
				origin_num = num;
				sort_list(list, 2, &num);
				sorttype = 2;
			}
			else if (sorttype == 2) {
				save_origin_list(list, origin);
				num = origin_num;
				sorttype = 0;
			}
			else {
				sort_list(list, 2, &num);
				sorttype = 2;
			}
			break;
		case 'q': case 'Q':
			return;
			break;
		default:
			printf("�ش� ��� �������� �ʽ��ϴ�.\n");
			break;
		}
		Display_list(list);
	}
}


int main() {
	console();

	return 0;
}
