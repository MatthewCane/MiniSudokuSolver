#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int getRow(int *, int row);
int getColumn(int *, int column);
int getGrid(int *, int grid);
int checker(int *);
int randomNumber();

int main() 
{
	
	const int sudoku[4][4] = {	{4, 0, 0, 0}, 
								{2, 3, 0, 1}, 
								{3, 0, 0, 4}, 
								{0, 0, 0, 2} };

	const int sudokuSolved[4][4] = {{ 4, 1, 2, 3 },
									{ 2, 3, 4, 1 },
									{ 3, 2, 1, 4 },
									{ 1, 4, 3, 2 } };
	
	srand((unsigned) time(NULL));
	bool solved = false;
	int sudokuTrial[16], attempt = 0;
	
	while (solved == false)
	{
		attempt++;
		int k = 0;
		for (int i = 0; i < 4; i++)
		{ //Takes the 2D sudoku array and copies it into a 1D array for processing
			for (int x = 0; x < 4; x++)
			{
				sudokuTrial[k] = sudoku[i][x];
				k++;
			}
		}
		
		for (int i = 0; i < 16; i++)
		{ //Takes the 1D array and assigns a random number where 0 is present
			if (sudokuTrial[i] == 0)
			{
				sudokuTrial[i] = randomNumber();
			}
		}

		if (checker(sudokuTrial) == false) //Calls the check function with the candidate solution and checks the result
		{
			printf("This solution is not valid:\n");
			printf("%d | %d | %d | %d\n", sudokuTrial[0], sudokuTrial[1], sudokuTrial[2], sudokuTrial[3]);
			printf("%d | %d | %d | %d\n", sudokuTrial[4], sudokuTrial[5], sudokuTrial[6], sudokuTrial[7]);
			printf("%d | %d | %d | %d\n", sudokuTrial[8], sudokuTrial[9], sudokuTrial[10], sudokuTrial[11]);
			printf("%d | %d | %d | %d\n\n", sudokuTrial[12], sudokuTrial[13], sudokuTrial[14], sudokuTrial[15]);
		}
		else
		{
			solved = true;
			printf("A solution has been found after %d attempts:\n", attempt);
			printf("%d | %d | %d | %d\n", sudokuTrial[0], sudokuTrial[1], sudokuTrial[2], sudokuTrial[3]);
			printf("%d | %d | %d | %d\n", sudokuTrial[4], sudokuTrial[5], sudokuTrial[6], sudokuTrial[7]);
			printf("%d | %d | %d | %d\n", sudokuTrial[8], sudokuTrial[9], sudokuTrial[10], sudokuTrial[11]);
			printf("%d | %d | %d | %d\n\n", sudokuTrial[12], sudokuTrial[13], sudokuTrial[14], sudokuTrial[15]);
		}
	}
	

	return(0);
}

int getRow(int *sudoku, int row) 
{ //Takes an array pointer and a row number and returns the sum of the row in the array
	int rowArray[4], rowTotal = 0;

	for (int i = 0; i < 4; i++)
	{
		rowArray[i] = sudoku[i + row * 4];
	}

	for (int i = 0; i < 4; i++)
	{
		rowTotal = rowTotal + rowArray[i];
	}

	return(rowTotal);
}

int getColumn(int *sudoku, int column)
{ //Takes an array pointer and a colmn number and returns the sum of the colmn in the array
	int columnArray[4], columnTotal = 0;

	for (int i = 0; i < 4; i++)
	{
		columnArray[i] = sudoku[i * 4 + column];
	}

	for (int i = 0; i < 4; i++)
	{
		columnTotal = columnTotal + columnArray[i];
	}

	return(columnTotal);
}

int getGrid(int *sudoku, int grid)
{ //Takes an array pointer and a grid number and returns the sum of the grid in the array
	int gridArray[4], gridTotal = 0;

	if (grid == 0)
	{
		gridArray[0] = sudoku[0];
		gridArray[1] = sudoku[1];
		gridArray[2] = sudoku[4];
		gridArray[3] = sudoku[5];
	}
	else if (grid == 1)
	{
		gridArray[0] = sudoku[2];
		gridArray[1] = sudoku[3];
		gridArray[2] = sudoku[6];
		gridArray[3] = sudoku[7];
	}
	else if (grid == 2)
	{
		gridArray[0] = sudoku[8];
		gridArray[1] = sudoku[9];
		gridArray[2] = sudoku[12];
		gridArray[3] = sudoku[13];
	}
	else if (grid == 3)
	{
		gridArray[0] = sudoku[10];
		gridArray[1] = sudoku[11];
		gridArray[2] = sudoku[14];
		gridArray[3] = sudoku[15];
	}

	for (int i = 0; i < 4; i++)
	{
		gridTotal = gridTotal + gridArray[i];
	}

	return(gridTotal);
}

int checker(int *sudoku)
{ //Takes a pointer to an array as input, checks if it is a valid complete sudoku board and returns true if valid
	bool correct = false;
	int sum = 0;
	
	if ((getRow(sudoku, 0) == 10) && (getRow(sudoku, 1) == 10) && (getRow(sudoku, 2) == 10) && (getRow(sudoku, 3) == 10))
	{
		correct = true;
		//printf("\n%d\n", getRow(sudoku, 0));
	}
	
	if (correct == true)
	{
		if ((getColumn(sudoku, 0) == 10) && (getColumn(sudoku, 1) == 10) && (getColumn(sudoku, 2) == 10) && (getColumn(sudoku, 3) == 10))
		{
			correct = true;
		}
		else
		{
			correct = false;
		}
	}

	if (correct == true)
	{
		if ((getGrid(sudoku, 0) == 10) && (getGrid(sudoku, 1) == 10) && (getGrid(sudoku, 2) == 10) && (getGrid(sudoku, 3) == 10))
		{
			correct = true;
		}
		else
		{
			correct = false;
		}
	}

	for (int i = 0; i <= 15; i++)
	{
		sum = sum + sudoku[i];
	}

	if (correct == true)
	{
		if (sum == 40)
		{
			correct = true;
		}
		else
		{
			correct = false;

		}
	}

	return(correct);
}

int randomNumber()
{ //Returns a random number between 1 and 4
	int x = (rand() % 4) + 1;

	return(x);
}