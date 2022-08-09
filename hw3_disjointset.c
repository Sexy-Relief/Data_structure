#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int ver1;
	int ver2;
	int weight;
} element;

element* heap;
int* vertices_set;

void insert_heap(element* item,int *n) {
	int i = ++(*n);
	while (i != 1 && item->weight < heap[i / 2].weight) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i].ver1 = item->ver1;
	heap[i].ver2 = item->ver2;
	heap[i].weight = item->weight;
}

element delete_heap(int* n) {
	int parent, child;
	element item, temp;
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if (child < *n && heap[child].weight > heap[child + 1].weight)
			child++;
		if (temp.weight > heap[child].weight) {
			heap[parent] = heap[child];
			parent = child;
			child = parent * 2;
		}
		else break;
	}
	heap[parent] = temp;
	return item;
}

int set_Find(int i) {
	for (; vertices_set[i] >= 0; i = vertices_set[i])
		;
	return i;
}

void set_Union(int i, int j) {
	i = set_Find(i);
	j = set_Find(j);
	
	int temp = vertices_set[i] + vertices_set[j];

	if (vertices_set[i] > vertices_set[j]) {
		vertices_set[i] = j;
		vertices_set[j] = temp;
	}
	else {
		vertices_set[j] = i;
		vertices_set[i] = temp;
	}
}


int main(int argc, char* argv[]) {
	clock_t start = clock();
	FILE* fp;
	int count = 0, n = 0, ver1, ver2, weight, i, vernum, edgenum;
	element *input;
	element temp;
	if (argc != 2) {
		printf("usage: ./hw3 input_filename\n");
		exit(-1);
	}

	fp = fopen(argv[1], "r");
	if (!fp) {
		printf("The input file does not exist.\n");
		exit(-1);
	}
	fscanf(fp, "%d", &vernum);
	fscanf(fp, "%d", &edgenum);

	vertices_set = malloc(vernum * sizeof(int));
	for (i = 0; i < vernum; i++)
		vertices_set[i] = -1;			//vertice들의 disjoint set을 위한 array initialization

	heap = malloc((edgenum+1) * sizeof(element));		//Kruskal algorythm 적용을 위해 min heap 생성
	input = malloc(sizeof(element));
	while (fscanf(fp, "%d %d %d", &ver1, &ver2, &weight) != EOF) {
		input->ver1 = ver1;
		input->ver2 = ver2;
		input->weight = weight;
		insert_heap(input, &n);
	}
	fclose(fp);
	free(input);
	
	fp = fopen("hw3_result.txt", "w");
	i = 0;
	while (i < vernum - 1 && n != 0) {
		temp = delete_heap(&n);
		if (set_Find(temp.ver1) != set_Find(temp.ver2)) {
			set_Union(temp.ver1, temp.ver2);
			fprintf(fp, "%d %d %d\n", temp.ver1, temp.ver2, temp.weight);
			count += temp.weight;
			i++;
		}
		else
			continue;
	}
	fprintf(fp,"%d\n", count);
	if (i == vernum - 1)
		fprintf(fp, "CONNECTED\n");
	else
		fprintf(fp, "DISCONNECTED\n");

	fclose(fp);
	free(vertices_set);
	free(heap);
	printf("output written to hw3_result.txt.\n");
	clock_t end = clock();
	printf("running time: %.6lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}