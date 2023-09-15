#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

void console() {
	int map1[3][3];
	int map2[3][3];
	
	srand(time(NULL));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			map1[i][j] = rand() % 3;
			map2[i][j] = rand() % 3;
		}
	}

	

	while (1) {
		char input;

		printf("1�� ���\n");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf("%2d", map1[i][j]);
			}
			printf("\n");
		}

		printf("2�� ���\n");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf("%2d", map2[i][j]);
			}
			printf("\n");
		}

		printf("----------\nOrderList\nm = ����� ����\na = ����� ����\nd = ����� ����\n1~9 = ��Į���\nr = �࿭���� ��\nt = ��ġ��İ� �� ��Ľ��� ��\nh = 3x3��� 4x4��ķ� ��ȯ �� ��Ľ� ��\ns = ����� ���� ���� ��������\nq = ���α׷� ����\n----------\n");
		printf("��ɾ� �Է�:");

		scanf(" %c",&input);
		
		switch (input) {
		case 'm':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%2d", map1[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 3; j++) {
					printf("%2d", map2[i][j]);
				}
				printf("\t");

				if(i == 1)
					printf("=");

				printf("\t");
				
				for (int j = 0; j < 3; j++) {
					int a = 0;
					for (int k = 0; k < 3; k++) {
						int tmp = map1[i][k] * map2[k][j];
						a += tmp;
					}
					printf("%2d", a);
				}		

				printf("\n");
			}
			break;
		case 'a':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%2d", map1[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 3; j++) {
					printf("%2d", map2[i][j]);
				}
				printf("\t");

				if (i == 1)
					printf("=");

				printf("\t");
				for (int j = 0; j < 3; j++) {					
					printf("%2d", map1[i][j] + map2[i][j]);
				}

				printf("\n");
			}
			break;
		case 'd':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%2d", map1[i][j]);
				}
				printf("\t");

				for (int j = 0; j < 3; j++) {
					printf("%2d", map2[i][j]);
				}
				printf("\t");

				if (i == 1)
					printf("=");

				printf("\t");
				for (int j = 0; j < 3; j++) {					
					printf("%2d", map1[i][j] - map2[i][j]);
				}

				printf("\n");
			}
			break;		
		case 'r':
			//��Ľ� ���
			input = 0;
			int sum = 0;
			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map1[j][line++];
					line %= 3;
				}				
				sum += tmp;
			}

			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map1[j][2-line];
					line++;
					line %= 3;
				}
				sum -= tmp;
			}

			//��Ľ� ���
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%2d", map1[i][j]);
				}

				if (i == 1) {
					printf(" = %2d",sum);
				}
				printf("\n");
			}
			printf("\n");

			//���2�� ���
			sum = 0;
			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map2[j][line++];
					line %= 3;
				}
				sum += tmp;
			}

			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map2[j][2 - line];
					line++;
					line %= 3;
				}
				sum -= tmp;
			}

			//���2�� ���
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%2d", map2[i][j]);
				}

				if (i == 1) {
					printf(" = %2d", sum);
				}
				printf("\n");
			}
			break;
		case 't':
			//��Ľ� ���
			input = 0;
			sum = 0;
			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map1[j][line++];
					line %= 3;
				}
				sum += tmp;
			}

			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map1[j][2 - line];
					line++;
					line %= 3;
				}
				sum -= tmp;
			}

			//��Ľ� ���
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%2d", map1[j][i]);
				}

				if (i == 1) {
					printf(" = %2d", sum);
				}
				printf("\n");
			}
			printf("\n");

			//���2�� ���
			sum = 0;
			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map2[j][line++];
					line %= 3;
				}
				sum += tmp;
			}

			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map2[j][2 - line];
					line++;
					line %= 3;
				}
				sum -= tmp;
			}

			//���2�� ���
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%2d", map2[j][i]);
				}

				if (i == 1) {
					printf(" = %2d", sum);
				}
				printf("\n");
			}
			break;
		case 'h':
			//��Ľ� ���
			input = 0;
			sum = 0;
			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map1[j][line++];
					line %= 3;
				}
				sum += tmp;
			}

			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map1[j][2 - line];
					line++;
					line %= 3;
				}
				sum -= tmp;
			}

			//��Ľ� ���
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%2d", map1[i][j]);
				}
				printf(" 0");

				if (i == 1) {
					printf(" = %2d", sum);
				}
				printf("\n");
			}
			printf(" 0 0 0 1");
			printf("\n\n");

			//���2�� ���
			sum = 0;
			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map2[j][line++];
					line %= 3;
				}
				sum += tmp;
			}

			for (int i = 0; i < 3; i++) {
				int tmp = 1;
				int line = i;
				for (int j = 0; j < 3; j++) {
					tmp *= map2[j][2 - line];
					line++;
					line %= 3;
				}
				sum -= tmp;
			}

			//���2�� ���
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%2d", map2[i][j]);					
				}
				printf(" 0");

				if (i == 1) {
					printf(" = %2d", sum);
				}
				printf("\n");
			}
			printf(" 0 0 0 1");
			break;
		case 's':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					map1[i][j] = rand() % 3;
					map2[i][j] = rand() % 3;
				}
			}
			break;
		case 'q':
			return;

			break;	
		default:
			if ('0' < input && input <= '9') {
				//���1 ��Į���
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						printf("%2d", map1[i][j]);
					}					
					printf("\t");

					if (i == 1)
						printf(" * %2d =", input - 48);

					printf("\t");
					for (int j = 0; j < 3; j++) {
						printf("%2d", map1[i][j]* (input-48));
					}

					printf("\n");
				}
				printf("\n");

				//���2 ��Į���
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						printf("%2d", map2[i][j]);
					}
					printf("\t");

					if (i == 1)
						printf(" * %2d =", input - 48);

					printf("\t");
					for (int j = 0; j < 3; j++) {
						printf("%2d", map2[i][j] * (input - 48));
					}

					printf("\n");
				}
			}
			else {
				printf("�ش� ��ɾ �������� ����.\n");
			}
			break;
		}		
		printf("\n");

	}
}

int main() {
	console();

	return 0;
}