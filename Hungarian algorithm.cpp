#include <iostream>
#include <float.h>
using namespace std;

int Mat_check(float **Mat, const int N, const int M)
{
    int *arr = new int[N];
    int *arr_col = new int[M];
    int flag;

    for (int i = 0; i < N; i++)
        arr[i] = 0;
    for (int i = 0; i < N; i++)
    {
        flag = 0;
        for (int j = 0; j < M; j++)
        {
            if (Mat[i][j] == 0 && arr[j] == 0)
            {
                flag = 1;
                arr[j] = 1;
                break;
            }
        }
        if (flag == 0)
        {
            delete[] arr;
            delete[] arr_col;
            return (false);
        }
    }

    for (int i = 0; i < M; i++)
        arr_col[i] = 0;
    for (int i = 0; i < M; i++)
    {
        flag = 0;
        for (int j = 0; j < N; j++)
        {
            if (Mat[i][j] == 0 && arr_col[j] == 0)
            {
                flag = 1;
                arr_col[i] = 1;
                break;
            }
        }
        if (flag == 0)
        {
            delete[] arr;
            delete[] arr_col;
            return (false);
        }
    }
    delete[] arr;
    delete[] arr_col;
    return (true);
}

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
            if (Mat[i][j] < MIN)
                MIN = Mat[i][j];
        }
        for (int j = 0; j < N; j++)
            Mat[i][j] = Mat[i][j] - MIN;
    }
}

void DFS(float **Mat, const int N, const int M, int i, int j)
{
}

float calc_mat(float **Mat, const int N, const int M, const int MODE, float *assignment_index)
{
    float ret = 0;
    int *arr = new int[N];
    for (int i = 0; i < N; i++)
        arr[i] = 0;
    for (int i = 0; i < N; i++)
    {
        if (arr[i] == 0)
        {
            for (int j = 0; j < M; j++)
            {
                if (Mat[i][j] == 0)
                {
                    DFS(Mat, N, M, i, j);
                }
            }
        }
    }
    delete[] arr;
    return (ret);
}

void Mat_change(float **Mat, int N, int M)
{
    //check 배열 2차원..?
    float MIN = FLT_MAX;
    int **check = new int *[N];
    bool *row = new bool[N];
    bool *col = new bool[M];

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

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
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
                    for (int k = j + 1; k < M; k++)
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

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << check[i][j] << " ";
        }
        cout << endl;
    }

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
    for (int i = 0; i < N; i++)
    {
        if (row[i])
        {
            for (int j = 0; j < M; j++)
            {
                if (Mat[i][j] == 0)
                    col[j] = true;
            }
        }
    }
    for (int i = 0; i < M; i++)
    {
        if (col[i])
        {
            bool flag = 0;
            for (int j = 0; j < N; j++)
            {
                if (check[i][j] == 1)
                    row[j] = true;
            }
        }
    }

    for (int i = 0; i < N; i++)
        cout << row[i] << " ";
    cout << endl;
    for (int i = 0; i < M; i++)
        cout << col[i] << " ";
    cout << endl;

    cout<<"START\n";
    //row = false && col = true
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
    cout<<MIN_VALUE<<endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (!row[i] && col[j])
                Mat[i][j] += MIN_VALUE;
            else if (Mat[i][j] == 0)
                continue;
            else
                Mat[i][j] -= MIN_VALUE;
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << Mat[i][j] << " ";
        }
        cout << endl;
    }
}

float Solve(float **Cost, const int N, const int M, const int MODE, float *assignment_index)
{
    float ret;
    int min_row, min_col;
    float **Mat = new float *[N];

    for (int i = 0; i < M; i++)
        Mat[i] = new float[M];

    make_minimum_mat(Cost, Mat, N, M);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << Mat[i][j] << " ";
        }
        cout << endl;
    }

    while (!Mat_check(Mat, N, M))
    {
        Mat_change(Mat, N, M);
        return (ret);
        cout << "fail";
        break;
    }
    ret = calc_mat(Mat, N, M, MODE, assignment_index);
    for (int i = 0; i < N; i++)
        delete[] Mat[i];
    delete[] Mat;
    return (ret);
}

int main(void)
{
    int N, M, MODE;
    float input;

    cout << " Input row, column : ";
    cin >> N >> M;

    float **Cost = new float *[N];
    float *assignment_index = new float[N];

    for (int i = 0; i < N; i++)
        Cost[i] = new float[M];

    cout << " Input Matrix : \n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> Cost[i][j];
    cout << " Input Mode (1. Minimize, 2. Maximize): ";
    cin >> MODE;
    Solve(Cost, N, M, MODE, assignment_index);

    for (int i = 0; i < N; i++)
        cout << assignment_index[i] << " ";
    for (int i = 0; i < N; i++)
        delete[] Cost[i];
    delete[] Cost;
    delete[] assignment_index;
}
