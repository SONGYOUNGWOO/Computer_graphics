#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���� �Է� �Լ�
char* getString(const char* fileName) {
	char* str = (char*)malloc(sizeof(char) * 800);
	FILE* fp = fopen(fileName, "rt");

	int len = 0;
	if (fp == NULL) {
		printf("���� ���� ����\n");
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

// ���� ��ü�� ������
void reverseString(char* str) {
	int len = strlen(str);
	for (int i = 0; i < len / 2; i++) {
		char tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
	}
	return;
}

//3���� ���̿� ���� ����/����
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

//���� �������� �ܾ� ������
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

//���� ��ü
void replaceAlphabet(char* str, char target, char replaceto) {
	char* tmp = str;

	while (*tmp != '\0') {
		if (*tmp == target) {
			*tmp = replaceto;
		}
		tmp++;
	}	
}



//�յڰ� ���� �ܾ� ���
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

//�ܾ� ���� �Ǻ�
int isNum(const char* word) {
	for (int i = 0; word[i] != '\0'; i++) {
		// ���ڰ� �ƴ� ���ڰ� ������ 0(false) ��ȯ
		if (!isdigit(word[i])) {
			return 0; 
		}
	}
	return 1; //���ڸ� 1(true) ��ȯ
}

//���� ����
void modifyNumericWords(char** str, int option) {
	if (str == NULL) {
		return;
	}

	char finish[800];
	*finish = '\0';
	int finishp = 0;

	char* current = *str; // ���ڿ�
	char* wordStart = *str; // ���� �ܾ�

	while (1) {
		if (*current == ' ' || *current == '\n'|| *current == '\0') {
			char blank = *current;	//�������� ���๮������ ����
			char* wordEnd = current; //�ܾ� ��
			int wordLength = wordEnd - wordStart;

			char tmp[100];

			// �ܾ� ����		
			*current = '\0';
			strcpy(tmp, wordStart);	//���Ⱑ ����
			*current = blank;
			// ������ ��� ó��
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
				// ����� ���ڸ� ���ڿ��� ��ȯ
				//snprintf(finishp, numlen + 1, "%d", num);
				snprintf(finish, sizeof(finish), "%s%d%c", finish, num, blank);
				finishp += numlen;
			}
			else {
				// ������ �ܾ �� ���ڿ��� ����
				//strncpy(finishp, tmp, wordLength);
				snprintf(finish, sizeof(finish), "%s%s%c", finish, tmp, blank);
				finishp += strlen(tmp);
			}			
			finishp++;
			finish[finishp] = '\0';

			// ���� �ܾ�� �̵�
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
	int check = 0;	//0: ���� ���� ����, 1: ���� ���� ��.

	//���� �̸��� �Է¹޾� ���ڿ��� �Է¹���
	char* str = NULL;
	while (str == NULL) {
		char name[50];
		printf("���� ���ϸ� �Է�:");
		scanf("%s", name);
		str = getString(name);
	}

	printf("����: %s\n", str);	//�Է¹��� ���ڿ� ���
	//��ɾ� ó��
	while (1) {
		char order;
		char target, replaceto;
		printf("��ɾ� ���:  d: ���� ��ü�� ������\n");
		printf("e: ������ �������� ���⸦ ���� ���� �����ϱ�\n");
		printf("f : ������ �������� ���� ������\n");
		printf("g : ���� ������ Ư�� ���ڿ��� �ٸ� ���ڿ��� �ٲٱ�\n");
		printf("h : �յڿ��� �о��� �� ������ ���� �������� ����ϱ�\n");
		printf("+ : ���ڿ� + 1\n");
		printf("- : ���ڿ� - 1\n");
		printf("q : ����\n\n");						
		printf("��ɾ� �Է�:");
		scanf(" %c", &order);

		printf("\n");
		switch (order) {
		case 'd': case 'D':
			reverseString(str);		
			printf("����: %s\n", str);	//�Է¹��� ���ڿ� ���

			break;
		case 'e': case 'E':
			insertLetter(&str, check);
			check++;
			check %= 2;			
			printf("����: %s\n", str);	//�Է¹��� ���ڿ� ���
			break;
		case 'f': case 'F':
			reverseWord(str);
			printf("����: %s\n", str);	//�Է¹��� ���ڿ� ���
			break;
		case 'g': case 'G':
			scanf(" %c %c", &target, &replaceto);
			replaceAlphabet(str, target, replaceto);
			printf("����: %s\n", str);	//�Է¹��� ���ڿ� ���
			break;
		case 'h': case 'H':
			checkreverseWord(str);
			break;
		case '+':
			modifyNumericWords(&str, 1);
			printf("����: %s\n", str);	//�Է¹��� ���ڿ� ���
			break;
		case '-':
			modifyNumericWords(&str, -1);
			printf("����: %s\n", str);	//�Է¹��� ���ڿ� ���
			break;
		case 'q': case 'Q':
			return;
			break;
		default:
			printf("�ش� ��ɾ �������� ����.\n");
			break;
		}
	}

}


int main() {
	console();
	return 0;
}