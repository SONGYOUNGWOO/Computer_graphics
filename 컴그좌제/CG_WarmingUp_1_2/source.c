#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//���� �Է� �Լ�
char* getString(const char* fileName) {
	char* str = malloc(sizeof(char) * 800);
	FILE* fp = fopen(fileName, "rt");

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
		strp++;
	}

	return str;
}

//���ڿ� �ܾ� ���� üũ
int wordCount(char* str) {
	int count = 0;
	char* tmp = malloc(sizeof(char) * strlen(str));
	strcpy(tmp, str);

	char* word = strtok(tmp, " \n");
	while (word != NULL) {
		if ('0' <= *word && *word <= '9') {
			word++;
			if (*word == ' ' || *word == '\0') {
							
				word = strtok(NULL, " \n");				
			}
		}
		else {
			count += 1;
			word = strtok(NULL, " \n");				
		}
	}

	return count;
}

//���ڿ� ���� ���� üũ
int numberCount(char* str) {
	int count = 0;
	char* tmp = malloc(sizeof(char) * strlen(str));
	strcpy(tmp, str);

	char* word = strtok(tmp, " \n");

	char target[20];
	strcpy(target, word);

	while (word != NULL) {		
		if ('0'<= *word && *word <= '9') {
			word++;
			if (*word == ' '|| *word == '\0') {
				count += 1;
				printf("%d: %s\n",count,target);
				word = strtok(NULL, " \n");
				if(word != NULL)
					strcpy(target, word);
			}
		}
		else {
			word = strtok(NULL, " \n");
			if (word != NULL)
				strcpy(target, word);
		}
	}


	return count;
}


//���ڿ� �빮�� ���Դܾ� ���� üũ
int capitalCount(char* str) {
	int count = 0;
	char* tmp = malloc(sizeof(char) * strlen(str));
	strcpy(tmp, str);

	char* word = strtok(tmp, " \n");


	char target[20];
	strcpy(target, word);
	while (word != NULL) {
		if ('A' <= *word && *word <= 'Z') {
			count += 1;
			printf("%d: %s\n", count, target);
			word = strtok(NULL, " \n");
			if (word != NULL)
				strcpy(target, word);
		}
		else {			
			word = strtok(NULL, " \n");
			if (word != NULL)
				strcpy(target, word);			
		}
	}
	return count;
}


void console() {
	//char* str = getString();
	char* str = NULL;
	while (str == NULL) {
		char name[50];
		printf("���� ���ϸ� �Է�:");
		scanf("%s", name);
		str = getString(name);
	}
	printf("%s", str);
	printf("\n");
	printf("word count: %d\n",wordCount(str));
	printf("\n");
	printf("number count: %d\n", numberCount(str));
	printf("\n");
	printf("Capital count: %d\n", capitalCount(str));
}

int main() {
	console();

	system("pause");
	return 0;
}
