#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **matrix, int row, int column)
{
    for (int i = 0; i < row; i++) // ��� ���� ó������ ������
    {
        for (int j = 0; j < column; j++) // �� ���� ��� ���� ���� ���
        {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(int **matrix, int row)
{
    for (int i = 0; i < row; i++)
        free(matrix[i]); // ������ ��鿡 ���� �޸� ����
    free(matrix);        // 2���� �迭�� ���� �޸� ����
    // ���� �ÿ��� 2���� �迭 matrix�� �Ҵ� �Ŀ� ������ ��鿡 ����
    // 1���� �迭�� �������� �Ҵ��Ͽ����Ƿ� ������ 1����, 2���� ������ ����.
}

// ������ �������� �⺻������ ��� ���� ������ ������ ��.
int **addition_matrix(int **A, int **B, int row, int column) // 2���� �迭�� ���� return������ �޴� �Լ�
{
    int **result = (int **)malloc(sizeof(int *) * row); // A+B�� ������� �����ϱ� ���� result 2���� �迭�� �� �Ҵ�.

    for (int i = 0; i < row; i++) // �Ҵ�� �� �࿡�� �� ������ �߰��� ���� �Ҵ��Ͽ� 2���� �迭�� ����.
        result[i] = (int *)malloc(sizeof(int) * column);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
            result[i][j] = A[i][j] + B[i][j]; // ��� ������ ���ǿ� ���� A+B�� �� ��� ���� �����ϴ� ������ ���� ���Ͽ� ������� ����.
    }
    return result; // �ش� ������� ��ȯ��.
}

int **subtract_matrix(int **A, int **B, int row, int column) // 2���� �迭�� ���� return������ �޴� �Լ�
{
    int **result = (int **)malloc(sizeof(int *) * row); // A-B�� ������� �����ϱ� ���� 2���� �迭�� �� �Ҵ�.

    for (int i = 0; i < row; i++) // �� ��鿡 ���� �� ������ �߰��� ���� �Ҵ��Ͽ� 2���� �迭 ����.
        result[i] = (int *)malloc(sizeof(int) * column);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
            result[i][j] = A[i][j] - B[i][j]; // ��� ������ ���ǿ� ���� A-B�� �� ��� ���� �����ϴ� ������ ���� ���� ������� ����.
    }
    return result; // �ش� ������� ��ȯ��.
}

int **transpose_matrix(int **matrix, int A_row, int A_columm) // 2���� �迭�� ���� return������ �޴� �Լ�
{
    int **result = (int **)malloc(sizeof(int *) * A_columm); // ��ġ����� ������� �����ϱ� ���� 2���� �迭�� �� �Ҵ�.

    for (int i = 0; i < A_columm; i++)
        result[i] = (int *)malloc(sizeof(int) * A_row); // �� ��鿡 ���� �� ������ �߰��� ���� �Ҵ��Ͽ� 2���� �迭 ����.

    for (int i = 0; i < A_row; i++)
    {
        for (int j = 0; j < A_columm; j++)
            result[j][i] = matrix[i][j];
        // ��ġ����� A^T�� A�� ��� ���� ���� �ٲ� ����̹Ƿ�
        // ���ǿ� ���� ��� ���� �ٲ� result 2���� �迭�� ��������.
    }
    return result; // �ش� ������� ��ȯ��.
}

int **multiply_matrix(int **A, int **B, int A_row, int A_columm, int B_row, int B_columm)
// ��� A�� B�� ���Ͽ��� �ϹǷ� �� ����� size, �� ��� ���� ��� �μ��� �޾ƾ� ��.
// ��Ģ�� A�� ���� B�� ���� �������� ������ ������ �Ұ��ϳ�, �� �Լ��� ������ ��� ������
// A�� B�� �� ������ �����ϴٴ� ���� ������ �Ͽ� �ڵ带 ������.
{
    int **result = (int **)malloc(sizeof(int *) * A_row); // A*B�� ������� �����ϱ� ���� 2���� �迭�� �� �Ҵ�.

    for (int i = 0; i < A_row; i++) // �� ��鿡 ���� �� ������ �߰��� ���� �Ҵ��Ͽ� 2���� �迭 ����.
        result[i] = (int *)malloc(sizeof(int) * B_columm);

    // A�� ���� B�� ���� ���ƾ� ������ �����ϸ�
    // ����� A�� ��� B�� ����ŭ�� ����� ������.
    // Ex) A(2x3) * B(3x2) = C(2x2) Matrix ����.

    for (int i = 0; i < A_row; i++) // A*B���� A�� ��� B�� ���� ���ϹǷ� A�� ���� �������� �ݺ�.
    {
        for (int j = 0; j < B_columm; j++) // �׷��Ƿ� B�� ���� �������� �ݺ�.
        {
            result[i][j] = 0; // res ��� �ʱ�ȭ
            for (int k = 0; k < B_row /*A_columm*/; k++)
                result[i][j] += A[i][k] * B[k][j];
            // ��� ���� Fix. ���⼭ A�� ���� B�� �ุ�� �����ǹǷ�
            // ���� k�� ���� �ݺ������� ������ ����.
            // result �Լ��� 1�� 1���� A�� 1��� B�� 1���� �� ������ ���Ͽ� ���� ���̴�.
            // ���� ����, A[0][0]=A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0] �� �����̸�
            // ���⼭ �ڵ�� �����ϱ� ���ؼ��� ������ ��� ���� �ٲ�� ���� �� ������ ��� ���� ���ϱ� ������
            // A�� ���� B�� ���� ������ ������ �������� A�� ��� B�� ���� i, j�� ���� �����Ǹ� �̵鿡 ���� ������ �ٲ�.
            // �������ڸ� �߰������� k��� ������ ���� A�� ���� B�� ���� ���������μ� result���� ���� ������.
        }
    }
    return result; // �ش� ������� ��ȯ��.
}

int main(void)
{
    printf("2021041069 ������\n");
    int A_row, A_columm, B_row, B_columm;
    printf("��� A�� ��� ���� ���� �Է��ϼ���: ");
    scanf("%d %d", &A_row, &A_columm);

    printf("\n��� B�� ��� ���� ���� �Է��ϼ���: ");
    scanf("%d %d", &B_row, &B_columm);

    int **A = (int **)malloc(sizeof(int *) * A_row);

    for (int i = 0; i < A_row; i++)
        A[i] = (int *)malloc(sizeof(int) * A_columm);

    int **B = (int **)malloc(sizeof(int *) * B_row);

    for (int i = 0; i < B_row; i++)
        B[i] = (int *)malloc(sizeof(int) * B_columm);

    // A ��İ� B ����� ���� ����ڰ� �Է��� ���� ���� ���� �Ҵ�����.

    printf("\n��� A�� ��\n");
    for (int i = 0; i < A_row; i++)
    {
        for (int j = 0; j < A_columm; j++)
        {
            A[i][j] = rand() % 10 + 1; // rand �Լ��� ���Ͽ� 1~10������ �������� A ��Ŀ� ����.
            // seed�� ���� �������� time.h�� �߰��Ͽ� srand�� ��� ���������� ���ǻ� rand�Լ��� ����Ͽ� ������ ���� ���.
        }
    }

    print_matrix(A, A_row, A_columm);

    printf("��� B�� ��\n");
    for (int i = 0; i < B_row; i++)
    {
        for (int j = 0; j < B_columm; j++)
        {
            B[i][j] = rand() % 10 + 1; // �����ϰ� rand �Լ��� ���Ͽ� 1~10������ �������� B ��Ŀ� ����.
        }
    }

    print_matrix(B, B_row, B_columm);

    int **result_add = addition_matrix(A, B, A_row, A_columm);
    printf("A+B ����� ��\n");
    print_matrix(result_add, A_row, A_columm);

    int **result_sub = subtract_matrix(A, B, A_row, A_columm);
    printf("A-B ����� ��\n");
    print_matrix(result_sub, A_row, A_columm);

    int **result_transpose = transpose_matrix(A, A_row, A_columm);
    printf("A�� ��ġ����� ��\n");
    print_matrix(result_transpose, A_columm, A_row);

    int **result_multiply = multiply_matrix(A, B, A_row, A_columm, B_row, B_columm);
    printf("A*B ����� ��\n");
    print_matrix(result_multiply, A_row, B_columm);

    free_matrix(A, A_row);
    free_matrix(B, B_row);

    return 0;
}