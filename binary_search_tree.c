#include <stdio.h>
#include <stdlib.h>

#define INORDER 1
#define PREORDER 2
#define POSTORDER 3

typedef struct _node {
	struct _node* right;
	struct _node* left;
	int data;
} node;

void traversal(node *node, int which) {
	if(node == NULL) 
		return;

	switch(which) {
	case INORDER:
		traversal(node->left, INORDER);
		printf("%d ", node->data);
		traversal(node->right, INORDER);
		break;
	case PREORDER :
		printf("%d ", node->data);
		traversal(node->left, PREORDER);
		traversal(node->right, PREORDER);
		break;
	case POSTORDER : 
		traversal(node->left, POSTORDER);
		traversal(node->right, POSTORDER);
		printf("%d ", node->data);
		break;
	}
}

void insert(node **_root, int insert_node_data) {
	node *root = *_root;
	node *new_node = NULL;
	node *parent = NULL;

	new_node = (node *) malloc (sizeof(node));
	new_node->right = NULL;
	new_node->left = NULL;
	new_node->data = insert_node_data;

	parent = root;
	while(1) {
		if(parent->data < insert_node_data) {
			if(parent->right != NULL)
				parent = parent->right;
			else
				break;
		} else {
			if(parent->left != NULL)
				parent = parent->left;
			else
				break;
		}
	}

	if(parent->data > insert_node_data)
		parent->left = new_node;
	else
		parent->right = new_node;
}

int delete(node **_root, int delete_node_data) {
	node *parent = NULL;
	node *curr = *_root;
	node *leaf = NULL;

	if(delete_node_data == curr->data) {
		printf("root cannot be deleted\n");
		return -1;
	}

	while(1) {
		if(curr->data < delete_node_data) {
			if(curr->right != NULL) {
				parent = curr;
				curr = curr->right;
			}
			else
				return -1;
		} else if (curr->data > delete_node_data) {
			if(curr->left != NULL){
				parent = curr;
				curr = curr->left;
			}
			else
				return -1;
		} else {
			break;
		}
	}

	if(curr->right == NULL && curr->left == NULL) {
		if(parent->right == curr)
			parent->right = NULL;
		else
			parent->left = NULL;
		free(curr);
	} else if (curr->right == NULL) {
		if(parent->right == curr)
			parent->right = curr->left;
		else
			parent->left = curr->left;
		free(curr);
	} else if(curr->left == NULL) {
		if(parent->right == curr)
			parent->right = curr->right;
		else
			parent->left = curr->right;
		free(curr);
	} else {
		leaf = curr->right;
		while(leaf->left != NULL) {
			parent = leaf;
			leaf = leaf->left;
		}
		curr->data = leaf->data;
		free(leaf);
		parent->left = NULL;
	}

	return 1;
}

void destroy(node *node) {
	if(node == NULL)
		return;
	destroy(node->left);
	destroy(node->right);
	free(node);
}

node *create(int root_data, int *arr) {
	node *root;
	node *tmp;
	int i, len;

	root = (node *) malloc (sizeof(node));

	if(root == NULL)
		return NULL;
	
	root->right = NULL;
	root->left = NULL;
	root->data = root_data;

	if(arr == NULL)
		return root;

	len = sizeof(arr);
	for(i=0; i < len; i++)
		insert(&root, arr[i]);

	return root;
}

int main(int argc, char const *argv[])
{
	node *root;
	int arr[8] = {1, 78, 90, 12, 34, 120, 22, 4};

	root = create(50, arr);
	printf("create root [%d]\n", root->data);
	/*
					50
				1		70
	-------------------------------------
					50
				1		70
							90
	-------------------------------------
					50
			1				70
				12				90
	-------------------------------------
					50
		1					70
			12					90
				34
	-------------------------------------
					50
		1					70
			12					90
				34					120
	-------------------------------------
					50
		1					70
			12					90
				34					120
			22
	-------------------------------------
					50
		1					70
				12				90
			4		34				120
				22
	-------------------------------------
	*/

	printf("\ntraversal INORDER\n");
	traversal(root, INORDER);
	printf("\n");
	printf("traversal POSTORDER\n");
	traversal(root, POSTORDER);
	printf("\n");
	printf("traversal PREORDER\n");
	traversal(root, PREORDER);
	printf("\n");

	printf("\ndelete 5, 12, 34\n");
	if(delete(&root, 5) < 0)
		printf("5 is not a node of this tree\n");
	if(delete(&root, 12) < 0)
		printf("12 is not a node of this tree\n");
	if(delete(&root, 34) < 0)
		printf("34 is not a node of this tree\n");

	printf("traversal INORDER\n");
	traversal(root, INORDER);
	printf("\n");

	printf("\ninsert 5, 21\n");
	insert(&root, 5);
	insert(&root, 21);

	printf("traversal INORDER\n");
	traversal(root, INORDER);
	printf("\n");

	printf("\ndestroy all\n");
	destroy(root);

	return 0;
}