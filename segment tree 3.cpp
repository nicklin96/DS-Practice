/*
poj1184
*/
#include <iostream>
using namespace std;
#define MAXN 10000
int line[MAXN], ans[MAXN];
struct node {
	int l, r, len;
}tree[MAXN*4];

void build(int node, int l, int r) {
	int mid = (l + r) >> 1;
	tree[node].len = r - l + 1;
	tree[node].l = l;
	tree[node].r = r;
	if (l == r) return;
	build(node * 2, l, mid);
	build(node * 2 + 1, mid + 1, r);
}

int query(int node, int k) {
	tree[node].len--;
	if (tree[node].l == tree[node].r) {
		return tree[node].l;
	}
	else if (tree[2 * node].len >= k) {
		return query(2 * node, k);
	}
	else {
		return query(2 * node + 1, k - tree[node * 2].len);
	}
}
int main()
{
	int n;
	cin >> n;
	line[1] = 0;
	for (int i = 2; i <= n; i++) {
		cin >> line[i];
	}
	build(1, 1, n);
	for (int i = n; i >= 1; i--) {
		ans[i] = query(1, line[i] + 1);
	}
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << endl;
	}

	return 0;
}