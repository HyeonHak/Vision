#include <iostream>
#include <limits.h>
#include <time.h>
#include <stdio.h>
#include <vector>
using namespace std;

void Input(vector<int> &vec)
{
	int cnt;
	int data;

	cout << "Number count : ";
	cin >> cnt;
	for (int i = 0; i < cnt; i++)
	{
		cin >> data;
		vec.push_back(data);
	}
}

int Solved(vector<int> &vec)
{
	int i, j, tmp_val;
	int ret = INT_MIN;
	int start = 0;
	int end = 0;
	int SIZE = vec.size();

	for (i = 0; i < SIZE; i++)
	{
		tmp_val = 0;
		for (j = i; j < SIZE; j++)
		{
			tmp_val += vec[j];
			if (ret < tmp_val)
			{
				ret = tmp_val;
				start = i;
				end = j;
			}
		}
	}
	cout<<start<<" "<<end<<"\n";
	return (ret);
}

int main(void)
{
	clock_t start, end;
	vector<int> vec;
	Input(vec);
	start = clock();
	cout << Solved(vec) << "\n";
	end = clock();
	printf("%f", (double)(end - start) / (CLOCKS_PER_SEC));
}
