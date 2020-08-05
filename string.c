#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>
#include <stdlib.h>

void GetNext(char* S, int* next, int len);
void DoKMP(char* b, char* S,  int len);

int isIgnoreCase = 0;

int main(int argc,char **argv) {
	
	FILE* fp1;
	char* allString;
	char matchedString[10][10000];
	int cont_S = 0;
	char b[10000];
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i],"-F"))
		{
			if (!strcmp(argv[++i], "-i"))
			{
				isIgnoreCase = 1;
				fp1 = fopen(argv[++i], "r");
			}
			else
			{
				fp1 = fopen(argv[i], "r");
			}
		}
		else if (!strcmp(argv[i], "-E"))
		{
			if (!strcmp(argv[++i], "-i")) {
				isIgnoreCase = 1;
				allString = argv[++i];
			}
			else
			{
				allString = argv[i];
			}
		}
		else if (!strcmp(argv[i], "-i"))
		{
			isIgnoreCase = 1;
		}
	}/*“-i”“-E”“-F”识别模块*/
	char *s1;
	char* buf;
	char *jug = "|";
	s1 = strtok_r(allString, "|", &buf);
	int cont = 0;
	while (s1 != NULL)
	{
		strcpy(matchedString[cont_S++], s1);
		fseek(fp1, 0, SEEK_SET);
		int len = strlen(matchedString[cont_S - 1]);
		while (matchedString[cont_S - 1][len - 1] == '\\')
		{
			char temp[10000];
			memset(temp, 0, sizeof(temp));
			strncpy(temp, matchedString[cont_S - 1], strlen(matchedString[cont_S - 1]) - 1);
			s1 = strtok_r(NULL, "|", &buf);
			strcpy(matchedString[cont_S - 1], s1);
			strcat(temp, matchedString[cont_S - 1]);
			strcpy(matchedString[cont_S - 1], temp);
			len = strlen(matchedString[cont_S - 1]);
		}
		int s_len = strlen(matchedString[cont_S - 1]);
		if (fp1 == NULL)
		{
			printf("File open failed!\n");
			return 0;
		}/*匹配字符串分割*/
		s1 = strtok_r(NULL, "|", &buf);
	}
	while (fgets(b, 10000, fp1) != NULL)
	{
		for (int i = 0; i < cont_S; i++)
		{
			DoKMP(b, matchedString[i], strlen(matchedString[i]));
		}
	}
	fclose(fp1);
}

void DoKMP(char* b, char* S, int len) {
	int i = 0, j = 0;
	int isRegular = 0;
	int isI = 0;
	for ( i = 0; i < len-1; i++)
	{
		if (S[i] == '.'&& S[i+1] == '*')
		{
			isRegular = 1;
			break;
		}
	}
	if (isRegular)
	{
		char match1[10000], match2[10000];
		int j2 = 0;
		int i2 = 0;
		int k = 0;
		for (k = 0; k < i; k++)
		{
			match1[k] = S[k];
		}
		k = k + 2;
		for ( ;k < len ; k++)
		{
			match2[j2++] = S[k];
		}
		int *next1 = malloc(sizeof(int)*(strlen(match1) + 1));
		int *next2 = malloc(sizeof(int)*(strlen(match2) + 1));
		GetNext(match1, next1, strlen(match1));
		GetNext(match2, next2, strlen(match2));
		i = 0;
		i2 = 0;
		j = -1;
		j2 = -1;
		int len1 = strlen(match1);
		int len2 = strlen(match2);
		int lenMain = strlen(b);
		if (isIgnoreCase) {
			while (i < lenMain && j < len1)
			{
				if (j == -1 || b[i] == match1[j] || match1[j] - b[i] == 32 || b[i] - match1[j] == 32) {
					j++;
					i++;
				}
				else
				{
					j = next1[j];
				}
			}
			while (i2 < lenMain && j2 < len2)
			{
				if (j2 == -1 || b[i2] == match2[j2] || match2[j2] - b[i2] == 32 || b[i2] - match2[j2] == 32) {
					j2++;
					i2++;
				}
				else
				{
					j2 = next2[j2];
				}
			}
		}
		else
		{
			while (i < lenMain && j < len1)
			{
				if (j == -1 || b[i] == match1[j]) {
					j++;
					i++;
				}
				else
				{
					j = next1[j];
				}
			}
			while (i2 < lenMain && j2 < len2)
			{
				if (j2 == -1 || b[i2] == match2[j2]) {
					j2++;
					i2++;
				}
				else
				{
					j2 = next2[j2];
				}
			}
		}

		if (j >= len1 && j2 >= len2)
		{
			printf("%s", b);
		}
		/*正则表达式搜索*/
	}
	else
	{
		int* next = malloc(sizeof(int) * (strlen(S)));
		GetNext(S, next, strlen(S));
		i = 0;
		j = -1;
		if (isIgnoreCase) {
			while (i < strlen(b) && j < len)
			{
				if (j == -1 || b[i] == S[j] || S[j] - b[i] == 32 || b[i] - S[j] == 32)
				{
					i++;
					j++;
				}
				else
				{
					j = next[j];
				}
			}
		}
		else
		{
			while (i < strlen(b) && j < len)
			{
				if (j == -1 || b[i] == S[j])
				{
					i++;
					j++;
				}
				else
				{
					j = next[j];
				}
			}
		}
		if (j >= len)
		{
			printf("%s", b);
		}
		/*KMP算法匹配*/
	}
}

void GetNext(char* S, int* next, int len) {
	int i = 0, j = -1;
	next[0] = -1;
	while (i < len + 1)
	{
		if (j == -1 || S[i] == S[j])
		{
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