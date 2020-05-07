#include <iostream>
#include <float.h>
using namespace std;

void make_minimum_mat(float **Cost, float **Mat, const int N, const int M)
{
    float MIN;

    for (int i = 0; i < N; i++)
    {
        MIN = FLT_MAX;
        for (int j = 0; j < M; j++)
        {
            if (Cost[i][j] < MIN)
                MIN = Cost[i][j];
        }
        for (int j = 0; j < M; j++)
            Mat[i][j] = Cost[i][j] - MIN;
    }

    for (int i = 0; i < M; i++)
    {
        MIN = FLT_MAX;
        for (int j = 0; j < N; j++)
        {
            if (Mat[j][i] < MIN)
                MIN = Mat[j][i];
        }
        for (int j = 0; j < N; j++)
            Mat[j][i] = Mat[j][i] - MIN;
    }
}

void make_maximum_mat(float **Cost, float **Mat, const int N, const int M)
{
    float MAX;
    float MIN;

    for (int i = 0; i < N; i++)
    {
        MAX = FLT_MIN;
        for (int j = 0; j < M; j++)
        {
            if (Cost[i][j] > MAX)
                MAX = Cost[i][j];
        }
        for (int j = 0; j < M; j++)
            Mat[i][j] = MAX - Cost[i][j];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << Mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < M; i++)
    {
        MIN = FLT_MAX;
        for (int j = 0; j < N; j++)
        {
            if (Mat[j][i] < MIN)
                MIN = Mat[j][i];
        }
        for (int j = 0; j < N; j++)
            Mat[j][i] = Mat[j][i] - MIN;
    }
}

int Step3_Mark(int **check, float **Mat, bool *col, bool *row, int N, int M, int zero_cnt)
{
    int ret = 0;

    //Mark all columns having zeros in newly marked row(s)
    for (int i = 0; i < N; i++)
    {
        if (row[i])
        {
            for (int j = 0; j < M; j++)
            {
                if (Mat[i][j] == 0 && col[j] == false)
                {
                    col[j] = true;
                    ret = 1;
                }
            }
        }
    }

    //Mark all rows having assignments in newly marked columns
    for (int i = 0; i < M; i++)
    {
        if (col[i])
        {
            bool flag = 0;
            for (int j = 0; j < N; j++)
            {
                if (check[j][i] == 1 && row[j] == false)
                {
                    row[j] = true;
                    ret = 1;
                }
            }
        }
    }
    return (ret);
}

int is_vaild(int N, float **Mat, float *assignment_index, int MODE)
{
    int flag = 1;
    int cnt;
    int j;
    int ans = 0;
    int **check = new int *[N];

    for (int i = 0; i < N; i++)
        check[i] = new int[N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            check[i][j] = 0;
    }

    while (flag)
    {
        flag = 0;
        int j_idx;
        for (int i = 0; i < N; i++)
        {
            cnt = 0;
            for (j = 0; j < N; j++)
            {
                if (Mat[i][j] == 0 && check[i][j] == 0)
                {
                    cnt++;
                    j_idx = j;
                    if (cnt > 1)
                        break;
                }
            }
            if (cnt > 1)
                continue;
            if (cnt == 1)
            {
                flag = 1;
                ans++;
                check[i][j_idx] = 1;
                for (int i = 0; i < N; i++)
                {
                    if (Mat[i][j_idx] == 0)
                        check[i][j_idx] = -1;
                }
                for (int k = 0; k < N; k++)
                {
                    if (Mat[i][k] == 0)
                        check[i][k] = -1;
                }
                check[i][j_idx] = 1;
            }
        }
    }

    flag = 1;
    while (flag)
    {
        flag = 0;
        int i_idx;
        for (int i = 0; i < N; i++)
        {
            cnt = 0;
            for (j = 0; j < N; j++)
            {
                if (Mat[j][i] == 0 && check[j][i] == 0)
                {
                    cnt++;
                    i_idx = j;
                    if (cnt > 1)
                        break;
                }
            }
            if (cnt > 1)
                continue;
            if (cnt == 1)
            {
                flag = 1;
                ans++;
                check[i_idx][i] = 1;
                for (int i = 0; i < N; i++)
                {
                    if (Mat[i_idx][i] == 0)
                        check[i_idx][i] = -1;
                }
                for (int k = 0; k < N; k++)
                {
                    if (Mat[k][i] == 0)
                        check[k][i] = -1;
                }
                check[i_idx][i] = 1;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Mat[i][j] == 0 && check[i][j] == 0)
            {
                ans++;
                for (int k = 0; k < N; k++)
                {
                    if (Mat[i][k] == 0 && check[i][k] == 0)
                        check[i][k] = -1;
                    if (Mat[k][j] == 0 && check[k][j] == 0)
                        check[k][j] = -1;
                }
                check[i][j] = 1;
            }
        }
    }

    int value = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (check[i][j] == 1)
                assignment_index[value++] = j;
        }
    }
    for (int i = 0; i < N; i++)
        delete[] check[i];
    delete[] check;

    if (ans == N)
        return (1);
    return (-1);
}

void check_set(int N, float **Mat, int **check)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Mat[i][j] == 0)
            {
                if (check[i][j] == 0)
                {
                    check[i][j] = 1;
                    for (int k = 0; k < N; k++)
                    {
                        if (Mat[k][j] == 0 && k != i)
                            check[k][j] = -1;
                    }
                    for (int k = j + 1; k < N; k++)
                    {
                        if (Mat[i][k] == 0)
                            check[i][k] = -1;
                    }
                    break;
                }
                else
                    check[i][j] = -1;
            }
        }
    }
}

int Mat_change(float **Mat, int N, int M, float *assignment_index, int MODE)
{
    //check 배열 2차원..?
    float MIN = FLT_MAX;
    int **check = new int *[N];
    bool *row = new bool[N];
    bool *col = new bool[M];
    int zero_cnt = 0;

    //init check, row, col
    for (int i = 0; i < N; i++)
        check[i] = new int[M];
    for (int i = 0; i < N; i++)
    {
        row[i] = false;
        for (int j = 0; j < M; j++)
        {
            check[i][j] = 0;
            col[j] = false;
        }
    }

    int ret = 0;
    //check init (step 3 assign)
    cout << "START\n";

    if (is_vaild(N, Mat, assignment_index, MODE) == 1)
        return (1);
    check_set(N, Mat, check);

    for (int i = 0; i < N; i++)
    {
        bool flag = false;
        for (int j = 0; j < M; j++)
        {
            if (check[i][j] == 1)
            {
                flag = true;
                row[i] = false;
                break;
            }
        }
        if (!flag)
            row[i] = true;
    }

    while (Step3_Mark(check, Mat, col, row, N, M, zero_cnt))
    {
    }

    float MIN_VALUE = FLT_MAX;
    for (int i = 0; i < N; i++)
    {
        if (row[i])
        {
            for (int j = 0; j < M; j++)
            {
                if (!col[j])
                {
                    if (MIN_VALUE > Mat[i][j])
                        MIN_VALUE = Mat[i][j];
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (!row[i])
            {
                if (col[j])
                    Mat[i][j] += MIN_VALUE;
                else
                    continue;
            }
            else if (col[j])
                continue;
            else if (Mat[i][j] == 0)
                continue;
            else
                Mat[i][j] -= MIN_VALUE;
        }
    }

    return (0);
}

float Solve(float **Cost, const int N, const int M, const int MODE, float *assignment_index)
{
    float ret;
    float total = 0;
    float **Mat = new float *[N];

    for (int i = 0; i < M; i++)
        Mat[i] = new float[M];

    if (MODE == 0)
        make_minimum_mat(Cost, Mat, N, M);
    else if (MODE == 1)
        make_maximum_mat(Cost, Mat, N, M);
    int ret2 = 0;
    while (Mat_change(Mat, N, M, assignment_index, MODE) == 0)
    {
    }

    for (int i = 0; i < N; i++)
        delete[] Mat[i];
    delete[] Mat;
    return (ret);
}

int main(void)
{
    int N, M, MODE;
    float input;
    float **Cost;
    float *assignment_index;
    float total = 0;
    int len = 0;

    cout << " Input row, column : ";
    cin >> N >> M;
    len = N;
    if (N > M)
    {
        Cost = new float *[N];
        for (int i = 0; i < N; i++)
            Cost[i] = new float[N];
    }
    else
    {
        Cost = new float *[M];
        for (int i = 0; i < M; i++)
            Cost[i] = new float[M];
    }
    assignment_index = new float[N];

    cout << " Input Matrix : \n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> Cost[i][j];
    if (N < M)
    {
        for (int i = N; i < M; i++)
        {
            for (int j = 0; j < M; j++)
                Cost[i][j] = 10;
        }
        N = M;
    }
    else
    {
        for (int i = M; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                Cost[j][i] = 10;
            }
        }
        M = N;
    }

    cout << " Input Mode (0. Minimize, 1. Maximize): ";
    cin >> MODE;
    Solve(Cost, N, M, MODE, assignment_index);

    cout << "assignment index : ";
    for (int i = 0; i < len; i++)
    {
        total += Cost[i][(int)assignment_index[i]];
        cout << assignment_index[i] << " ";
    }

    cout << "\n";
    cout << "Total cost : " << total;
    for (int i = 0; i < N; i++)
        delete[] Cost[i];
    delete[] Cost;
    delete[] assignment_index;
}
