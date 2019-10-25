//
//  main.c
//  matrixthread
//
//  Created by karim fathy on 11/19/18.
//  Copyright © 2018 Fetouh. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
int rowA,columnA,rowB,columnB;
int matrixA[100][100],matrixB[100][100],matrixC1[100][100],matrixC2[100][100];

typedef struct
{int row;
    int column;
}argo;
argo    RandC[100];


void output1(double time)
{
    FILE *fp;
    fp = fopen("/Users/fetouh/Desktop/matrixthread/output1.txt", "w");
    for(int i=0; i<rowA; i++)
    { for(int j=0; j<columnB;j++)
    {
        fprintf(fp,"%d\t",matrixC1[i][j]);
    }
       fprintf(fp,"\n");
        
        
        
    }
     fprintf(fp,"%f",time);
    
    
    
    
    
    
    
    
}
void output2(double time)
{
    FILE *fp;
    fp = fopen("/Users/fetouh/Desktop/matrixthread/output2.txt", "w");
    for(int i=0; i<rowA; i++)
    { for(int j=0; j<columnB;j++)
    {
        fprintf(fp,"%d\t",matrixC2[i][j]);
    }
        fprintf(fp,"\n");
        
        
        
    }
    fprintf(fp,"%f",time);
    
    
    
    
    
    
    
    
}


void* multiply1(void *data)
{
    
    for(int j=0; j<columnB;j++)
    {
        
        for(int k=0;k<rowB;k++)
            matrixC1[(int)data][j]+=matrixA[(int)data][k]*matrixB[k][j];
    }
    
    
    
    
    
    pthread_exit(NULL);
    
}

void* multiply2(void *data)
{
 argo* x=   (argo*)data;
    
    int row= x->row;
    int column=x->column;
         
               for(int k=0;k<rowB;k++)
                   matrixC2[row][column]+=matrixA[row][k]*matrixB[k][column];
    
         
    
    
            
            
   pthread_exit(NULL);
    
}

void getMatrixA()
{      FILE *fp;
    
    fp = fopen("/Users/fetouh/Desktop/matrixthread/matrixA.txt", "r");
    fscanf(fp, "%d %d", &rowA,&columnA);
    
    while(!feof(fp))
    {
        for(int i=0; i<rowA;i++)
        {
            for(int j=0; j<columnA;j++)
                
                fscanf (fp, "%d", &matrixA[i][j]);
            
            
            
        }
       
    }
    
    fclose(fp);
    
}
void getMatrixB()
{      FILE *fp;
    
    fp = fopen("/Users/fetouh/Desktop/matrixthread/matrixB.txt", "r");
    fscanf(fp, "%d %d", &rowB,&columnB);
    
    while(!feof(fp))
    {
        for(int i=0; i<rowB;i++)
        {
            for(int j=0; j<columnB;j++)
                
                fscanf (fp, "%d", &matrixB[i][j]);
            
            
            
        }
        
        
        
        
    }
    
    fclose(fp);
    
}

int main(int argc, const char * argv[]) {
    
    // pthread_t threadsA[number of rows];
    
    
    
    
    getMatrixA();
    getMatrixB();
    if(columnA!=rowB)
    {return 0;}
        clock_t begin = clock();
     pthread_t threads[rowA];    //row
    for (int i = 0; i <rowA ; i++) {
        
        pthread_create(&threads[i], NULL, multiply1, (void *)i);
    }
    for (int i = 0; i < rowA; i++)
        pthread_join(threads[i], NULL);
    
    
    clock_t end = clock();
 double   time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    output1(time_spent);
begin = clock();
     pthread_t threads2[rowA*columnB];//element
int    k=0;
    for (int i = 0; i <rowA ; i++) {
        for (int j = 0; j <columnB ; j++) {
            {RandC[k].row=i;
                RandC[k++].column=j;
                pthread_create(&threads2[k], NULL, multiply2, (void *)&RandC[k]);}
    }
    }
    
    for (int i = 0; i < k; i++)
        pthread_join(threads[i], NULL);
    end = clock();
 time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
     output2(time_spent);
    
   
    return 0;
}
