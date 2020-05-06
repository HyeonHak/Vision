#include <iostream>
#include <algorithm>
#include <limits.h>
#include <time.h>
#include <vector>
#include <stdio.h>

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

int divide_conquer(int left, int right, vector<int> &vec)
{
	if (left == right)
		return (vec[left]);
	int mid = (left + right) / 2;
	int left_max, right_max, tmp_val;
	left_max = right_max = tmp_val = 0;

	for (int i = mid; i >= left; i--)
	{
		tmp_val += vec[i];
		if (tmp_val >= left_max)
			left_max = tmp_val;
	}
	tmp_val = 0;
	for (int i = mid + 1; i <= right; i++)
	{
		tmp_val += vec[i];
		if (tmp_val >= right_max)
			right_max = tmp_val;
	}
	return (max({divide_conquer(left, mid, vec), divide_conquer(mid + 1, right, vec), left_max + right_max}));
}

int Solved(vector<int> &vec)
{
	int left, right, ret;
	int SIZE = vec.size();

	left = 0;
	right = SIZE - 1;
	ret = divide_conquer(left, right, vec);
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
