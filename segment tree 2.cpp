/*
poj1106
*/
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
const int N = 100000 + 5;
struct kthNum {
public:
	int a[100005];
	int sorted[100005];
	int tree[20][100005];
	int sum[20][100005];
	
	void init(int n) {
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			tree[0][i] = sorted[i] = a[i];
		}
		sort(sorted + 1, sorted + 1 + n);
	}


	void Build(int c, int l, int r) {
		int mid = (l + r) >> 1;
		int lm = mid - l + 1;
		int lp = l, rp = mid + 1;
		for (int i = l; i <= mid; i++) {
			if (sorted[i] < sorted[mid]) {
				lm--;
			}
		}
		for (int i = l; i <= r; i++) {
			if (i == l) {
				sum[c][i] = 0;
			}
			else {
				sum[c][i] = sum[c][i - 1];
			}
			if (tree[c][i] == sorted[mid]) {
				if (lm) {
					lm--;
					sum[c][i]++;
					tree[c + 1][lp++] = tree[c][i];
				}
				else {
					tree[c + 1][rp++] = tree[c][i];
				}
			}
			else if (tree[c][i] < sorted[mid]) {
				sum[c][i]++;
				tree[c + 1][lp++] = tree[c][i];
			}
			else {
				tree[c + 1][rp++] = tree[c][i];
			}
		}
		if (l == r) return;
		Build(c + 1, l, mid);
		Build(c + 1, mid + 1, r);
		
	}

	int Query(int c, int l, int r, int ql, int qr, int k) {
		int mid = (l + r) >> 1;
		if (l == r) {
			return tree[c][l];
		}
		int s, ss;
		if (l == ql) {
			s = 0;
			ss = sum[c][qr];
		}
		else {
			s = sum[c][ql - 1];
			ss = sum[c][qr] - s;
		}
		if (k <= ss) {
			return Query(c + 1, l, mid, l + s, l + s + ss - 1, k);
		}
		else {
			return Query(c + 1, mid + 1, r, mid + 1 - l + ql - s, mid + 1 - l + qr - s - ss, k - ss);
		}
	}
}solve;

int main()
{
	int n, m;
	cin >> n >> m;
	solve.init(n);
	solve.Build(0, 1, n);
	while (m--) {
		int l, r, k;
		cin >> l >> r >> k;
		//cout << l << r << k << endl;
		cout << solve.Query(0, 1, n, l, r, k) << endl;
	}
	
	return 0;
}