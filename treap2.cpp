/*
poj444
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn = 300005;
int nodeNum, optNum;
int nums[maxn];
struct node {
	node* left;
	node* right;
	int priority;
	int nodeCount;//number of nodes in its subtrees
	int value;
	node() {
		left = right = NULL;
		priority = rand();
		nodeCount = 0;
	}
	
	void updateNodeCount() {
		nodeCount = 1;
		if (left != NULL)nodeCount += left->nodeCount;
		if (right != NULL)nodeCount += right->nodeCount;
	}
};

void rotate_left(node* &root) {
	node* tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	root->updateNodeCount();
	tmp->updateNodeCount();
	root = tmp;
	return;
}

void rotate_right(node* &root) {
	node* tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	root->updateNodeCount();
	tmp->updateNodeCount();
	root = tmp;
	return;
}

void insert(node* &root, int value) {
	if (root == NULL) {
		node* tmp = new node();
		tmp->value = value;
		root = tmp;
	}
	else {
		if (value < root->value) {
			insert(root->left, value);
			if (root->left->priority > root->priority) {
				rotate_right(root);
			}
		}
			
		else {
			insert(root->right, value);
			if (root->right->priority > root->priority) {
				rotate_left(root);
			}
		}
			
	}
	//after rotation, nodeCount needs to be updated
	root->updateNodeCount();
}

int getKth(node* root, int k) {
	if (root == NULL || k <= 0)return 0;//invalid cases
	int s;
	if (root->right == NULL)s = 0;
	else s = root->right->nodeCount;
	//if the number of nodes in right subtree is no larger than k, find kth in right subtree, if not, in left subtree.
	if (k == s + 1)return root->value;
	else if (k <= s)
		return getKth(root->right, k);
	else return getKth(root->left, k - s - 1);
}

int main() {
	scanf("%d %d", &nodeNum, &optNum);
	node* root = NULL;
	for (int i = 1; i <= nodeNum; i++) {
		scanf("%d", &nums[i]);
	}
	int count = 1, tmp;
	for (int i = 1; i <= optNum; i++) {
		scanf("%d", &tmp);
		while (count <= tmp) {
			insert(root, nums[count]);
			++count;
		}
		printf("%d\n", getKth(root, count - i));
	}
	return 0;
}