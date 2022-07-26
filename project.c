#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "project.h"
#define MAX_TREE_HT 1000

struct node* newNode(char data, unsigned freq)
{
	struct node* temp = (struct node*)malloc(
		sizeof(struct node));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap* create(unsigned capacity)

{

	struct MinHeap* minHeap
		= (struct MinHeap*)malloc(sizeof(struct MinHeap));

	// current size is 0
	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array = (struct node**)malloc(
		minHeap->capacity * sizeof(struct node*));
	return minHeap;
}

// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct node** a,
					struct node** b)

{

	struct node* t = *a;
	*a = *b;
	*b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)

{

	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size
		&& minHeap->array[left]->freq
			< minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size
		&& minHeap->array[right]->freq
			< minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest],
						&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

// A utility function to check
// if size of heap is 1 or not
int checkSize(struct MinHeap* minHeap)
{

	return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct node* extractValue(struct MinHeap* minHeap)

{

	struct node* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap,
            struct node* minHeapNode)

{

	++minHeap->size;
	int i = minHeap->size - 1;

	while (i
		&& minHeapNode->freq
				< minHeap->array[(i - 1) / 2]->freq) {

		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}

// A standard function to build min hap
void buildMinHeap(struct MinHeap* minHeap)

{

	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);

	//printf("\n");
}


void printArrChar(char arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%c", arr[i]);

	printf("\n");
}


// Utility function to check if this node is leaf
int isLeaf(struct node* root)

{

	return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[],
									int freq[], int size)

{

	struct MinHeap* minHeap = create(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}
void printInorder(struct node* node)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    printInorder(node->left);

    /* then print the data of node */
    printf("%c-%d|", node->data, node->freq);

    /* now recur on right child */
    printInorder(node->right);
}

// The main function that builds tree
struct node* buildTree(char data[],
									int freq[], int size)

{
	struct node *left, *right, *top;

	// Step 1: Create a min heap of capacity
	// equal to size. Initially, there are
	// modes equal to size.
	struct MinHeap* minHeap
		= createAndBuildMinHeap(data, freq, size);

	// Iterate while size of heap doesn't become 1
	while (!checkSize(minHeap)) {

		// Step 2: Extract the two minimum
		// freq items from min heap
		left = extractValue(minHeap);
		right = extractValue(minHeap);

		// Step 3: Create a new internal
		// node with frequency equal to the
		// sum of the two nodes frequencies.
		// Make the two extracted node as
		// left and right children of this new node.
		// Add this node to the min heap
		// '$' is a special value for internal nodes, not
		// used
		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}

	// Step 4: The remaining node is the
	// root node and the tree is complete.
	return extractValue(minHeap);
}

//Calculate height/Depth of left and right subtree
int maxDepth(struct node* node)
{
    if (node == NULL)
        return -1;
    else {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);


        if (lDepth > rDepth){
            return 1;
        }
        else{
            return 0;
        }

    }
}

struct node* semisplayright(struct node* y){
    //semi splay the tree to the right
    struct node* x = y->left;
    struct node* T1 = x->right;
    //after splaying:
    x->right = y;
    y->left = T1;
    return x;
}

struct node* semisplayleft(struct node* x){
    //semi splaying the tree to the left
    struct node* y = x->right;
    struct node* T1 = y->left;
    //after splaying:
    y->left = x;
    x->right = T1;

    return y;
}

//Splay condition
void splay2(struct node* root){
    if(maxDepth(root)==-1){
        return;
    }
    else if(maxDepth(root)==1){
        semisplayright(root);
    }
    else if(maxDepth(root)==0){
        semisplayleft(root);
    }
    return;
}

struct node* splay(struct node* root){
    if(maxDepth(root)==1){
        root = semisplayright(root);
        return root;
    }
    else if(maxDepth(root)==0){
        root = semisplayleft(root);
        return root;
    }
    return root;
}

struct node* semisplaying(struct node* root){
    if((root->left==NULL && root->right==NULL)){
        return root;
    }
    else if(maxDepth(root)==1){
        root=semisplayright(root);
        struct node* p=root;
        p=p->left;
        if(p->left->data=='$'||p->right->data=='$'||!isLeaf(p)){
            splay2(p);
        }
        return root;
    }
    else if(maxDepth(root)==0){
        root=semisplayleft(root);
        struct node* p=root;
        p=p->right;
        if(p->left->data=='$'||p->right->data=='$'||!isLeaf(p)){
            splay2(p);
        }
        return root;
    }
    return root;
}
void printCodes(struct node* root, int arr[],
				int top, int data)

{
    // Assign 0 to left edge and recur
    if (root->left) {

        arr[top] = 0;
		printCodes(root->left, arr,top + 1,data);
    }

	// Assign 1 to right edge and recur
    if (root->right) {
        arr[top] = 1;
		printCodes(root->right, arr, top + 1,data);
    }




	// If this is a leaf node, then
	// it contains one of the input
	// characters, print the character
	// and its code from arr[]
	if (isLeaf(root)&&root->data == data) {
            //printf("%c: ", root->data);
            printArr(arr, top);
        }

}

void CharCodes(struct node* root, int arr[],
				int top)

{
    // Assign 0 to left edge and recur
    if (root->left) {

        arr[top] = 0;
		CharCodes(root->left, arr,top + 1);
    }

	// Assign 1 to right edge and recur
    if (root->right) {
        arr[top] = 1;
		CharCodes(root->right, arr, top + 1);
    }




	// If this is a leaf node, then
	// it contains one of the input
	// characters, print the character
	// and its code from arr[]
	if (isLeaf(root)) {
            printf("\n%c: ", root->data);
            printArr(arr, top);
        }

}
void encode(struct node* root, char copydata[]){
    int arr[MAX_TREE_HT], top = 0;
    for(int l =0; l<strlen(copydata);l++){
        printCodes(root,arr,top,copydata[l]);
    }
    return;
}


// The main function that builds a
// Tree and print codes by traversing
// the built Tree
void SplayCodes(char data[],char copydata[], int freq[], int size)

{
    //char a[MAX_TREE_HT];
	struct node* root
		= buildTree(data, freq, size);
    int len = strlen(data);
    printf("\n");
    printf("The inorder traversal:\n");
    printInorder(root);
    printf("\n");
    int arr[MAX_TREE_HT], top = 0;
    //print code before splay
    printf("\n");
   	printf("\nLetter by letter encoding for Huffman ( without splaying )\n");
   	CharCodes(root,arr,top);
   	printf("\n");
   	printf("\n");
   	printf("Encoding");
   	printf("\n");
   	encode(root,copydata);

    //Print the code when splayed
	int arr3[MAX_TREE_HT], top3 = 0;
	printf("\n");
	if(len<=6){
        root = splay(root);
	}
	else{
        root = semisplaying(root);
	}
	printf("\n");
	printf("The inorder traversal:\n");
	printInorder(root);
	printf("\n");
    printf("\nLetter by letter encoding with semisplaying \n");
	CharCodes(root,arr3,top3);
	printf("\n\nEncoding\n");
	encode(root,copydata);

}

char checkchar(char c,char carr[],int size){
    int i;
    for(i=0;i<size;i++){
        if(carr[i]==c){
            return '^';
        }
        else{
            continue;
        }
    }
    return c;
}

int freqinit(const char* str,char c){
    int i;
    int count = 0;
    for(i=0; i<=strlen(str);i++){
        if(str[i]==c){
            count = count+1;
        }
        else{
            count = count;
        }
    }
    return count;
}

char* removeDuplicate(char str[], int n)
{
   // Used as index in the modified string
   int index = 0;

   // Traverse through all characters
   for (int i=0; i<n; i++) {

     // Check if str[i] is present before it
     int j;
     for (j=0; j<i; j++)
        if (str[i] == str[j])
           break;

     // If not present, then add it to
     // result.
     if (j == i)
        str[index++] = str[i];
   }

   return str;
}

void checkInArr(char str[],int freq[],int n ){
    // Used as index in the modified string
   int index = 0;

   // Traverse through all characters
   for (int i=0; i<n; i++) {

     // Check if str[i] is present before it
     int j;
     for (j=0; j<i; j++)
        if (str[i] == str[j])
           break;

     // If not present, then add it to
     // result.
     if (j == i)
        freq[index++] = freq[i];
   }

   return ;
}

