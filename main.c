#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void run1();
int **traditionalMatrixMultiplation(int size, int **A,int **B, int **C);
int **strassensMatrixMultiplication(int size, int **A,int **B, int **C, int breakpoint);
void printMatrix(int size, int **C);
void freeMatrix(int row, int **C);
int returnRequiredSize(int currentLength);
int **paddedStrassen(int requiredSize, int size, int **A, int **B, int **C, int breakpoint);
void generateReadingsForBreakpoints();
void improvedAlgo();

int main()
{
        run1();

    return 0;
}

void run1(){
    int i,j;
    int size = 5;
    int A[5][5] = {{1,2,3,4,4},{4,2,5,1,-12},{7,2,9,0,32},{12,45,61,8,33},{4,-2,5,10,3}};
    int B[5][5] = {{1,2,3,4,45},{4,2,5,1,3},{7,2,9,0,21},{12,45,61,8,-19},{-4,0,18,15,23}};

    int **C, **A1, **B1;
    C = malloc(size * sizeof(int)) ;
    A1 = malloc(size * sizeof(int)) ;
    B1 = malloc(size * sizeof(int)) ;
    for(i = 0; i < size; i++){
        C[i] = malloc(size * sizeof(int));
        A1[i] = malloc(size * sizeof(int));
        B1[i] = malloc(size * sizeof(int));
    }

    for( i = 0; i < size; i++){
        for( j =0 ; j < size; j++){
            A1[i][j] = A[i][j];
            B1[i][j] = B[i][j];
        }
    }

    clock_t t = clock();
    printf("Using Traditional matrix multiplication method:\n");
    C = traditionalMatrixMultiplation(size,A1,B1,C);
    t = clock() - t;
    double time = ((double)t/CLOCKS_PER_SEC); //time in ms
    printf(" Time taken: %10f sec\n\n",time);
    printMatrix(size, C);


    t = clock();
    printf("\nUsing Strassen's matrix multiplication Algorithm:\n");
    int requiredSize = returnRequiredSize(size);
    C = paddedStrassen(requiredSize, size, A1, B1, C, -1);
    t = clock() - t;
    time = ((double)t/CLOCKS_PER_SEC); //time in ms
    printf(" Time taken: %10f sec\n\n",time);
    printMatrix(size, C);


    freeMatrix(size, C);
    freeMatrix(size, A1);
    freeMatrix(size, B1);

    generateReadingsForBreakpoints();

    improvedAlgo();
}

int returnRequiredSize(int currentLength){
    int divisor = 1;
    while(currentLength % divisor != currentLength){
        divisor *= 2;
        if(divisor == currentLength)
            return divisor;
    }
    return divisor;
}

void freeMatrix(int row, int **C){
    int i;
    for( i = 0; i < row; i++){
       free(C[i]);
    }
    free(C);
}

void printMatrix(int size, int **C){
    int i,j;
    for( i = 0; i < size; i++){
        for( j =0 ; j < size; j++){
            printf("%5d", C[i][j]);
            printf(" ");
        }
        printf("\n");
    }

}

int **traditionalMatrixMultiplation(int size, int **A,int **B, int **C){
    //int C[size][size];
    int i,j,k;
    for( i = 0; i < size; i++){
        for( j = 0; j < size; j++){
                C[i][j] = 0;
            for( k = 0; k < size; k++){
                C[i][j] = C[i][j] + A[i][k]*B[k][j];
            }
        }
    }
    return C;
}

int **strassensMatrixMultiplication(int size, int **A,int **B, int **C, int breakpoint){
    int i,j,newSize = size/2;
    if(newSize == 0){
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int **M1,**M2,**M3,**M4,**M5,**M6,**M7, **a, **d, **e, **h;
    int **S1,**S2,**S3,**S4,**S5,**S6,**S7, **S8, **S9, **S10;
    M1 = malloc(newSize * sizeof(int));
    M2 = malloc(newSize * sizeof(int));
    M3 = malloc(newSize * sizeof(int));
    M4 = malloc(newSize * sizeof(int));
    M5 = malloc(newSize * sizeof(int));
    M6 = malloc(newSize * sizeof(int));
    M7 = malloc(newSize * sizeof(int));
    S1 = malloc(newSize * sizeof(int));
    S2 = malloc(newSize * sizeof(int));
    S3 = malloc(newSize * sizeof(int));
    S4 = malloc(newSize * sizeof(int));
    S5 = malloc(newSize * sizeof(int));
    S6 = malloc(newSize * sizeof(int));
    S7 = malloc(newSize * sizeof(int));
    S8 = malloc(newSize * sizeof(int));
    S9 = malloc(newSize * sizeof(int));
    S10 = malloc(newSize * sizeof(int));
    a = malloc(newSize * sizeof(int));
    d = malloc(newSize * sizeof(int));
    e = malloc(newSize * sizeof(int));
    h = malloc(newSize * sizeof(int));
    for(i = 0; i < newSize; i++){
        M1[i] = malloc(newSize * sizeof(int));
        M2[i] = malloc(newSize * sizeof(int));
        M3[i] = malloc(newSize * sizeof(int));
        M4[i] = malloc(newSize * sizeof(int));
        M5[i] = malloc(newSize * sizeof(int));
        M6[i] = malloc(newSize * sizeof(int));
        M7[i] = malloc(newSize * sizeof(int));
        S1[i] = malloc(newSize * sizeof(int));
        S2[i] = malloc(newSize * sizeof(int));
        S3[i] = malloc(newSize * sizeof(int));
        S4[i] = malloc(newSize * sizeof(int));
        S5[i] = malloc(newSize * sizeof(int));
        S6[i] = malloc(newSize * sizeof(int));
        S7[i] = malloc(newSize * sizeof(int));
        S8[i] = malloc(newSize * sizeof(int));
        S9[i] = malloc(newSize * sizeof(int));
        S10[i] = malloc(newSize * sizeof(int));
        a[i] = malloc(newSize * sizeof(int));
        d[i] = malloc(newSize * sizeof(int));
        e[i] = malloc(newSize * sizeof(int));
        h[i] = malloc(newSize * sizeof(int));
    }

    for(i = 0; i < newSize; i++){
        for(j = 0; j < newSize; j++){
                a[i][j] = A[i][j];
				d[i][j] = A[newSize + i][newSize + j];
				e[i][j] = B[i][j];
				h[i][j] = B[newSize + i][newSize + j];

				 S1[i][j] = B[i][newSize + j] - B[newSize + i][newSize + j];
				 S2[i][j] = A[i][j] + A[i][newSize + j];
				 S3[i][j] = A[newSize + i][j] + A[newSize + i][newSize + j];
				 S4[i][j] = B[newSize + i][j] - B[i][j];//g-e
				 S5[i][j] = A[i][j] + A[newSize + i][newSize + j];//a+d
				 S6[i][j] = B[i][j] + B[newSize + i][newSize + j];//e + h
				 S7[i][j] = A[i][newSize + j] - A[newSize + i][newSize + j];//b-d
				 S8[i][j] = B[newSize + i][j] + B[newSize + i][newSize + j]; //g+h
				 S9[i][j] = A[i][j] - A[newSize + i][j];//a-c
				 S10[i][j] = B[i][j] + B[i][newSize + j];//e+f
        }
    }

    if(newSize > breakpoint){
        M1 = strassensMatrixMultiplication(newSize, a, S1, M1, breakpoint);
        M2 = strassensMatrixMultiplication(newSize, S2, h, M2, breakpoint);
        M3 = strassensMatrixMultiplication(newSize, S3, e, M3, breakpoint);
        M4 = strassensMatrixMultiplication(newSize, d, S4, M4, breakpoint);
        M5 = strassensMatrixMultiplication(newSize, S5, S6, M5, breakpoint);
        M6 = strassensMatrixMultiplication(newSize, S7, S8, M6, breakpoint);
        M7 = strassensMatrixMultiplication(newSize, S9, S10, M7, breakpoint);
    }else{
        M1 = traditionalMatrixMultiplation(newSize, a, S1, M1);
        M2 = traditionalMatrixMultiplation(newSize, S2, h, M2);
        M3 = traditionalMatrixMultiplation(newSize, S3, e, M3);
        M4 = traditionalMatrixMultiplation(newSize, d, S4, M4);
        M5 = traditionalMatrixMultiplation(newSize, S5, S6, M5);
        M6 = traditionalMatrixMultiplation(newSize, S7, S8, M6);
        M7 = traditionalMatrixMultiplation(newSize, S9, S10, M7);
    }

    for( i = 0; i < newSize; i++){
		for( j = 0; j < newSize; j++){
				C[i][j] = M5[i][j] + M4[i][j] - M2[i][j] + M6[i][j];//C11[i][j];
				C[i][newSize + j] = M1[i][j] + M2[i][j];//C12[i][j];
				C[newSize + i][j] = M3[i][j] + M4[i][j];//C21[i][j];
				C[newSize + i][newSize + j] = M1[i][j] + M5[i][j] - M3[i][j] - M7[i][j];//C22[i][j];
        }
    }

    freeMatrix(newSize,M1);
    freeMatrix(newSize,M2);
    freeMatrix(newSize,M3);
    freeMatrix(newSize,M4);
    freeMatrix(newSize,M5);
    freeMatrix(newSize,M6);
    freeMatrix(newSize,M7);
    freeMatrix(newSize,S1);
    freeMatrix(newSize,S2);
    freeMatrix(newSize,S3);
    freeMatrix(newSize,S4);
    freeMatrix(newSize,S5);
    freeMatrix(newSize,S6);
    freeMatrix(newSize,S7);
    freeMatrix(newSize,S8);
    freeMatrix(newSize,S9);
    freeMatrix(newSize,S10);
    freeMatrix(newSize,a);
    freeMatrix(newSize,d);
    freeMatrix(newSize,e);
    freeMatrix(newSize,h);

    return C;
}

int **paddedStrassen(int requiredSize, int size, int **A, int **B, int **C, int breakpoint){
    int i,j;
    if(requiredSize != size){
         int **As = malloc(requiredSize * sizeof(int));
         int **Bs = malloc(requiredSize * sizeof(int));
         int **D = malloc(requiredSize * sizeof(int));
         for(i=0; i<requiredSize; i++){
            As[i] = malloc(requiredSize * sizeof(int));
            Bs[i] = malloc(requiredSize * sizeof(int));
            D[i] = malloc(requiredSize * sizeof(int));
         }
         for( i = 0; i < requiredSize; i++){
            for( j =0 ; j < requiredSize; j++){
                if(i < size && j < size){
                    As[i][j] = A[i][j];
                    Bs[i][j] = B[i][j];
                    D[i][j] = C[i][j];
                }else{
                    As[i][j] = 0;
                    Bs[i][j] = 0;
                    D[i][j] = 0;
                }
            }
        }
        D = strassensMatrixMultiplication(requiredSize,As,Bs,D,breakpoint);
        for(i = 0; i < size; i++){
            for(j=0; j < size; j++){
                C[i][j] = D[i][j];
            }
        }
        freeMatrix(requiredSize,As);
        freeMatrix(requiredSize,Bs);
        freeMatrix(requiredSize,D);
    }else{
        C = strassensMatrixMultiplication(size, A, B, C, breakpoint);
    }
    return C;
}

void generateReadingsForBreakpoints(){
    int size = 1;
    printf("\n______________________________________________________________________________________________________\n");
    printf("%5s      %-12s   %-12s   %-12s   %-12s   %-12s   %-12s","N","16","32","64","128","256","512");
    printf("\n______________________________________________________________________________________________________\n");
    while(size <= 2048){
        size *= 2;
        int i,j;
        int **C, **A, **B;
        C = malloc(size * sizeof(int)) ;
        A = malloc(size * sizeof(int)) ;
        B = malloc(size * sizeof(int)) ;
        for(i = 0; i < size; i++){
            C[i] = malloc(size * sizeof(int));
            B[i] = malloc(size * sizeof(int));
            A[i] = malloc(size * sizeof(int));
        }

        for(i = 0; i < size; i++){
            for(j = 0; j < size; j++){
                A[i][j] = rand()%200;
                B[i][j] = rand()%200;
            }
        }
        int requiredSize = returnRequiredSize(size);
        int breakPoint = 16;
        printf("%5d   ",size);
        while(breakPoint <= 512){
            clock_t t = clock();
            C = paddedStrassen(requiredSize, size, A, B, C, breakPoint);
            t = clock() - t;
            double time = ((double)t/CLOCKS_PER_SEC); //time in ms
            //printf("size: %d N \nBP: %d\ntime: %f ms\n____________\n", size, breakPoint, time);
            printf(" %10f sec",time);
            breakPoint *= 2;
        }
        printf("\n");
        freeMatrix(size,C);
        freeMatrix(size,A);
        freeMatrix(size,B);
    }
}

void improvedAlgo(){
    int breakPoint = -1;
    puts("Please Enter a suitable Breakpoint based on above observations");
    scanf("%d", &breakPoint);
    //gets(breakPoint);

    int size = 1;
    while(size <= 2048){
        size *= 2;
        int i,j;
        int **C, **A, **B;
        C = malloc(size * sizeof(int)) ;
        A = malloc(size * sizeof(int)) ;
        B = malloc(size * sizeof(int)) ;
        for(i = 0; i < size; i++){
            C[i] = malloc(size * sizeof(int));
            B[i] = malloc(size * sizeof(int));
            A[i] = malloc(size * sizeof(int));
        }

        for(i = 0; i < size; i++){
            for(j = 0; j < size; j++){
                A[i][j] = rand()%200;
                B[i][j] = rand()%200;
            }
        }
        int requiredSize = returnRequiredSize(size);
        printf("___________\nSize: %-5d   \n",size);
        clock_t t = clock();
        C = paddedStrassen(requiredSize, size, A, B, C, breakPoint);
        t = clock() - t;
        double time = ((double)t/CLOCKS_PER_SEC); //time in ms
        printf("Improved-Time: %-10f sec",time);
        printf("\n");

        t = clock();
        C = traditionalMatrixMultiplation(size, A, B, C);
        t = clock() - t;
        time = ((double)t/CLOCKS_PER_SEC); //time in ms
        printf("Traditional-Time: %-10f sec",time);
        printf("\n");

        t = clock();
        C = paddedStrassen(requiredSize, size, A, B, C, -1);
        t = clock() - t;
        time = ((double)t/CLOCKS_PER_SEC); //time in ms
        printf("Stressen's-Time: %-10f sec",time);
        printf("\n");

        freeMatrix(size,C);
        freeMatrix(size,A);
        freeMatrix(size,B);
    }
    puts("Press Enter to Quit");
    char c[10];
    gets(c);
}
