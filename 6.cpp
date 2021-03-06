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

int Step3_Mark(int **assign, float **Mat, bool *col, bool *row, int N, int M, int zero_cnt)
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
                if (assign[j][i] == 1 && row[j] == false)
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
    {
        check[i] = new int[N];
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
                for (int k = 0; k < N; k++)
                {
                    if (Mat[k][j_idx] == 0)
                        check[k][j_idx] = -1;
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
                for (int k = 0; k < N; k++)
                {
                    if (Mat[i_idx][k] == 0)
                        check[i_idx][k] = -1;
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

void Step3_assign_mat(int N, float **Mat, int **assign, bool *row)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Mat[i][j] == 0)
            {
                if (assign[i][j] == 0)
                {
                    assign[i][j] = 1;
                    for (int k = 0; k < N; k++)
                    {
                        if (Mat[k][j] == 0 && k != i)
                            assign[k][j] = -1;
                    }
                    for (int k = j + 1; k < N; k++)
                    {
                        if (Mat[i][k] == 0)
                            assign[i][k] = -1;
                    }
                    break;
                }
                else
                    assign[i][j] = -1;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        bool flag = false;
        for (int j = 0; j < N; j++)
        {
            if (assign[i][j] == 1)
            {
                flag = true;
                row[i] = false;
                break;
            }
        }
        if (!flag)
            row[i] = true;
    }
}

void Step4_Mat_Change(int &N, bool *row, bool *col, float **Mat)
{
    float MIN_VALUE = FLT_MAX;

    for (int i = 0; i < N; i++)
    {
        if (row[i])
        {
            for (int j = 0; j < N; j++)
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
        for (int j = 0; j < N; j++)
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
}

int Mat_change(float **Mat, int N, int M, float *assignment_index, int MODE)
{
    float MIN = FLT_MAX;
    int **assign = new int *[N];
    bool *row = new bool[N];
    bool *col = new bool[M];
    int zero_cnt = 0;

    //init assign, row, col
    for (int i = 0; i < N; i++)
    {
        assign[i] = new int[M];
        row[i] = false;
        for (int j = 0; j < M; j++)
        {
            assign[i][j] = 0;
            col[j] = false;
        }
    }
    //vaildation check
    if (is_vaild(N, Mat, assignment_index, MODE) == 1)
    {
        for (int i = 0; i < N; i++)
            delete[] check[i];
        delete[] check;
        delete[] row;
        delete[] col;
        return (1);
    }
    Step3_assign_mat(N, Mat, assign, row);
    while (Step3_Mark(assign, Mat, col, row, N, M, zero_cnt)){}
    Step4_Mat_Change(N, row, col, Mat);

    for (int i = 0; i < N; i++)
            delete[] assign[i];
    delete[] assign;
    delete[] row;
    delete[] col;
    return (0);
}

float Solve(float **Cost, const int N, const int M, const int MODE, float *assignment_index)
{
    float ret;
    float **Mat = new float *[N];

    for (int i = 0; i < M; i++)
        Mat[i] = new float[M];

    if (MODE == 0)
        make_minimum_mat(Cost, Mat, N, M);
    else if (MODE == 1)
        make_maximum_mat(Cost, Mat, N, M);
    while (Mat_change(Mat, N, M, assignment_index, MODE) == 0){}

    for (int i = 0; i < N; i++)
        delete[] Mat[i];
    delete[] Mat;
    return (ret);
}

void Set_Cost_Mode(float **Cost, int &N, int &M, int &MODE)
{
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
}

void Print_Answer(int &N, float *assignment_index, int total, float **Cost)
{
    cout << "assignment index : ";
    for (int i = 0; i < N; i++)
    {
        total += Cost[i][(int)assignment_index[i]];
        cout << assignment_index[i] << " ";
    }
    cout << "\n";
    cout << "Total cost : " << total;
}

int main(void)
{
    int N, M, MODE, ori_N;
    float **Cost;
    float *assignment_index;
    float total = 0;

    cout << " Input row, column : ";
    cin >> N >> M;
    ori_N = N;
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
    Set_Cost_Mode(Cost, N, M, MODE);
    Solve(Cost, N, M, MODE, assignment_index);
    Print_Answer(ori_N, assignment_index, total, Cost);
    for (int i = 0; i < N; i++)
        delete[] Cost[i];
    delete[] Cost;
    delete[] assignment_index;
}