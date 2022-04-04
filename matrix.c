#include <stdio.h>
#include <stdlib.h>
#include <time.h> //생성한 행열 안에 난수를 넣어주는 time을 쓰기위한 라이브러리

int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matirx_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{
	char command;
	printf("[----- [hankyuwon] [2019037002] -----]\n");

	int row, col;
	srand(time(NULL)); //난수 생성(seed가 time으로 실행 시간에 따라 난수가 계속 다르게 생성된다.)

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);
	int** matrix_a = create_matrix(row, col); //matrix_a,matrix_b,matrix_a_t 생성(create_matrix함수는 단순히 행 렬값을 받아서 메모리 할당해주는 함수)
	int** matrix_b = create_matrix(row, col);
	int** matrix_a_t = create_matrix(col, row);
 
	printf("Matrix created.\n");

	if (matrix_a == NULL || matrix_b == NULL) { //matrix_a 혹은 matrix_b가 메모리 할당에 실패했을경우 에러
		return -1;
	}

    do{
        printf("----------------------------------------------------------\n"); //do while문으로 반복
        printf("                  Matrix Manipulation                     \n");
        printf("----------------------------------------------------------\n");
        printf(" Initialize Matrix  = z             Print Matrix      = p \n");
        printf(" Add Matrix         = a             Subtract Matrix   = s \n");
        printf(" Transpose matrix_a = t             Multiply Matrix   = m \n");
        printf(" Quit               = q\n");
        printf("----------------------------------------------------------\n");

        printf("Commad = ");
        scanf(" %c",&command); //command를 받는다. 여기서 command는 z,p,a,s,t,m,q이며 switch문을 통해 구분

        switch(command){
            case'z':case'Z': //commad가 z 혹은 Z 일 경우 break;전까지 실행. fill_data 등 함수에 대한 설명은 아래 함수부분에서 설명.
            printf("Matrix Initialized\n");
            fill_data(matrix_a,row,col);
            fill_data(matrix_b,row,col);
            break;
            case'p':case'P': // 이하 동문
            printf("print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a,row,col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
            case'a':case'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a,matrix_b,row,col);
            break;
            case's':case'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a,matrix_b,row,col);
            break;
            case't':case'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a,matrix_a_t,col,row);
            print_matrix(matrix_a_t,col,row);
            break;
            case'm':case'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a,matrix_a_t,col,row);
            multiply_matrix(matrix_a,matrix_a_t,row,col);
            break;
            case'q':case'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t,col,row);
            free_matrix(matrix_a,row,col);
            free_matrix(matrix_b,row,col);
            break;
            default: //지정된 command 이외에 다른 값이 들어간 경우 다음 break;가 나오기 전까지의 문장 실행. 이후 do while에 의하여 do 처음으로 돌아감
            printf("\n          >>>>> Connection!! <<<<<       \n");
            break;
        }

    }while(command !='q' && command !='Q'); //command가 q || Q 인 경우 do while문 종료

    return 1;
}

int** create_matrix(int row, int col) // create_matrix(메모리 할당)
{
    if(row<=0||col<=0){ //행 열 입력값이 0보다 작은경우 return NULL
        printf("Check the size of row and col!\n");
        return NULL;
    }

  int** matrix=(int**)malloc(sizeof(int*)*row); //행렬(2차원 배열)에 대한 동적메모리 할당. row 값에 해당하는 부분을 2차원 배열로 생각, 
  //col 값에 해당하는 부분을 1차원 배열로 생각하고 메모리 할당을 해준다.
  for(int i=0;i<row;i++)
  {
      matrix[i]=(int*)malloc(sizeof(int)*col);
  }

  if(matrix==NULL) //matrix 에 메모리 할당이 제대로 됐는지 체크
  {
      printf("Memory Allocation Failed.\n");
      return NULL;
  }
  return matrix;
}

void print_matrix(int** matrix, int row, int col) // print_matrix(matrix 2차원 배열을 print)
{

    if(row<=0||col<=0) //row 값과 col 값 확인을 통해 알맞은 값이 들어갔는지 확인. 함수의 형태가 void이므로 반환값이 없다.
    {
        printf("Check the size of row and col!\n");
        return;
    }

    for(int i=0;i<row;i++) //matrix[0][0]~matrix[row-1][col-1]을 출력하기위해 for문 두개를 돌려 print해준다.
    {
        for(int j=0;j<col;j++)
        {
            printf("%3d",matrix[i][j]); //아래 fill_data 함수에서 행 열에 각각 값을 최대 2자리 수를 넣어줬다. 숫자의 구분/행,열의 구분을 위해 %3d로 출력
        }
        printf("\n");
    }
    printf("\n");

    if(matrix==NULL) //동적 메모리 할당이 제대로 됐는지 NULL체크를 통해 확인
    {
        printf("Memory Allocation Failed.\n");
        return;
    }

    return;
}

int free_matrix(int** matrix, int row, int col) //free_matrix(메모리 해제)
{
    if(row<=0||col<=0) //row, col 값이 0 이하로 입력됐는지 확인. < 에러
    {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for(int i=0;i<row;i++) //2차원 배열(행열)을 메모리 해제. 행열의 가로부분 matrix[??] 부분부터 메모리 해제. 이후 세로 부분 matrix 메모리 해제.
    {
        free(matrix[i]);
    }
    free(matrix);
    return 1;
}

int fill_data(int** matrix, int row, int col) //fill_data(행열 안에 난수 값 채워넣기)
{
    if(row<=0||col<=0) //row, col 값이 0 이하로 입력됐는지 확인. < 에러
    {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            matrix[i][j]=rand()%20; //행열의 값에 난수값 넣어줌. rand 값은 0~32767로 편의를 위해 0~20의 수를 채워넣어주기 위해 rand()%20.
        }
    }

    if(matrix==NULL){ //동적 메모리 할당이 제대로 됐는지 NULL 체크를 통해 확인
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    return 1;
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) //additional_matrix(matrix_a+matrix_b)
{
    int** matrix_sum=create_matrix(row,col); //matrix_sum 행열을 새로 만들고, 동적 메모리 할당을 통해 공간을 새로 생성

    if(row<=0||col<=0) //row, col 값 체크
    {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for(int i=0;i<row;i++) //matrix_sum=matrix_a+matrix_b 단순 연산
    {
        for(int j=0;j<col;j++)
        {
            matrix_sum[i][j]=matrix_a[i][j]+matrix_b[i][j];
        }
    }

        if(matrix_a==NULL||matrix_b==NULL||matrix_sum==NULL) //matrix_a, matrix_b, matrix_sum NULL체크를 통해 메모리 할당 확인
        {
            printf("Memory Allocation Failed.\n");
            return -1;
        }

        for(int i=0;i<row;i++) //matrix_sum 출력. additional_matrix이후 출력해주는 함수가 없으므로 additional_matrix에 출력해주는 기능을 넣어줌.
        {
            for(int j=0;j<col;j++)
            {
                printf("%3d",matrix_sum[i][j]);
            }
            printf("\n");
        }

        return 1;
    
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) //matrix_sub(matrix_a-matrix_b)
{
    int** matrix_sub=create_matrix(row,col); //matrix_sub 행열을 새로 만들고 메모리 할당
   
    if(row<=0||col<=0) //row, col 값 체크
    {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for(int i=0;i<row;i++) //matrix_sub=matrix_a-matrix_b 단순 연산
    {
        for(int j=0;j<col;j++)
        {
            matrix_sub[i][j]=matrix_a[i][j]-matrix_b[i][j];
        }
    }

    if(matrix_a==NULL||matrix_b==NULL||matrix_sub==NULL) //matrix_a, matrix_b, matrix_sub 메모리 할당이 제대로 됐는지 확인
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    for(int i=0;i<row;i++) //matrix_sub 출력
    {
        for(int j=0;j<col;j++)
        {
            printf("%3d",matrix_sub[i][j]);
        }
        printf("\n");
    }
    return 1;
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col) //transpose_matrix(전치행렬로 만들기 함수)
{
    if(row<0||col<=0) //row, col 값 체크
    {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for(int i=0;i<row;i++) //matrix_a에서 행, 열값만 바꿔주면 전치행렬 matrix_a_t 생성완료
    {
        for(int j=0;j<col;j++)
        {
            matrix_t[i][j]=matrix[j][i];
        }
    }

    if(matrix==NULL||matrix_t==NULL) //메모리 할당이 제대로 됐는지 확인
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    return 1;
}

int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) // multiply_matrix(행렬의 곱셈)
{
    int** multiply_matrix=create_matrix(row,row); // 행열의 곱셈 값을 넣어줄 multiply_matrix 행렬 생성

    if(row<=0||col<=0) //row, col 값 체크
    {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for(int i=0;i<row;i++) // 행렬의 곱 연산(multiply_matirix[0][0]=matrix_a[0][0]*matrix_a_t[0][0]+matrix_a[1][0]*matrix_a_t[0][1]+
    //matrix_a[2][0]*matrix_a_t[0][2]+matrix_a[row][0]*matrix_a_t[0][row]로 일정한 규칙이 있음)
    {
        for(int j=0;j<row;j++) // matrix_a 와 matrix_a_t의 곱이므로 행,열 값이 서로 같음. 따라서 for문에서 둘다 row까지 증가.
       {
           int multiply=0;
           for(int k=0;k<col;k++)
        {
            multiply+=matrix_a[i][k]*matrix_t[k][j]; //multiply_matrix[i][j]=matrix_a[0][0]*matrix_a_t[0][0]+matrix_a[1][0]*matrix_a_t[0][1]+...+
            //matrix_a[i][row]*matrix_a_t[row][j] 이므로 각각의 곱을 계속하여 더함
        }
        multiply_matrix[i][j]=multiply; //각각의 곱을 더한값을 multiply_matrix[i][j] 값에 넣어줌.
       }
    }

    if(matrix_t==NULL||multiply_matrix==NULL) //메모리 할당이 제대로 됐는지 확인
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    for(int i=0;i<row;i++) //multiply_matrix 출력
    {
        for(int j=0;j<row;j++)
        {
            printf("%5d",multiply_matrix[i][j]);
        }
        printf("\n");
    }

    return 1;
}
