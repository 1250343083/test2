#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"MapSun.h"

int main() {
	int isInsert = 0;
	int isSum = 0;
	int Value = 0;
	char S[10000];
	char Key[100000];
	while (scanf("%s",S)!=EOF)
	{
		if (!isInsert && !isSum)
		{
			if (!strcmp(S, "-i"))
			{
				isInsert = 2;
			}
			else if (!strcmp(S, "-s"))
			{
				isSum = 1;
			}
		}
		else if (isInsert)
		{
			if (isInsert == 2)
			{
				strcpy(Key, S);
			}
			else
			{
				Value = atoi(S);
				insert(Key, Value);
			}
			isInsert--;
		}
		else if (isSum)
		{
			strcpy(Key, S);
			sum(Key);
			isSum--;
		}
	}
}