/*
poj3523
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
#pragma warning(disable:4996)
using namespace std;

int stepCount = 0;

int tree[100000+5];
int head[100000 + 5];
int tail[100000 + 5];
vector<vector<int>> fork(100000+5);
int hasApple[100000 + 5];
int N;

int lowbit(int x) {
	return x&(-x);
}

int sum(int pos) {
	int sum = 0;
	int i = pos;
	while (i) {
		sum += tree[i];
		i -= lowbit(i);
	}
	return sum;
}

void increase(int pos, int value) {
	int i = pos;
	while (i <= N) {
		tree[i] += value;
		i += lowbit(i);
	}
}

void travel(int index,int &step) {
	head[index] = step;
	for (int i = 0; i < fork[index].size(); ++i) {
		step++;
		travel(fork[index][i], step);
	}
	tail[index] = step;
}

int main()
{
	scanf("%d", &N);
	memset(head,0,sizeof(head));
	memset(tail, 0, sizeof(tail));
	for (int k = 0; k < N - 1; ++k) {
		int parent, son;
		scanf("%d%d", &parent, &son);
		fork[parent].push_back(son);
	}
	int step = 1;
	travel(1, step);
	for (int i = 1; i <=  N; i++) {
		hasApple[i] = 1;
		increase(i, 1);
	}

	int M;
	char ctl[10];
	int index;
	scanf("%d", &M);
	while (M--) {
		scanf("%s%d", ctl, &index);
		if (ctl[0] == 'C') {
			if (hasApple[index]) {
				increase(head[index], -1);
				hasApple[index] = 0;
			}
			else {
				increase(head[index], 1);
				hasApple[index] = 1;
			}
		}
		else {
			cout << sum(tail[index]) - sum(head[index] - 1)<<endl;
		}
	}
    return 0;
}