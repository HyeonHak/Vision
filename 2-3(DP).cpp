#include <iostream>
#include <algorithm>
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
	int ret = INT_MIN;
	int SIZE = vec.size();
	int left, right;
	int tmp_val;
	vector<int> DP(SIZE, 0);

  left = right = 0;
	DP[0] = vec[0];

	for (int i = 1; i < SIZE; i++)
	{
		tmp_val = max(DP[i - 1] + vec[i], vec[i]);
		if (tmp_val == vec[i])
			left = right = i;
		DP[i] = tmp_val;
		if (ret < DP[i])
		{
			ret = DP[i];
			right = i;
		}
	}
	cout<<left<<" "<<right<<"\n";
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
