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

int divide_conquer(int left, int right, vector<int> &vec, int *LEFT, int *RIGHT)
{
	if (left == right)
		return (vec[left]);
	int mid = (left + right) / 2;
	int left_max, right_max, tmp_val;
	int tmp_left, tmp_right;


	left_max = right_max = tmp_val = 0;

	for (int i = mid; i >= left; i--)
	{
		tmp_val += vec[i];
		if (tmp_val >= left_max)
		{
			left_max = tmp_val;
			tmp_left = i;
		}
	}
	tmp_val = 0;
	for (int i = mid + 1; i <= right; i++)
	{
		tmp_val += vec[i];
		if (tmp_val >= right_max)
		{
			right_max = tmp_val;
			tmp_right = i;
		}
	}
	
	int left_value = divide_conquer(left, mid, vec, LEFT, RIGHT);
	int right_value = divide_conquer(mid + 1, right, vec, LEFT, RIGHT);
	int current_value = left_max + right_max;
	int max_value = max({left_value, right_value, current_value});
	if (max_value == left_value)
	{
		*LEFT = left;
		*RIGHT = mid;
		return (left_value);
	}
	else if (max_value == right_value)
	{
		*LEFT = mid + 1;
		*RIGHT = right;
		return (right_value);
	}
	else
	{
		*LEFT = tmp_left;
		*RIGHT = tmp_right;
		return (current_value);
	}
}

int Solved(vector<int> &vec, int *LEFT, int *RIGHT)
{
	int left, right, ret;
	int SIZE = vec.size();

	left = 0;
	right = SIZE - 1;
	ret = divide_conquer(left, right, vec, LEFT, RIGHT);
	cout<<*LEFT<<" "<<*RIGHT<<"\n";
	return (ret);
}

int main(void)
{
	clock_t start, end;
	int LEFT, RIGHT;
	LEFT = RIGHT = 0;
	vector<int> vec;
	Input(vec);
	start = clock();
	cout << Solved(vec, &LEFT, &RIGHT) << "\n";
	end = clock();
	printf("%f", (double)(end - start) / (CLOCKS_PER_SEC));
}
