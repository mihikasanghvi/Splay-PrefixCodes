#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_TREE_HT 1000
struct node {
	char data;
	unsigned freq;
	struct node *left, *right;
};

// A Min Heap
struct MinHeap {
	unsigned size;
	unsigned capacity;
	struct node** array;
};
struct node* newNode(char data, unsigned freq);
struct MinHeap* create(unsigned capacity);
void swapMinHeapNode(struct node** a, struct node**b);
void MinHeapify(struct MinHeap* minHeap, int idx);
int checkSize(struct MinHeap* minHeap);
struct node* extractValue(struct MinHeap* minHeap);
void insertMinHeap(struct MinHeap* minHeap, struct node* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
void printArr(int arr[], int n);
void printArrChar(char arr[], int n);
int isLeaf(struct node* root);
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);
void printInorder(struct node* node);
struct node* buildTree(char data[], int freq[], int size);
int maxDepth(struct node* node);
struct node* semisplayright(struct node* y);
struct node* semisplayleft(struct node* x);
struct node* splay(struct node* root);
void splay2(struct node* root);
struct node* semisplaying(struct node* root);
void printCodes(struct node* root, int arr[], int top, int data);
void encode(struct node* root, char data[]);
void SplayCodes(char data[], char copydata[], int freq[], int size);
char checkchar(char c, char carr[],int size);
int freqinit(const char* str, char c);
int readline(char *line, int l);
char* removeDuplicate(char str[], int n);
void checkInArr(char str[],int freq[],int n );


