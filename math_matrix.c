#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include <string.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));

    //check if the number of arguments is correct
    if (argc < 6 || argc > 7) 
    {
        printf("Usage: %s nrows_A ncols_A nrows_B ncols_B <operation> [print]\n", argv[0]);
        // uses argv[0] to print the program name
        return 1;
    }
    int N1= atoi(argv[1]);
    int M1 = atoi(argv[2]);
    int N2 = atoi(argv[3]);
    int M2 = atoi(argv[4]);
    //storing the user input as integers

    //generate random matrices A with size N1*M1 and B with size N2*M2
    double A[N1][M1];
    double B[N2][M2];  //  <---- LINE 25
    generateMatrix(N1, M1, A); 
    generateMatrix(N2, M2, B); 
    
    
    //if the operation is add
    if (strcmp(argv[5], "add") == 0) 
    {
        // the matrixes have to bee the same size to add them so check if they are
        if(N1 != N2 || M1 != M2)
        {
            printf("The matrices can't be added\n");
            return 1;
        }
        double result[N1][M1]; // create a result matrix when addition both matrix are same size
        addMatrices(N1, M1, A, N2, M2, B, result);

        //check if there are more than 6 arguments because if no then print was not incliuded 
        //and then check what the value of the '6' which is 7th argument was as input (print) and use strcmp to scompare it to "add" to see if it's true
        if(argc > 6 && strcmp(argv[6], "print") == 0)
        {
            //prints matrix A
            printf("Matix A:\n");
            printMatrix(N1, M1, A);

            //prints matrix B
            printf("Matix B:\n");
            printMatrix(N2, M2, B);

            //prints result matrix
            printf("Result of A+B:\n");
            printMatrix(N1, M1, result);

        }
    }

    //if the operation is subtract
    else if (strcmp(argv[5], "subtract")==0)
    {
        // the matrices have to be the same size to subtract them so check if they are
        if(N1 != N2 || M1 != M2)
        {
            printf("The matrices can't be subtracted\n");
            return 1;
        }
        double result[N1][M1]; // create a result matrix when subtracting both matrix are same size
        subtractMatrices(N1, M1, A, N2, M2, B, result);
        if(argc > 6 && strcmp(argv[6], "print") == 0)
        {
            //prints matrix A
            printf("Matix A:\n");
            printMatrix(N1, M1, A);

            //prints matrix B
            printf("Matix B:\n");
            printMatrix(N2, M2, B);

            //prints result matrix
            printf("Result of A-B:\n");
            printMatrix(N1, M1, result);

        }
    }

    //if the operation is multiply
    else if (strcmp(argv[5], "multiply") == 0) 
    {
        // the number of columns in the first matrix has to be equal to the number of rows in the second matrix to multiply them so check if they are
        if(M1 != N2)
        {
            printf("The matrices can't be multiplied\n");
            return 1;
        }
        double result[N1][M2]; // create a result matrix when multiplying the number of columns of the first matrix is equal to the number of rows of the second matrix
        multiplyMatrices(N1, M1, A, N2, M2, B, result);
        if(argc > 6 && strcmp(argv[6], "print") == 0)
        {
            
            //prints matrix A
            printf("Matix A:\n");
            printMatrix(N1, M1, A);

            //prints matrix B
            printf("Matix B:\n");
            printMatrix(N2, M2, B);

            //prints result matrix
            printf("Result of A*B:\n");
            printMatrix(N1, M2, result);

        }
    }
    else if(strcmp(argv[5], "solve") == 0)
    {
        //requirments are only for square matrices so check if the matrices are square
        if(N1 != M1 || N1 != N2)
        {
            printf("Invalid Inputs\n");
            return 1;
        }
        if(M2 != 1)
        {
            printf("Invalid Inputs\n");
            return 1;
        }
        double x[N1][M2];
        solveLinearSystem(N1, M1, A, N2, M2, B, x);
        if(argc > 6 && strcmp(argv[6], "print") == 0)
        {   
            //prints matrix A
            printf("Matix A:\n");
            printMatrix(N1, M1, A);

            //prints matrix B
            printf("Matix B:\n");
            printMatrix(N2, M2, B);

            //prints result matrix
            printf("Result of A*X=B when solved for x:\n");
            printMatrix(N1, M2, x);
        }
    }
    else
    {
        printf("Invalid operation\n");
    }

    return 0;
}
