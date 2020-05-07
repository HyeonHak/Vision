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
            if (Mat[j][i] < MIN)
                MIN = Mat[j][i];
        }
        //cout << "MIN: " << MIN << endl;
        for (int j = 0; j < N; j++)
            Mat[j][i] = Mat[j][i] - MIN;
    }
}

float calc_mat(float **Mat, const int N, const int M, const int MODE, float *assignment_index)
{
    float ret = 0;
    int *arr = new int[N];
    for (int i = 0; i < N; i++)
        arr[i] = 0;
    delete[] arr;
    return (ret);
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
    for (int i = 0; i < N; i++)
    {
        if (row[i])
        {
            for (int j = 0; j < M; j++)
            {
                if (!col[j] && Mat[i][j] == 0)
                    return (1);
            }
        }
    }
    return (0);
}

int Mat_change(float **Mat, int N, int M, float *assignment_index)
{
    //check 배열 2차원..?
    float MIN = FLT_MAX;
    int **check = new int *[N];
    bool *row = new bool[N];
    bool *col = new bool[M];
    int zero_cnt = 0;

    //init
    for (int i = 0; i < N; i++)
        check[i] = new int[M];
    for (int i = 0; i < N; i++)
    {
        row[i] = false;
        for (int j = 0; j < M; j++)
        {
            if (Mat[i][j] == 0)
                zero_cnt++;
            check[i][j] = 0;
            col[j] = false;
        }
    }

    int ret = 0;
    //check init (step 3 assign)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (Mat[i][j] == 0)
            {
                if (check[i][j] == 0)
                {
                    check[i][j] = 1;
                    assignment_index[ret] = j;
                    ret++;
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
    if (ret == N)
        return (1);
    /*for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << check[i][j] << " ";
        }
        cout << endl;
    }*/

    //Mark all rows having no assignments
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
    /*cout << "INIT\n";
    for (int i = 0; i < N; i++)
        cout << row[i] << " ";
    cout << endl;
    for (int j = 0; j < M; j++)
        cout << col[j] << " ";
    cout << endl;
    cout << endl;*/
    //step 3 (Mark)
    while (Step3_Mark(check, Mat, col, row, N, M, zero_cnt))
    {
        /*for (int i = 0; i < N; i++)
            cout << row[i] << " ";
        cout << endl;
        for (int j = 0; j < M; j++)
            cout << col[j] << " ";
        cout << endl;
        cout << endl;*/
    }

    /*cout << "ROW\n";
    for (int i = 0; i < N; i++)
        cout << row[i] << " ";
    cout << endl;
    for (int i = 0; i < M; i++)
        cout << col[i] << " ";
    cout << endl;

    cout << "START\n";*/
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
    //cout << MIN_VALUE << endl;
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

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            check[i][j] = 0;
            cout << Mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return (0);
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

    //while (!Mat_check(Mat, N, M))
    //{
    while (Mat_change(Mat, N, M, assignment_index) == 0)
    {
    }
    /*return (ret);
        cout << "fail";
        break;*/
    //}
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout << Mat[i][j] << " ";
        cout << endl;
    }
    float total = 0;
    for (int i = 0; i < N; i++)
    {
        total += Cost[i][(int)assignment_index[i]];
        cout << "COST" << Cost[i][(int)assignment_index[i]] << endl;
        cout << assignment_index[i] << " ";
    }

    cout << "\n"
         << total << "\n";
    return (ret);
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
