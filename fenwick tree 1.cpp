/*
poj1354
*/
#include <cstdio>
#include <cstring>

int tree[40000];
int level[40000];
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
	while (i <= 40000) {
		tree[i] += value;
		i += lowbit(i);
	}
}

int main()
{
	int N;
	scanf_s("%d", &N);
	int count = N;
	memset(tree, 0, sizeof(tree));
	memset(level, 0, sizeof(level));
	while (count--) {
		int x, y;
		scanf_s("%d%d", &x, &y);
		int pos = sum(x + 1);//tree下标从1开始
		level[pos]++;
		increase(x + 1, 1);
	}
	for (int i = 0; i < N; i++) {
		printf("%d\n", level[i]);
	}
    return 0;
}

