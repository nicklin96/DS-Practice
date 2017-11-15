/*
poj743
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int maxN = 10005, maxM = 20005;
int n, m, total, answer, e[maxN], w[maxM], son[maxM], nxt[maxM];
struct node {
	node* son[2];
	int val, tsize, weight, ran;
	void update() {
		tsize = son[0]->tsize + son[1]->tsize + weight;
	}
}tree[maxN*6],*roots[maxN],*firstNode = tree;

void addEdge(int x, int y, int z) {
	
	w[++total] = z;
	son[total] = y;
	nxt[total] = e[x];
	e[x] = total;

}

void rotate(node* &root, int direction) {
	node* tmp = root->son[direction];
	root->son[direction] = tmp->son[direction ^ 1];
	tmp->son[direction ^ 1] = root;
	tmp->tsize = root->tsize;
	root->update();
	root = tmp;
}

void Insert(node* &root, int val, int num) {
	if (root == firstNode) {
		++total;
		root = &tree[total];
		root->tsize = root->weight = num;
		root->val = val;
		root->ran = rand();
		root->son[1] = root->son[0] = firstNode;
		return;
	}
	int d;
	if(root->val > val)
		d = 0;
	else if(root->val < val)
		d = 1;
	else
		d = -1;
	root->tsize += num;
	if (d == -1)
		root->weight += num;
	else {
		Insert(root->son[d], val, num);
		if (root->son[d]->ran < root->ran) {
			rotate(root, d);
		}
	}
}

int Query(node* root, int val) {
	if (root == firstNode) return 0;
	int d;
	if(root->val > val)
		d = 0;
	else if(root->val < val)
		d = 1;
	else
		d = -1;
	if (d < 0)
		return root->son[0]->tsize + root->weight;
	else if (d)
		return root->son[0]->tsize + root->weight + Query(root->son[1], val);
	return Query(root->son[0], val);
}

void Join(node* &t1, node*t2) {
	if (t2 == firstNode)
		return;
	Insert(t1, t2->val, t2->weight);
	Join(t1, t2->son[0]);
	Join(t1, t2->son[1]);
}

int cal(node* t1, node*t2, int val) {
	if (t2 == firstNode)
		return 0;
	return t2->weight*Query(t1, val - t2->val) + cal(t1, t2->son[0],val) + cal(t1, t2->son[1],val);
}

void work(int x, int dep, int fa) {
	for (int j = e[x]; j; j = nxt[j]) {
		if (son[j] != fa) {
			work(son[j], dep + w[j], x);
			if (roots[x]->tsize < roots[son[j]]->tsize)
				swap(roots[x], roots[son[j]]);
			answer += cal(roots[x], roots[son[j]], 2 * dep + m);
			Join(roots[x], roots[son[j]]);
		}
	}
	answer += Query(roots[x], dep + m);
	Insert(roots[x], dep, 1);
}

int main() {
	while (true) {
		scanf("%d%d", &n, &m);
		if (n == 0)
			break;
		memset(e, 0, sizeof(e));
		memset(son, 0, sizeof(son));
		total = 0;
		for (int i = 1; i <= n; i++)
			roots[i] = firstNode;
		int x, y, z;
		for (int i = 1; i < n; i++) {
			scanf("%d%d%d", &x, &y, &z);
			addEdge(x, y, z);
			addEdge(y, x, z);
		}
		total = answer = 0;
		work(1, 0, 0);
		printf("%d\n", answer);
	}
	return 0;
}