#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//파일 입력 함수
char* getString(const char* fileName) {
	char* str = (char*)malloc(sizeof(char) * 800);
	FILE* fp = fopen(fileName, "rt");

	int len = 0;
	if (fp == NULL) {
		printf("파일 열기 실패\n");
		return NULL;
	}
	char* strp = str;
	while (1) {
		if (feof(fp) != 0) {
			*strp = '\0';		
			break;
		}
		*strp = fgetc(fp);
		printf("%c", *strp);
		if (*strp < 0) {
			*strp = '\0';
			break;
		}
		strp++;
		len++;
	}
	char* optimizition = (char*)malloc(sizeof(char) * len);
	strcpy(optimizition, str);
	free(str);
	return optimizition;
}

// 문장 전체를 뒤집기
void reverseString(char* str) {
	int len = strlen(str);
	for (int i = 0; i < len / 2; i++) {
		char tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
	}
	return;
}

//3글자 사이에 글자 삽입/삭제
void insertLetter(char** str,int check) {
	char* origin = *str;
	int len = strlen(origin);	

	char* result = (char*)malloc(sizeof(char) * (len * 2 + 1));

	int i = 0; 
	int j = 0; 

	while (origin[j] != '\0') {
		if (check == 0) {			
			result[i] = origin[j];
			i++;
			j++;
			if (j % 3 == 0) {
				result[i] = '@';
				i++;
				result[i] = '@';
				i++;
			}
		}
		else {			
			if (origin[j] == '@' && origin[j + 1] == '@') {
				j += 2;
			}
			else {
				result[i] = origin[j];
				i++;
				j++;
			}
		}
	}
	result[i] = '\0';
	
	if (*str != NULL) {
		//free(*str);
	}
	*str = result;
	return;
}

//띄어쓰기 기준으로 단어 뒤집기
void reverseWord(char* str) {
	int len = strlen(str);

	int start = 0;
	for (int i = 0; i <= len; i++) {
		if (str[i] == ' ' || str[i] == '\0' || str[i] == '\n') {			
			int end = i - 1;
			while (start < end) {
				char temp = str[start];
				str[start] = str[end];
				str[end] = temp;
				start++;
				end--;
			}
			start = i + 1;
		}
	}
}

//문자 교체
void replaceAlphabet(char* str, char target, char replaceto) {
	char* tmp = str;

	while (*tmp != '\0') {
		if (*tmp == target) {
			*tmp = replaceto;
		}
		tmp++;
	}	
}



//앞뒤가 같은 단어 출력
void checkreverseWord(char* str) {
	int len = strlen(str);

	char* copy_str = strdup(str);

	char* token = strtok(copy_str, "\n");
	while (token != NULL) {
		printf("%s", token);
		char string[100];
		char* strp = string;

		char* start = token;
		char* end = token;
		while (*end != '\0') {
			end++;
		}
		end--;
		while (start != end && start < end) {
			if (*start == *end) {
				*strp = *start;
				start++;
				end--;
				strp++;
				*strp = '\0';
			}
			else {				
				*strp = '\0';
				break;
			}
		}
		if (strp == string) {
			printf(":0\n");
		}
		else {
			printf(": %s\n", string);
		}
		token = strtok(NULL, "\n");
	}
}

//단어 숫자 판별
int isNum(const char* word) {
	for (int i = 0; word[i] != '\0'; i++) {
		// 숫자가 아닌 문자가 있으면 0(false) 반환
		if (!isdigit(word[i])) {
			return 0; 
		}
	}
	return 1; //숫자면 1(true) 반환
}

//숫자 변경
void modifyNumericWords(char** str, int option) {
	if (str == NULL) {
		return;
	}

	char finish[800];
	*finish = '\0';
	int finishp = 0;

	char* current = *str; // 문자열
	char* wordStart = *str; // 현재 단어

	while (1) {
		if (*current == ' ' || *current == '\n'|| *current == '\0') {
			char blank = *current;	//띄어쓰기인지 개행문자인지 저장
			char* wordEnd = current; //단어 끝
			int wordLength = wordEnd - wordStart;

			char tmp[100];

			// 단어 추출		
			*current = '\0';
			strcpy(tmp, wordStart);	//여기가 문제
			*current = blank;
			// 숫자인 경우 처리
			if (isNum(tmp)) {
				int num = atoi(tmp);
				if (option == 1) {
					num++;
				}
				else {
					if (num > 0) {
						num--;
					}
				}
				int numlen = 1;
				while (num / (numlen * 10) != 0) {
					numlen++;
				}
				// 변경된 숫자를 문자열로 변환
				//snprintf(finishp, numlen + 1, "%d", num);
				snprintf(finish, sizeof(finish), "%s%d%c", finish, num, blank);
				finishp += numlen;
			}
			else {
				// 꺼내온 단어를 새 문자열에 저장
				//strncpy(finishp, tmp, wordLength);
				snprintf(finish, sizeof(finish), "%s%s%c", finish, tmp, blank);
				finishp += strlen(tmp);
			}			
			finishp++;
			finish[finishp] = '\0';

			// 다음 단어로 이동
			wordStart = current + 1;
			//printf("'%s' len = %d\n", word, strlen(word));			
		}
		if (*current == '\0')
			break;
		current++;
	}	
	realloc(*str, finishp + 1);
	strcpy(*str, finish);		
	return;
}


void console() {	
	int check = 0;	//0: 문자 삽입 안함, 1: 문자 삽입 함.

	//파일 이름을 입력받아 문자열을 입력받음
	char* str = NULL;
	while (str == NULL) {
		char name[50];
		printf("읽을 파일명 입력:");
		scanf("%s", name);
		str = getString(name);
	}

	printf("문장: %s\n", str);	//입력받은 문자열 출력
	//명령어 처리
	while (1) {
		char order;
		char target, replaceto;
		printf("명령어 목록:  d: 문장 전체를 뒤집기\n");
		printf("e: 동일한 간격으로 띄어쓰기를 일정 개수 삽입하기\n");
		printf("f : 공백을 기준으로 문자 뒤집기\n");
		printf("g : 문자 내부의 특정 문자열을 다른 문자열로 바꾸기\n");
		printf("h : 앞뒤에서 읽었을 때 어디까지 같은 문자인지 출력하기\n");
		printf("+ : 숫자에 + 1\n");
		printf("- : 숫자에 - 1\n");
		printf("q : 종료\n\n");						
		printf("명령어 입력:");
		scanf(" %c", &order);

		printf("\n");
		switch (order) {
		case 'd': case 'D':
			reverseString(str);		
			printf("문장: %s\n", str);	//입력받은 문자열 출력

			break;
		case 'e': case 'E':
			insertLetter(&str, check);
			check++;
			check %= 2;			
			printf("문장: %s\n", str);	//입력받은 문자열 출력
			break;
		case 'f': case 'F':
			reverseWord(str);
			printf("문장: %s\n", str);	//입력받은 문자열 출력
			break;
		case 'g': case 'G':
			scanf(" %c %c", &target, &replaceto);
			replaceAlphabet(str, target, replaceto);
			printf("문장: %s\n", str);	//입력받은 문자열 출력
			break;
		case 'h': case 'H':
			checkreverseWord(str);
			break;
		case '+':
			modifyNumericWords(&str, 1);
			printf("문장: %s\n", str);	//입력받은 문자열 출력
			break;
		case '-':
			modifyNumericWords(&str, -1);
			printf("문장: %s\n", str);	//입력받은 문자열 출력
			break;
		case 'q': case 'Q':
			return;
			break;
		default:
			printf("해당 명령어가 존재하지 않음.\n");
			break;
		}
	}

}


int main() {
	console();
	return 0;
}