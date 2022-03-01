#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <string.h>

char wordtoguess[255];
int gamestate=0;

int SearchArray(char word, char* array, int arraySize) {
	for (int i=0;i<arraySize;i++)
		if (array[i]==word)
			return 1;
	return 0;
}

int SearchArray2(char* array1, int array1size, char* array2, int array2size) {
	for (int i=0;i<array1size;i++)
		for (int k=0;k<array2size;i++)
			if (array1[i]==array2[k])
				return 1;
	return 0;
}

void Display(int att, char* gC) {
	printf("==========================================\n");
	switch (att) {
		default:
			break;
	}
	for (int i=0;i<strlen(wordtoguess);i++) {
		if (SearchArray(wordtoguess[i],gC,strlen(gC))==1)
			putchar(wordtoguess[i]);
		else
			putchar('#');
	}
	putchar('\n');
	printf("You have %d attempts left\n",att);
	printf("Your guessed characters: ");
	for (int i=0;i<27;i++) {
		if (gC[i]!=00)
			printf("%c, ",gC[i]);
	}
	putchar('\n');
}

void GuessChar(int* att,char* gC,int q) {
	char e;
	while (1) {
		printf("Guess a character:\n");
		scanf("%c%*c",&e);
		e=toupper(e);
		if (SearchArray(e,gC,27)==1)
			printf("You have already guessed this character\n");
		else
			break;
	}
	*(gC+q)=e;
	if (SearchArray(e,wordtoguess,strlen(wordtoguess))==1)
		printf("%c was in the word\n",e);
	else {
		printf("%c wasn't in the word\n",e);
		*att=*att-1;
	}
	return ;
}

int ChangeGameState(char* gC) {
	for (int i=0;i<strlen(wordtoguess);i++)
		if (SearchArray(wordtoguess[i],gC,27)!=1)
			return -1;
	return 1;
}

int main() {
	srand(time(NULL));
	FILE* list=fopen("./list.txt","r");
	if (list==NULL) {
		printf("list.txt file not found. Exitting...\n");
		return 0;
	}
	int lineno=0;
	while (strcmp(wordtoguess,"END")!=0) {
		fscanf(list,"%s",&wordtoguess);
		lineno++;
	}
	int ttt=rand()%lineno+1;
	fclose(list);
	list=fopen("./list.txt","r");
	for (int i=0;i<ttt;i++)
		fscanf(list,"%s",&wordtoguess);
	int attemptLeft=6,g=0;
	char* guessedChar=(char*)calloc(27,sizeof(char));
	while (attemptLeft!=0) {
		Display(attemptLeft,guessedChar);
		GuessChar(&attemptLeft,guessedChar,g);
		g++;
	}
	gamestate=ChangeGameState(guessedChar);
	switch(gamestate) {
		case -1: {
			printf("You loses. The word was \"%s\"\n",wordtoguess);
			break;
		}
		case 1: {
			printf("Congrats! The word was \"%s\"\n",wordtoguess);
			break;
		}
	}
	return 0;
}
