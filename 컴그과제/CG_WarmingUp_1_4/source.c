#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct spot {
	int x, y, z;
	int vaild;	//1: 값이 들어있음.
}spot;

//원점과의 거리 공식
float distance(spot* spot) {
	return sqrt((spot->x) * (spot->x) + (spot->y) * (spot->y) + (spot->z) * (spot->z));
}

//리스트 출력
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
//명령어 목록 출력
void orderlist_output() {
	printf("--------------------------------------------- \n");
	printf("+ x y z: 리스트의 맨 위에 입력 (x, y, z: 숫자) \n");
	printf("-: 리스트의 맨 위에서 삭제한다.\n");
	printf("e x y z: 리스트의 맨 아래에 입력 (명령어 +와 반대의 위치, 리스트에 저장된 데이터값이 위로 올라간다.)\n");
	printf("d: 리스트의 맨 아래에서 삭제한다. (리스트에서 삭제된 칸이 비어있다.)\n");
	printf("l: 리스트에 저장된 점의 개수를 출력한다.\n");
	printf("c: 리스트를 비운다. 리스트를 비운 후 다시 입력하면 0번부터 저장된다.\n");
	printf("m: 원점에서 가장 먼 거리에 있는 점의 좌표값을 출력한다,\n");
	printf("n: 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력한다.\n");
	printf("a: 원점과의 거리를 정렬하여 오름차순으로 정렬하여 출력한다. 인덱스 0번부터 빈 칸없이 저장하여 출력한다.\n");
	printf("s: 원점과의 거리를 정렬하여 내림차순으로 정렬하여 출력한다. (다시 a 또는 s를 누르면 원래의 인덱스 위치에 출력한다.)\n");
	printf("q: 프로그램을 종료한다.\n");
	printf("--------------------------------------------- \n");
}
//기존 리스트 저장
void save_origin_list(spot* destination, spot* origin) {
	for (int i = 0; i < 10; i++) {
		destination[i].x = origin[i].x;
		destination[i].y = origin[i].y;
		destination[i].z = origin[i].z;
		destination[i].vaild = origin[i].vaild;
	}
}

//리스트 정렬(1: 오름차순, 2: 내림차순)
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
	
	if (option == 1) {	//오름차순
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
	
	if (option == 2) {	//내림차순
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
	//리스트 선택
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
		printf("+ x y z: 리스트의 맨 위에 입력 (x, y, z: 숫자)\n");
		printf("- : 리스트의 맨 위에서 삭제한다.\n");
		printf("e x y z : 리스트의 맨 아래에 입력(명령어 + 와 반대의 위치, 리스트에 저장된 데이터값이 위로 올라간다.\n");
		printf("d : 리스트의 맨 아래에서 삭제한다. (리스트에서 삭제된 칸이 비어있다.)\n");
		printf("l : 리스트에 저장된 점의 개수를 출력한다.\n");
		printf("c : 리스트를 비운다.리스트를 비운 후 다시 입력하면 0번부터 저장된다.\n");
		printf("m : 원점에서 가장 먼 거리에 있는 점의 좌표값을 출력한다.\n");
		printf("n : 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력한다.\n");
		printf("a : 원점과의 거리를 정렬하여 오름차순으로 정렬하여 출력한다.인덱스 0번부터 빈 칸없이 저장하여 출력한다.\n");
		printf("s : 원점과의 거리를 정렬하여 내림차순으로 정렬하여 출력한다. (다시 a 또는 s를 누르면 원래의 인덱스 위치에 출력한다.)\n");
		printf("q : 프로그램을 종료한다.\n");		
		printf("----------------------------------------------------------------------------------------\n");

		printf("명령어 입력:");

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
			printf("리스트 길이: %d\n", x);
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
			printf("원점에서 가장 먼 거리에 있는 점의 좌표값: (%d, %d, %d)\n", list[x].x, list[x].y, list[x].z);
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
			printf("원점에서 가장 가까운 거리에 있는 점의 좌표값: (%d, %d, %d)\n", list[x].x, list[x].y, list[x].z);		
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
			printf("해당 명렁어가 존재하지 않습니다.\n");
			break;
		}
		Display_list(list);
	}
}


int main() {
	console();

	return 0;
}
