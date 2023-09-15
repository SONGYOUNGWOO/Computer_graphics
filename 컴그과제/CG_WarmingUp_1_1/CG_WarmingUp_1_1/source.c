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

		printf("1번 행렬\n");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf("%2d", map1[i][j]);
			}
			printf("\n");
		}

		printf("2번 행렬\n");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf("%2d", map2[i][j]);
			}
			printf("\n");
		}

		printf("----------\nOrderList\nm = 행렬의 곱셈\na = 행렬의 덧셈\nd = 행렬의 뺄셈\n1~9 = 스칼라곱\nr = 행열식의 값\nt = 전치행렬과 그 행렬식의 값\nh = 3x3행렬 4x4행렬로 변환 및 행렬식 값\ns = 행렬의 값을 새로 랜덤설정\nq = 프로그램 종료\n----------\n");
		printf("명령어 입력:");

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
			//행렬식 계산
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

			//행렬식 출력
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

			//행렬2식 계산
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

			//행렬2식 출력
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
			//행렬식 계산
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

			//행렬식 출력
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

			//행렬2식 계산
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

			//행렬2식 출력
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
			//행렬식 계산
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

			//행렬식 출력
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

			//행렬2식 계산
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

			//행렬2식 출력
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
				//행렬1 스칼라곱
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

				//행렬2 스칼라곱
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
				printf("해당 명령어가 존재하지 않음.\n");
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