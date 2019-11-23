#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>


//declaring int variables for Matrice dimentions
int Row1, Column1, Row2,Column2;

//declaring pointers for Matrices

int Matrice1[5000][5000];
int Matrice2[5000][5000];
int MatriceAnsrSingle[5000][5000];
int MatriceAnsrMThrd[5000][5000];


//Thread
void * Multi_Thread_Woker( void *arg )
{
  int i, j, k, tid, portion_size, row_start, row_end;
  double sum;

  tid = *(int *)(arg); // get the thread ID assigned sequentially.
  portion_size = Row2 / Column1;
  row_start = tid * portion_size;
  row_end = (tid+1) * portion_size;

  for (i = row_start; i < row_end; ++i) { // hold row index of 'matrix1'
    for (j = 0; j < Column2; ++j) { // hold column index of 'matrix2'
      sum = 0; // hold value of a cell
      /* one pass to sum the multiplications of corresponding cells
	 in the row vector and column vector. */
      for (k = 0; k < Column1; ++k) {
	sum += Matrice1[ i ][ k ] * Matrice2[ k ][ j ];
      }
      MatriceAnsrMThrd[ i ][ j ] = sum;
    }
  }
}




void MatricesRandomValues();
void MatricesPrint();
void Read_Txt_Matrices();
void Write_Txt_Matrices();
void MatricesMultiply();
void MatriceMultiTread_Driver();

int main()
{

  printf("%s\n","----------------------------------" );
  printf("%s\n","|   Matrixes  Multiplication     |" );
  printf("%s\n","----------------------------------" );


  //  Multiplication time calculatations
         struct timeval tstart, tend;
         struct timeval tstart1, tend1;
         double exectime;



  // getting values for Rows and Column

   printf("%s\n","\n#1st Matrice" );
   printf("%s"  ," Inter Row value of   1st Matrice  : " );
   scanf("%d",&Row1);

  printf("%s"    ," Inter Column value of 1st Matrice : " );
  scanf("%d", &Column1);

   printf("%s\n","\n#2nd Matrice" );
   printf("%s"  ," Inter Row value of    2st   Matrice : " );
   scanf("%d",&Row2 );

   printf("%s"  ," Inter Column value of  2st Matrice  : " );
   scanf("%d",&Column2 );

    printf("%s\n","\n-----------------------------------------------------------" );

    if(Column1==Row2){

        printf("[%d][%d]  x [%d][%d]  are Maltiplicable Matrices \n",Row1,Column1,Row2,Column2 );


        printf("----------------------------------------------------------------\n");
        printf("%s\n","Fill the matrix with the values given in a file [1]");
        printf("%s\n","Fill the matrix with random values              [2] ");
        int Schr;
        printf("\n%s","Select the Option : ");
        scanf("%d",&Schr);

        if(Schr==1)
        {

            printf("\n%s\n", " Txt Read Matrices" );
            Read_Txt_Matrices();

                     printf("%s\n","Single Thread  " );


                       gettimeofday( &tstart, NULL );// Getting Start time ;

                      MatricesMultiply();

                      gettimeofday( &tend, NULL );

                     exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
                     exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms

                     printf("%s\n","___________________________________________________________");
                     printf("%s %.3lf %s\n ","  Time taken for Single Thread  :  " ,exectime/1000.0 ,"s"  );
                     printf("%s\n","___________________________________________________________");


                      gettimeofday( &tstart1, NULL );// Getting Start time ;

                      MatriceMultiTread_Driver();
                      gettimeofday( &tend1, NULL );

                      exectime = (tend1.tv_sec - tstart1.tv_sec) * 1000.0; // sec to ms
                      exectime += (tend1.tv_usec - tstart1.tv_usec) / 1000.0; // us to ms


                      printf("%s\n","________________________________________________________");
                      printf("%s %.3lf %s\n ","  Time taken for MultiThread  :  " ,exectime/1000.0,"s"  );
                      printf("%s\n","________________________________________________________");

                      Write_Txt_Matrices();


        }else if(Schr==2)
        {

          // assging Random values to 2 MatricesRandomValues

          MatricesRandomValues();
        //  MatricesPrint();

                   printf("%s\n","Single Threading" );

                   gettimeofday( &tstart, NULL );// Getting Start time ;

                   MatricesMultiply();
                  gettimeofday( &tend, NULL );

                  exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
                  exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms


                   printf("%s\n","_________________________________________________________________________________________________");
                   printf("%s %.3lf %s\n ","  Time taken for Single Thread  :  " ,exectime/1000.0,"s"  );
                   printf("%s\n","_________________________________________________________________________________________________");

                   printf("%s\n","Multithread");

                   gettimeofday( &tstart1, NULL );// Getting Start time ;

                  MatriceMultiTread_Driver();

                  gettimeofday( &tend1, NULL );

                  exectime = (tend1.tv_sec - tstart1.tv_sec) * 1000.0; // sec to ms
                  exectime += (tend1.tv_usec - tstart1.tv_usec) / 1000.0; // us to ms

                  printf("%s\n","_________________________________________________________________________________________________");
                  printf("%s %.3lf %s\n ","  Time taken for MultiThread  :  " ,exectime/1000.0,"s"  );
                  printf("%s\n","_________________________________________________________________________________________________");

                  Write_Txt_Matrices();



        }else{
            printf("%s\n"," Invalid Input ");
            return 0;
        }


        printf("%s\n","Exit()......................");


  }else
  {
       printf("[%d][%d]  x [%d][%d]  are not Maltiplicable \n",Row1,Column1,Row2,Column2 );
       return 0;
  }

  return 0;
}




//Print Matrices
void MatricesPrint()
{

   printf("\n%s\n","------1st Matrice----- ");

  for (int i=0; i<Row1; i++)
  {
    for (int j=0; j<Column1; j++)
    {
      printf(" %d ",Matrice1[i][j] );
    }
    printf("\n");
  }

     printf("\n%s\n","------2nd Matrice----- ");

  for (int i=0; i<Row2; i++)
  {
    for (int j=0; j<Column2; j++)
    {
      printf(" %d ",Matrice2[i][j] );
    }
    printf("\n");
  }


}

//assging Random Values to 2 Matrices

void MatricesRandomValues()
{

  for (int i=0; i<Row1; i++)
  {
      for (int j=0; j<Column1; j++)
      {
         Matrice1[i][j] = rand() % 20;
      }
  }


  for (int i=0; i<Row2; i++)
  {
      for (int j=0; j<Column2; j++)
      {
         Matrice2[i][j] = rand() % 20;
      }
  }

}

void Read_Txt_Matrices()
{

  FILE *infile;

  infile = fopen("filein.txt", "r");

  if(infile == NULL)
  {
      printf("Error opening file\n");
      exit(1);
  }

  printf("Testing fscanf() function: \n\n");

  for(int i=0;i<Row1;i++){

     for(int j=0;j<Column1;j++){

         fscanf(infile,"%d,",&Matrice1[i][j]);

     }

  }


  for(int i=0;i<Row2;i++){

     for(int j=0;j<Column2;j++){

         fscanf(infile,"%d,",&Matrice2[i][j]);

     }

  }


  fclose(infile);

}


void Write_Txt_Matrices()
{

  FILE *outfile;

  outfile = fopen("outfile.txt","w");

  if(outfile == NULL)
  {
      printf("Error writing file\n");
      exit(1);
  }

//  printf("Testing fprintf() function: \n\n");
  fprintf(outfile,"%s\n"," Matrices 1");

  for(int i=0;i<Row1;i++){

     for(int j=0;j<Column1;j++){

         fprintf(outfile," %d ",Matrice1[i][j]);

     }
       fprintf(outfile,"\n");
  }

fprintf(outfile,"\n%s\n"," Matrices 2");

  for(int i=0;i<Row2;i++){

     for(int j=0;j<Column2;j++){

         fprintf(outfile," %d ",Matrice2[i][j]);

     }
       fprintf(outfile,"\n");
  }

    fprintf(outfile,"\n%s\n"," Multiplied Matrices Single Thread ");

    for(int i=0;i<Row2;i++){

       for(int j=0;j<Column2;j++){

           fprintf(outfile," %d ",MatriceAnsrSingle[i][j]);

       }
         fprintf(outfile,"\n");
    }

    fprintf(outfile,"\n%s\n"," Multiplied Matrices Multi Thread ");

    for(int i=0;i<Row2;i++){

       for(int j=0;j<Column2;j++){

           fprintf(outfile," %d ",MatriceAnsrMThrd[i][j]);

       }
         fprintf(outfile,"\n");
    }


  fclose(outfile);

}


void MatricesMultiply()
{
  	int i, j, k;

	// Multiplying matrix

	   for(i = 0; i < Row1; ++i)
    	{
     	   	for(j = 0; j < Column2; ++j)
	       	{
		       	  for(k=0; k<Column1; ++k)
		       	  {
			          	MatriceAnsrSingle[i][j] += Matrice1[i][k] * Matrice2[k][j];
		       	  }
		      }
    	}


}

void MatriceMultiTread_Driver()
{

  int i;
  pthread_t * threads;
  //int size = atoi( argv[1] );
  int num_threads = Row1;
  threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t) );
  for ( i = 0; i < num_threads; ++i ) {
    int *tid;
    tid = (int *) malloc( sizeof(int) );
    *tid = i;
    pthread_create( &threads[i], NULL, Multi_Thread_Woker, (void *)tid );
  }

  for ( i = 0; i < num_threads; ++i ) {
    pthread_join( threads[i], NULL );
  }


}
