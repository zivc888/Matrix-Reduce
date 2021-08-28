#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define EPS (1e-6)
#define N (100)
#define M (100)
#define SUCCESS (0)
#define ERROR (1)
//I've added some jokes to the description of functions to lighten up the mood, I hope you don't mind :)
//BTW, parts of the skeleton didn't work (functions got parameters they never used and stuff like that) so I had to edit the skeleton a little bit. I asked Avi about it but he never replied...

double zero_by_threshold(double num, double eps) { //a pre-made function: thanks for doing some work for me!
    return fabs(num) > eps ? num : 0;
}

bool read_sizes(int * n, int * m) { //a self-made function: takes the dimensions of the matrix from the user (and then go to a ranch of free functions in the north)
    if (scanf("%d%d", n, m) != 2) {
        return false;
    }

    return ((*n >= 1) && (*n <= N) && (*m >= 1) && (*m <= M));
}

void print_matrix(double a[][M], int n, int m) { //a pre-made function: thanks again for writing a code which is good, in oppose to mine
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%.2f ", zero_by_threshold(a[i][j], EPS));
        }

        printf("\n");
    }

    printf("\n");
}

bool read_matrix(double a[][M], int n, int m) { //a self-made function: gets all of the values of the matrix from the user
    double temp=0.0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int scan_var=scanf("%lf", &temp);
            if(scan_var==1){
                a[i][j]=temp;
            }
            else{
                return false;
            }
        }
    }

    return true;
}

void swap(double *pm, double *pn){ //a self-made function: switches between 2 pointers
	double temp=*pn;
	*pn=*pm;
	*pm=temp;
}
void swap_rows(double a[][M], int m, int row1, int row2) { //a self-made function: swaps 2 rows in a matrix (it's basically a for loop that contains the swap function)
    for(int i=0; i<m; i++){
        swap(&a[row1][i], &a[row2][i]);
    }
}

void multiply_row(double a[][M], int m, int row, double scalar) { //a self-made function: multiplies an entire row by a constant
    for(int i=0; i<m; i++){
        a[row][i]*=scalar;
    }
}

void add_row_to_row(double a[][M], int m, int row1, int row2, double scalar) { //a self-made function: multiplies one row by a constant, then adding it to another row - it is probably the worst way to do this
    multiply_row(a, m, row1, scalar);
    for(int i=0; i<m; i++){
        a[row2][i]+=a[row1][i];
    }
}

bool find_leading_element(double a[][M], int n, int m, int * row, int * column, int start) { //a self-made function: finds the first non-zero element in the matrix with the lowest column index
    int leader[2]={0, M+1};
    for(int i=start; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j]!=0){
                if(leader[1]>j){
                    leader[0]=i;
                    leader[1]=j;
                }
            }
        }
    }

    if(leader[1]==M+1){
        return false;
    }

    *row=leader[0];
    *column=leader[1];
    return true;
}

void reduce_rows(double a[][M], int n, int m) { //a self-made function: reduces rows as requested in the question (hopefully) and the cause of about 10 hours of my suffering
    for(int i=0; i<n; i++){
        int row, j;
        bool is_lead=find_leading_element(a, n, m, &row, &j, i);
        if(!is_lead){
            return;
        }

        swap_rows(a, m, row, i);
        multiply_row(a, m, i, (double)(1/a[i][j]));

        for(int q=i+1; q<n; q++){
            double scalar = -a[q][j];

            if(scalar!=0){
                add_row_to_row(a, m, i, q, scalar);
                multiply_row(a, m, i, (double)(1/scalar));
            }
        }
    }
}

int main() {
    int n;
    int m;
    printf("Enter matrix size (row and column numbers): ");
    if (!read_sizes(&n, &m)) {
        printf("Invalid sizes!\n");
        return ERROR;
    }

    double a[N][M];
    printf("Enter matrix:\n");
    if (!read_matrix((double (*)[M]) a, n, m)) {
        printf("Invalid matrix!\n");
        return ERROR;
    }

    reduce_rows((double (*)[M]) a, n, m);
    printf("The reduced matrix:\n");
    print_matrix((double (*)[M]) a, n, m);
    return SUCCESS;
}
