/*
poj1483
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

struct node {
	int l, r,i;
};

int c[100000 + 5];
node a[100000 + 5];
int ans[100000 + 5];
int n;

int cmp(node x, node y) {
	if (x.r == y.r)
		return x.l < y.l;
	return x.r > y.r;
}

int lowbit(int x) {
	return x&(-x);
}

int sum(int x) {
	int sum = 0;
	while (x>0) {
		sum += c[x];
		x -= lowbit(x);
	}
	return sum;
}

void add(int x,int d) {
	while (x <= n) {
		c[x] += d;
		x += lowbit(x);
	}
	return;
}

int main() {
	while (true) {
		scanf_s("%d",&n);
		if (n == 0)
			break;
		memset(ans, 0, sizeof(ans));
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; ++i) {
			scanf_s("%d %d", &a[i].l, &a[i].r);
			a[i].i = i;
		}
		sort(a + 1, a + 1 + n, cmp);
		ans[a[1].i] = 0;
		add(a[1].l + 1, 1);
		for (int i = 2; i <= n; ++i) {
			if (a[i].l == a[i - 1].l && a[i].r == a[i - 1].r) {
				ans[a[i].i] = ans[a[i - 1].i];
			}
			else {
				ans[a[i].i] = sum(a[i].l + 1);
			}
			add(a[i].l + 1, 1);
		}
		for (int i = 1; i <= n; i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
	return 0;
}
