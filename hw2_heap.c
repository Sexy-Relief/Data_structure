#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENTS 1000000
//#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
//#define HEAP_EMPTY(n) (!n)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int key;
}element;

element max_heap[MAX_ELEMENTS];
element min_heap[MAX_ELEMENTS];
element temp_heap[MAX_ELEMENTS];

void Insert_Max(element item,int *m) {
	int i = ++(*m);
	while (i != 1 && item.key > max_heap[i / 2].key) {
		max_heap[i] = max_heap[i / 2];
		i /= 2;
	}
	max_heap[i] = item;
}

void Insert_Min(element item,int *n) {
	int i = ++(*n);
	while (i != 1 && item.key < min_heap[i / 2].key) {
		min_heap[i] = min_heap[i / 2];
		i /= 2;
	}
	min_heap[i] = item;
}

element Delete_Max(int *m) {
	int parent, child;
	element item, temp;
	item = max_heap[1];
	temp = max_heap[(*m)--];
	parent = 1;
	child = 2;

	while (child <= *m) {
		if (child < *m && max_heap[child].key < max_heap[child + 1].key)
			child++;
		if (temp.key < max_heap[child].key) {
			max_heap[parent] = max_heap[child];
			parent = child;
			child = parent * 2;
		}
		else break;
	}

	max_heap[parent] = temp;
	return item;

}
element Delete_Min(int* n) {
	int parent, child;
	element item, temp;
	item = min_heap[1];
	temp = min_heap[(*n)--];
	parent = 1;
	child = 2;

	while (child <= *n) {
		if (child < *n && min_heap[child].key > min_heap[child + 1].key)
			child++;
		if (temp.key > min_heap[child].key) {
			min_heap[parent] = min_heap[child];
			parent = child;
			child = parent * 2;
		}
		else break;
	}

	min_heap[parent] = temp;
	return item;
}

int main(int argc,char* argv[]) {
	clock_t start = clock();
	int i, m = 0, n = 0, storage;
	element temp;
	char command[20];
	FILE* fpread;
	FILE* fpwrite;
	if (argc != 2) {
		printf("usage: ./hw2 input_filename\n");		//argument error
		exit(-1);
	}

	fpread = fopen(argv[1], "r");
	fpwrite = fopen("hw2_result.txt", "w");
	if (!fpread) {
		printf("The input file does not exist.\n");		//file not exist
		exit(-1);
	}

	while (fscanf(fpread, "%s", command) != EOF) {

		if (!strcmp(command, "INSERT")) {
			fscanf(fpread, "%d", &temp.key);
			Insert_Max(temp, &m);
			Insert_Min(temp, &n);
		}
		else if (!strcmp(command, "ASCEND")) {
			storage = n;
			for (i = 1; i <= n; i++) 
					temp_heap[i] = min_heap[i];
			for (i = 0; i < storage; i++) {
				fprintf(fpwrite,"%d ", Delete_Min(&n).key);
			}
			n = storage;
			fprintf(fpwrite,"\n");
			for (i = 1; i <= n; i++) 
					min_heap[i] = temp_heap[i];
		}
		else if (!strcmp(command, "DESCEND")) {
			storage = m;
			for (i = 1; i <= n; i++)
					temp_heap[i] = max_heap[i];
			for (i = 0; i < storage; i++) {
				fprintf(fpwrite,"%d ", Delete_Max(&n).key);
			}
			m = storage;
			fprintf(fpwrite,"\n");
			for (i = 1; i <= n; i++) 
					max_heap[i] = temp_heap[i];
		}
		
	}

	fclose(fpread);
	fclose(fpwrite);
	printf("output written to hw2_result.txt.\n");
	clock_t end = clock();
	printf("running time: %.6lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}