#ifndef MAPSUN_H
#define MAPSUN_H

struct Node
{
	char Key[10000];
	int Value;
	struct Node* next;
};

void insertNode(char* Key, int Value);
void insert(char* Key, int Value);
void sum(char* Key);
void Getnext(char* S, int* next);
int KMP(char* P, char* S);
//void strcpy(char* s1, char* s2);
//int strcmp(char* s1, char* s2);
//int strlen(char* s);

struct Node* Head;

void insertNode(char* Key, int Value) {
	struct Node* Node = (struct Node*)malloc(sizeof(struct Node));
	Node->next = NULL;
	strcpy(Node->Key, Key);
	Node->Value = Value;
	struct Node* head = Head;
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = Node;
}

void insert(char* Key, int Value) {
	if (Head == NULL)
	{
		Head = (struct Node*)malloc(sizeof(struct Node));
		Head->next = NULL;
		insertNode(Key, Value);
	}
	else
	{
		struct Node* head = Head;
		int isExist = 0;
		while (head->next != NULL)
		{
			head = head->next;
			if (!strcmp(head->Key, Key))
			{
				printf("%d\n", strcmp(head->Key, Key));
				printf("%s\t%s\n", head->Key, Key);
				head->Value = Value;
				isExist = 1;
				break;
			}
		}
		if (!isExist)
		{
			insertNode(Key, Value);
		}
	}
}

void sum(char* Key) {
	struct Node* head = Head;
	int isExist = 0;
	int sumAll = 0;
	while (head->next != NULL)
	{
		head = head->next;
		isExist = KMP(head->Key, Key);
		if (isExist)
		{
			sumAll += head->Value;
			isExist = 0;
		}
	}
	printf("%d\n", sumAll);
}

void Getnext(char* S, int* next) {
	int i = 0, j = -1;
	next[0] = -1;
	int len = strlen(S);
	while (i < len + 1)
	{
		if (j == -1 || S[i] == S[j]) {
			i++;
			j++;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}

int KMP(char* P, char* S) {
	int len_P = strlen(P);
	int len_S = strlen(S);
	int i = 0, j = 0;
	int* next = malloc(sizeof(int) * (len_S + 1));
	Getnext(S, next);
	while (i < len_P && j < len_S)
	{
		if (j == -1 || P[i] == S[j])
		{
			i++;
			j++;
		}
		else
		{
			break;
		}
	}
	if (j >= len_S)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//void strcpy(char* s1, char* s2) {
//	if (s1 == NULL || s2 == NULL)
//	{
//		return;
//	}
//	int i = 0;
//	while (s2[i] != '\0') {
//		s1[i] = s2[i];
//		i++;
//	}
//	s1[i] = '\0';
//}
//
//int strcmp(char* s1, char* s2) {
//	int cont = 0;
//	while (s1[cont] == s2[cont])
//	{
//		cont++;
//	}
//	if (s1[cont - 1] == '\0')
//	{
//		return 0;
//	}
//	else
//	{
//		return s1 - s2;
//	}
//}
//
//int strlen(char* s) {
//	int cont = 0;
//	while (s[cont] != '\0')
//	{
//		cont++;
//	}
//	return cont;
//}
#endif