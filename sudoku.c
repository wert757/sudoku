#include <stdio.h>

#define SIZE 9
#define UNASSIGNED 0

int board[9][9] =  {{5,3,0,0,7,0,0,0,0},
                    {6,0,0,1,9,5,0,0,0},
                    {0,9,8,0,0,0,0,6,0},
                    {8,0,0,0,6,0,0,0,3},
                    {4,0,0,8,0,3,0,0,1},
                    {7,0,0,0,2,0,0,0,6},
                    {0,6,0,0,0,0,2,8,0},
                    {0,0,0,4,1,9,0,0,5},
                    {0,0,0,0,8,0,0,7,9}};

void printBoard()
{
    int i,j;
    for(i = 0; i < SIZE; i++)
    {
        for(j=0;j<SIZE;j++)
        {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
}

int unassigned(int *row, int *col)
{
    int num_unassign = 0;
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            if(board[i][j] == 0)
            {
                *row = i;
                *col = j;
                num_unassign = 1;
                return num_unassign;
            }
        }
    }
    return num_unassign;
}

int safe(int n, int r, int c)
{
    int i, j;
    for(i=0;i<SIZE;i++)
    {
        if(board[r][i] == n) //checking for the row
            return 0;
    }
    for(i=0;i<SIZE;i++)
    {
        if(board[i][c] == n) // checking for the column
            return 0;
    }
    int row_start = (r-r%3);        //checking the sub matrix
    int col_start = (c-c%3);
    for(i=row_start;i<row_start+3;i++)
    {
        for(j=col_start;j<col_start+3;j++)
        {
            if(board[i][j] == n)
                return 0;
        }
    }
    return 1;
}

int solve()
{
    int row;
    int col;

    if(unassigned(&row, &col) == 0) // if all the cases are filled then the sudoku is already solved
        return 1;
    
    int n,i;
    for(i=1;i<=SIZE;i++)
    {
        if(safe(i, row, col))
        {
            board[row][col] = i;
            //now we backtrack
            if(solve())
                return 1;
            board[row][col] = 0;
        }
    }
    return 0;
}

int main()
{
    if (solve())
        printBoard();
    else
    {
        printf("rip:( no solution\n");
    }

    return 0;
    
}