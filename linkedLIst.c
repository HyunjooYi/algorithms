#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	struct _node *next;
	struct _node *prev;
	int data;
} node;

node *head = NULL;
node *tail = NULL;

int removeFirst() {
	node *tmp;

	if(head == NULL)
		return -1;
	else {
		if(tail == head) { // last node
			free(head);
			tail = NULL;
			head = NULL;
		} else {
			head->next->prev = NULL;
			tmp = head->next;
			free(head);
			head = tmp;
		}
	}

	return 0;
}

int removeLast() {
	node *tmp;

	if(tail == NULL)
		return -1;
	else {
		if(tail == head) { // last node
			free(tail);
			tail = NULL;
			head = NULL;
		} else {
			tail->prev->next = NULL;
			tmp = tail->prev;
			free(tail);
			tail = tmp;
		}
	}

	return 0;
}

int insertFirst(node *node) {
	if(head == NULL) {
		head = node;
		tail = node;
		node->next = NULL;
		node->prev = NULL;
	} else {
		head->prev = node;
		node->next = head;
		node->prev = NULL;
		head = node;
	}

	return 0;
}

int insertLast(node *node) {
	if(tail == NULL) {
		tail = node;
		head = node;
		node->next = NULL;
		node->prev = NULL;
	} else {
		tail->next = node;
		node->prev = tail;
		node->next = NULL;
		tail = node;
	}

	return 0;
}

node* search(int targetData) {
	node* next;

	next = head;
	while(next != NULL) {
		if(next->data == targetData)
			return next;
		else
			next = next->next;
	}

	return NULL;
}

void printAll() {
	node* next;

	next = head;
	while(next != NULL) {
		printf("%d ", next->data);
		next = next->next;
	}

	printf("\n");
}

int main(void) {
	node *node1;
	node *node2;
	node *node3;
	node *node4;
	node *tmp;

	node1 = (node *) malloc(sizeof(node));
	node1->data = 1;
	node2 = (node *) malloc(sizeof(node));
	node2->data = 2;
	node3 = (node *) malloc(sizeof(node));
	node3->data = 3;
	node4 = (node *) malloc(sizeof(node));
	node4->data = 4;

	printf("Insert 1 at the first\n");
	insertFirst(node1);
	printAll();
	printf("\nInsert 3 at the last\n");
	insertLast(node3);
	printAll();
	printf("\nInsert 4 at the first\n");
	insertFirst(node4);
	printAll();
	printf("\nInsert 2 at the last\n");
	insertLast(node2);
	printAll();
	printf("\nRemove the last\n");
	removeLast();
	printAll();
	printf("\nRemove the First\n");
	removeFirst();
	printAll();
	tmp = search(2);
	printf("\nsearch(2) = %s\n", tmp==NULL?"There is NO 2":"There is 2 in the list");
	printAll();
	tmp = search(3);
	printf("\nsearch(3) = %s\n", tmp==NULL?"There is NO 3":"There is 3 in the list");
	printAll();

	return 0;
}