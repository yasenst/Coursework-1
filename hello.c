#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME 150

int menu(void);
void file_to_file(void);
void file_to_screen(void);
void keyboard_to_file(void);
void keyboard_to_screen(void);
void counter(FILE *fp, int *rows, int *semicolons, int *ifs, int *elseifs);


int main()
{
	int choice;

	do {
		system("cls");
		choice = menu();

		switch (choice) {
		case 1: system("cls"); file_to_file(); break;
		case 2: system("cls"); file_to_screen(); break;
		case 3: system("cls"); keyboard_to_file(); break;
		case 4: system("cls"); keyboard_to_screen(); break;
		case 5: printf("Bye!\n\n");
		default:
			exit(0);
		}

		printf("\nReady! Have a nice day!\n\n");
		system("pause");
	} while (choice != 5);

	return 0;
}

int menu(void)
{
	int i;
	char str[80];

	printf("\nWhat would you like to do?\n");
	printf("\n1. Read program from file and save result to file.\n");
	printf("\n2. Read program from file and print result on screen.\n");
	printf("\n3. Read program from keyboard and print result to file.\n");
	printf("\n4. Read program from keyboard and print result on screen.\n");
	printf("\n5. Quit.\n\n");

	do {

		printf("Enter number of choice:  ");
		gets(str);
		i = atoi(str);
		printf("\n");

	} while (i<1 || i>5);
	return i;
}

void file_to_file(void)
{
	FILE *fp;
	char readFileName[FILENAME], writeFileName[FILENAME];
	int rows = 0, semicolons = 0, ifs = 0, elseifs = 0;

	printf("\nEnter file name to read from: ");

	while (1) {
		gets(readFileName);

		if ((fp = fopen(readFileName, "r")) == NULL)
		{
			printf("\nCannot open file. Enter another name: ");
		}
		else
		{
			break;
		}
	}

	counter(fp, &rows, &semicolons, &ifs, &elseifs);

	fclose(fp);

	printf("\nEnter file name to save result to: ");

	while (1) {
		gets(writeFileName);

		if ((fp = fopen(writeFileName, "w+")) == NULL)
		{
			printf("\nCannot create file. Enter another name: ");
		}
		else
		{
			break;
		}
	}

	fprintf(fp, "You have requested information about %s\n", readFileName);
	fprintf(fp, "Number of rows: %d\n", rows);
	fprintf(fp, "Number of semicolons: %d\n", semicolons);
	fprintf(fp, "Number of if-statements: %d\n", ifs - elseifs);
	fprintf(fp, "Number of if/else-statements: %d\n", elseifs);

	fclose(fp);
}

void file_to_screen(void)
{
	FILE *fp;
	char readFileName[FILENAME];
	int rows = 0, semicolons = 0, ifs = 0, elseifs = 0;

	printf("\nEnter file name to read from: ");

	while (1) {
		gets(readFileName);

		if ((fp = fopen(readFileName, "r")) == NULL)
		{
			printf("\nCannot open file. Enter another name: ");
		}
		else
		{
			break;
		}
	}

	counter(fp, &rows, &semicolons, &ifs, &elseifs);

	fclose(fp);

	printf("\nYou have requested information about %s\n\n", readFileName);
	printf("Number of rows: %d\n", rows);
	printf("Number of semicolons: %d\n", semicolons);
	printf("Number of if-statements: %d\n", ifs - elseifs);
	printf("Number of if/else-statements: %d\n", elseifs);
}
void keyboard_to_file(void)
{
	FILE *fp;
	char writeFileName[FILENAME];
	int rows = 0, semicolons = 0, ifs = 0, elseifs = 0;

	printf("\nEnter file name to save result to: ");

	while (1) {
		gets(writeFileName);

		if ((fp = fopen(writeFileName, "w+")) == NULL)
		{
			printf("\nCannot create file. Enter another name: ");
		}
		else
		{
			break;
		}
	}

	printf("\nWrite your code...(press CTRL+Z when ready):\n\n");
	fflush(stdin);

	counter(stdin, &rows, &semicolons, &ifs, &elseifs);

	fprintf(fp, "Code information: \n");
	fprintf(fp, "Number of rows: %d\n", rows);
	fprintf(fp, "Number of semicolons: %d\n", semicolons);
	fprintf(fp, "Number of if-statements: %d\n", ifs - elseifs);
	fprintf(fp, "Number of if/else-statements: %d\n", elseifs);

	fclose(fp);
}

void keyboard_to_screen(void)
{
	int rows = 0, semicolons = 0, ifs = 0, elseifs = 0;

	printf("\nWrite your code...(press CTRL+Z when ready):\n\n");

	counter(stdin, &rows, &semicolons, &ifs, &elseifs);

	printf("\nCode information: \n");
	printf("Number of rows: %d\n", rows);
	printf("Number of semicolons: %d\n", semicolons);
	printf("Number of if-statements: %d\n", ifs - elseifs);
	printf("Number of if/else-statements: %d\n", elseifs);
}

void counter(FILE *fp, int *rows, int *semicolons, int *ifs, int *elseifs)
{
	char str[FILENAME];
	int i;
	const char c = ';';
	while (fgets(str, sizeof(str), fp) != NULL)
	{
		*rows = *rows + 1;
		char *p = str;
		while (((p = (strstr(p, "if"))) != NULL)) {
			if ((p == str || !isalnum((unsigned char)p[-1])) &&
				!isalnum((unsigned char)p[2]))
				*ifs = *ifs + 1;
			++p;
		}
		p = str;
		while (((p = (strstr(p, "else"))) != NULL)) {
			if ((p == str || !isalnum((unsigned char)p[-1])) &&
				!isalnum((unsigned char)p[4]))
				*elseifs = *elseifs + 1;
			++p;
		}
		for (i = 0; str[i] != '\0'; i++) {
			if (str[i] == c)
				*semicolons = *semicolons + 1;
		}
	}
}

