#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define LINE_SIZE  1024
#define ERROR_MSG "Invalid input in line: %d."

/** This struct represents the fileLines starting from line 4*/
typedef struct charLine
{
	char start;
	char end;
	int length;
	int price;
} charLine;

/** This struct represents the file data converted into relevant data members*/
typedef struct data
{
	char connections[LINE_SIZE];
	int L;
	int K;
	charLine *charLines;
	int N;
} data;

/** @brief printing FILE relevant error
 * @return EXIT_FAILURE*/
int printERR(char *toPrint)
{
	FILE *open = fopen("railway_planner_output.txt", "w+");
	fprintf(open, "%s", toPrint);
	fclose(open);
	return EXIT_FAILURE;
}

/** @brief printing assumptions relevant error
 * @return EXIT_FAILURE*/
int printFileErr(char *toPrint, int line)
{
	FILE *open = fopen("railway_planner_output.txt", "w+");
	fprintf(open, toPrint, line);
	return EXIT_FAILURE;
}

/** this function reads the second file, then saves it into data structure*/
int readFirstLine(char input[], FILE *fp)
{
	if (fgets(input, LINE_SIZE, fp) == NULL)
	{
		printERR("File is empty.");
		return -1;
	}
	char *first = strtok(input, "\r\n\0");


	for (int i = 0; (int) strlen(first) - 1; i++)
	{
		if (first[i] == '\0')
		{
			break;
		}
		if (!isdigit(first[i]))
		{
			printFileErr(ERROR_MSG, 1);
			return -1;
		}
	}
	int length = (int) strtol(first, (char **) NULL, 10);
	return length;
}

/** this function reads the second file, then saves it into data structure*/
int readSecondLine(char input[], FILE *fp)
{
	char *two = fgets(input, LINE_SIZE, fp);
	strtok(input, "\r\n\0");
	for (int i = 0; (int) strlen(two) - 1; i++)
	{
		if (two[i] == '\0')
		{
			break;
		}

		if (!isdigit(two[i]))
		{
			printFileErr(ERROR_MSG, 2);
			return -1;
		}
	}
	int K = (int) strtol(two, (char **) NULL, 10);
	if (K <= 0)
	{
		printFileErr(ERROR_MSG, 2);
		return -1;
	}
	return K;
}

/** this function reads the fourth line of a file, then saving it into dast*/
int readFourLine(char input[], FILE *fp, data *toSave, int line)
{
	charLine temp;
	int K = toSave->K;
	fgets(input, LINE_SIZE, fp);
	char *fourOne = strtok(input, ",");
	if ((int) strlen(fourOne) != 1)
	{
		return printFileErr(ERROR_MSG, line);
	}
	int j = 0;
	while (fourOne[0] != toSave->connections[j])
	{
		if (j == K)
		{
			return printFileErr(ERROR_MSG, line);
		}
		j++;
	}


	char *fourTwo = strtok(NULL, ",");
	if ((int) strlen(fourTwo) != 1)
	{
		return printFileErr(ERROR_MSG, line);
	}
	j = 0;
	while (fourTwo[0] != toSave->connections[j])
	{
		if (j == K)
		{
			return printFileErr(ERROR_MSG, line);
		}
		j++;
	}

	char *fourThree = strtok(NULL, ",");
	for (int i = 0; i < (int) strlen(fourThree); i++)
	{
		if (fourThree[i] == '\0')
		{ break; }
		if (!isdigit(fourThree[i]))
		{
			return printFileErr(ERROR_MSG, line);
		}
	}

	char *fourFour = strtok(NULL, "\r\n\0");
	char *fourCheck = strtok(NULL, ",\r\n\0");
	if (fourCheck != NULL)
	{
		return printFileErr(ERROR_MSG, line);
	}
	for (int i = 0; (int) strlen(fourFour) - 1; i++)
	{
		if (fourFour[i] == '\0')
		{
			break;
		}
		if (!isdigit(fourFour[i]))
		{
			return printFileErr(ERROR_MSG, line);
		}
	}
	temp.start = fourOne[0];
	temp.end = fourTwo[0];
	temp.length = (int) strtol(fourThree, (char **) NULL, 10);
	if (temp.length <= 0)
	{
		return printFileErr(ERROR_MSG, line);
	}
	temp.price = (int) strtol(fourFour, (char **) NULL, 10);
	if (temp.price <= 0)
	{

		return printFileErr(ERROR_MSG, line);
	}
	toSave->charLines = (charLine *) malloc(sizeof(charLine));
	if(toSave->charLines == NULL)
	{
		return EXIT_FAILURE;
	}
	toSave->charLines[0] = temp;
	return EXIT_SUCCESS;
}

/** this function reads the lines of a file starting in the fifth, then saving them into dast*/
int readFifthPlus(char input[], data *toSave, int curLine)
{
	int K = toSave->K;
	charLine temp;
	char *fourOne = strtok(input, ",");
	if ((int) strlen(fourOne) != 1)
	{
		free(toSave->charLines);
		return printFileErr(ERROR_MSG, curLine + 4);
	}
	int k = 0;
	while (fourOne[0] != toSave->connections[k])
	{
		if (k == K)
		{
			free(toSave->charLines);
			return printFileErr(ERROR_MSG, curLine + 4);
		}
		k++;
	}


	char *fourTwo = strtok(NULL, ",");
	if ((int) strlen(fourTwo) != 1)
	{
		free(toSave->charLines);
		return printFileErr(ERROR_MSG, curLine + 4);
	}
	k = 0;
	while (fourTwo[0] != toSave->connections[k])
	{
		if (fourTwo[0] == toSave->connections[k])
		{
			break;
		}
		if (k == K)
		{
			free(toSave->charLines);
			return printFileErr(ERROR_MSG, curLine + 4);
		}
		k++;
	}

	char *fourThree = strtok(NULL, ",");
	for (int i = 0; (int) strlen(fourThree); i++)
	{
		if (fourThree[i] == '\0')
		{
			break;
		}
		if (!isdigit(fourThree[i]))
		{
			free(toSave->charLines);
			return printFileErr(ERROR_MSG, curLine + 4);
		}
	}

	char *fourFour = strtok(NULL, "\r\n\0");
	char *fourCheck = strtok(NULL, ",\r\n\0");
	if (fourCheck != NULL)
	{
		free(toSave->charLines);
		return printFileErr(ERROR_MSG, curLine + 4);
	}
	for (int i = 0; (int) strlen(fourFour) - 1; i++)
	{
		if (fourFour[i] == '\0')
		{
			break;
		}
		if (!isdigit(fourFour[i]))
		{
			free(toSave->charLines);
			return printFileErr(ERROR_MSG, curLine + 4);
		}
	}
	temp.start = fourOne[0];
	temp.end = fourTwo[0];
	temp.length = (int) strtol(fourThree, (char **) NULL, 10);
	if (temp.length <= 0)
	{
		free(toSave->charLines);
		return printFileErr(ERROR_MSG, curLine + 4);
	}
	temp.price = (int) strtol(fourFour, (char **) NULL, 10);
	if (temp.price <= 0)
	{
		free(toSave->charLines);
		return printFileErr(ERROR_MSG, curLine + 4);
	}
	toSave->charLines = (charLine *) realloc(toSave->charLines,
											 sizeof(charLine) * (curLine + 1));
	toSave->charLines[curLine] = temp;
	return EXIT_SUCCESS;
}

/** This function read the file lines*/
int read(data *toSave, char *fileName)
{
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		return printERR("File doesn't exists.");
	}
	char input[LINE_SIZE];
	int readFirst = readFirstLine(input, fp);
	if (readFirst == -1)
	{
		fclose(fp);
		return EXIT_FAILURE;
	}
	toSave->L = readFirst;
	int K = readSecondLine(input, fp);
	if (K == -1)
	{
		fclose(fp);
		return EXIT_FAILURE;
	}
	toSave->K = K;
	fgets(input, LINE_SIZE, fp);
	char *three = strtok(input, ",\r\n\0");
	if ((int) strlen(three) != 1)
	{
		return printFileErr(ERROR_MSG, 3);
	}
	int count = 0;
	while (three != NULL)
	{
		toSave->connections[count] = three[0];
		if ((int) strlen(three) != 1)
		{
			return printFileErr(ERROR_MSG, 3);
		}
		three = strtok(NULL, ",\r\n\0");
		count++;
	}
	if (count != K)
	{
		return printFileErr(ERROR_MSG, 3);
	}
	if (readFourLine(input, fp, toSave, 4) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	int curLine = 1;
	while (fgets(input, LINE_SIZE, fp) != NULL)
	{
		if (readFifthPlus(input, toSave, curLine) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		curLine++;
	}
	toSave->N = curLine;
	return EXIT_SUCCESS;
}


/** @return this function returns the index of the symbols place in a list*/
int checkIndex(const char *symbs, char toCheck, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (symbs[i] == toCheck)
		{
			return i;
		}
	}
	return (len + 1);
}


/** This function calculates the minimal price of a give length*/
int calculateMin(const data *fp)
{
	int length = fp->L;
	int keys = fp->K;
	int n = fp->N;

	const char *symbols = fp->connections;
	int **list = (int **) malloc(sizeof(int *) * keys);
	for (int i = 0; i < keys; i++)
	{
		list[i] = (int *) calloc((length + 1), sizeof(int));
		if (list[i] == NULL)
		{
			return EXIT_FAILURE;
		}
		list[i][0] = 0;
	}

	for (int l = 1; l <= length; l++)
	{
		for (int col = 0; col < keys; col++)
		{
			int temp = INT_MAX;

			for (int line = 0; line < n; line++)
			{
				int index = checkIndex(symbols, fp->charLines[line].start, keys);
				if (fp->charLines[line].end == symbols[col] && fp->charLines[line].length == l
					&& fp->charLines[line].price < temp)
				{
					temp = fp->charLines[line].price;
					list[col][l] = fp->charLines[line].price;
				}

				else if (fp->charLines[line].end == symbols[col] && fp->charLines[line].length < l
						 && checkIndex(symbols, fp->charLines[line].start, keys) != (keys + 1) &&
						 list[index][l - fp->charLines[line].length] != INT_MAX
						 &&
						 list[index][l - fp->charLines[line].length] + fp->charLines[line].price <
						 temp
						 && 0 <=
						 list[index][l - fp->charLines[line].length] + fp->charLines[line].price)
				{
					temp = list[index][l - fp->charLines[line].length] + fp->charLines[line].price;
					list[col][l] = list[index][l - fp->charLines[line]
								.length] + fp->charLines[line].price;
				}
			}
			if (temp == INT_MAX)
			{
				list[col][l] = INT_MAX;
			}
		}

	}
	int final = list[0][length];
	for (int j = 1; j < keys; j++)
	{
		if (list[j][length] < final)
		{
			final = list[j][length];
		}
		free(list[j]);
	}
	free(list[0]);
	free(list);
	if (final == INT_MAX || final < 0)
	{
		final = -1;
	}
	FILE *open = fopen("railway_planner_output.txt", "w");
	fprintf(open, "The minimal price is: %d", final);
	fclose(open);
	return EXIT_SUCCESS;
}

/** the main function, actually runs the whole functions*/
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		return printERR("Usage: RailwayPlanner <InputFile>");
	}
	data try;
	if (read(&try, argv[1]) == EXIT_FAILURE)
	{ return EXIT_FAILURE; }
	const int toPrint = calculateMin(&try);
	if (toPrint == EXIT_FAILURE)
	{
		free(try.charLines);

		return EXIT_FAILURE;
	}
	free(try.charLines);
	return 0;
}

