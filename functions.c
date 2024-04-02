#include <stdio.h>
#include <stdlib.h> //use this for dynamic memory
#include <time.h>
#include "functions.h"
#include <math.h>
#include <stdbool.h>


//function to generate a random matrix
void generateMatrix(int rows, int cols, double matrix[rows][cols]) 
{

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            matrix[i][j] = (double)rand() / (double)RAND_MAX  *20.0 - 10.0;
            //scales it by 20 and then shifts it down by 10 with double precision
        }
    }
}

//function to print a matrix
void printMatrix(int rows, int cols, double matrix[rows][cols]) 
{
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            //nested for loops accessing the elements of the matrix
            printf("%lf ", matrix[i][j]);
        }
        // prints a new line after each row
        printf("\n");
    }
}
//function to add 2 matrices
void addMatrices(int N1, int M1, double A[N1][M1], int N2, int M2, double B[N2][M2], double result[N1][M1])
{
    for (int i = 0; i < N1; i++) 
    {
        for (int j = 0; j < M1; j++) 
        {
            //add the respective elements of the matrices
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrices(int N1, int M1, double A[N1][M1], int N2, int M2, double B[N2][M2], double result[N1][M1])
{
    for (int i = 0; i < N1; i++) 
    {
        for (int j = 0; j < M1; j++) 
        {  //looop through the matrices and subtract the respecitve elements
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

void multiplyMatrices(int N1, int M1, double A[N1][M1], int N2, int M2, double B[N2][M2], double result[N1][M2])
{
    //matrix miltiplation works by multilying the first matrix row by row with the second matrix column by column then adding 
    for (int i = 0; i < N1; i++) 
    {
        for (int j = 0; j < M2; j++) 
        {
            //set the result matrix to 0
            result[i][j] = 0;

            //multiply the i-th row of A with the j-th column of B
            for (int k = 0; k < M1; k++) 
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


//solving X in aX = b
void solveLinearSystem(int N1, int M1, double A[N1][M1], int N2, int M2, double B[N2][M2], double x[N1][M2])
{
    //create an augmented matrix with A | B
    double augmented[N1][M1+1];
    //fill with values of A
    for (int i = 0; i < N1; i++) 
    {
        for (int j = 0; j < M1; j++) 
        {
            augmented[i][j] = A[i][j];
        
        }
    }

    //fill the last column with values of B
    for (int i = 0; i < N1; i++) 
    {
        augmented[i][M1] = B[i][0];
    }

    //make sure the diagonal is not zero so when perform row operations the pivot is not zero because we need to multiply by itself
    for(int i = 0 ; i < N1; i++)
    {
        double temp = augmented[i][i]; // store the pivot
        for(int j = 0; j < M1+1; j++)
        {
            if(temp == 0) //if the pivot is 0 we need to swap the row with another row that has a pivot thats not zeor 
            {
                for(int k = i+1; k < N1; k++)
                {
                    if(augmented[k][i] != 0) //if the pivot is not 0
                    {
                        for(int l = 0; l < M1+1; l++)
                        {
                            double temp2 = augmented[i][l]; //store the row with the 0 pivot
                            augmented[i][l] = augmented[k][l]; //swap the row with the non zero pivot
                            augmented[k][l] = temp2; //swap the row with the 0 pivot
                        }
                        break;
                    }
                }
            }
           
        }
    }
    //now the pivots are gurantee not zero so we can perform row operations to make the other elements in the column 0 
    //now need to make the other elements in the column 0
    for(int i = 0; i < N1; i++) //lops over each pivot rows
    { 
        for(int j = 0; j < N1; j++) //loops over all the other rows 
        { 
            if(i != j) //skips the pivot itself in making zero
            { 
                double factor = augmented[j][i] / augmented[i][i]; //calculate the factor to make the element in the current column zero
                for(int k = 0; k <= M1; k++) //iterate over each column including the augmented part
                { 
                    augmented[j][k] -= factor * augmented[i][k]; //apply the row operation (minus the factor times the pivot row (1) from the current row to make the element 0 ie subtracting it from itself)
                }
            }
        }


        //normalize the pivot row back by dividing it by itself
        double pivot = augmented[i][i];
        for(int k = 0; k <= M1; k++)  //itterate over the cols
        {  
            augmented[i][k] /= pivot; //divide each element by the pivot to make the diagonal 1 (since all zero has only affect the pivot row)
        }
    }


    //fill the solution matrix with the last column of the augmented matrix
    for(int i = 0; i < N1; i++)
    {
        x[i][0] = augmented[i][M1]; 
        
    }


}

