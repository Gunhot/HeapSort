#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_COMMAND 1000000
#define COMMAND_LENGTH 10
//Use the array representation of a binary tree
typedef struct{
	int key;
}element;
	
int heap_num;
/////////////////////////////////////////////////////////////////////////////////////////////////
element copied_heap[MAX_COMMAND] = {0,};
void copy_heap(element* heap){
	for(int i = 1; i <= heap_num; i++){
		copied_heap[i] = heap[i];
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
element max_heap[MAX_COMMAND] = {0,};
void insert_max_heap(element num, int the_index){
	//새로운 녀석(num.key)이 parent(max_heap[i/2]보다 클 때 parent를 child자리로 내린다.
	//parent의 자리는 child가 갖는다.
	while((the_index > 1) && (num.key > max_heap[the_index/2].key)){
		max_heap[the_index] = max_heap[the_index/2];
		the_index /= 2;
	}
	max_heap[the_index] = num;
}
element min_heap[MAX_COMMAND] = {0,};
void insert_min_heap(element num, int the_index){
	//새로운 녀석(num.key)이 parent(min_heap[i/2]보다 작을  때 parent를 child자리로 내린다.
	//parent의 자리는 child가 갖는다.
	while((the_index > 1) && (num.key < min_heap[the_index/2].key)){
		min_heap[the_index] = min_heap[the_index/2];
		the_index /= 2;
	}
	min_heap[the_index] = num;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

element return_max(int n){
	element item = copied_heap[1];
	element temp = copied_heap[n--];
	int parent = 1;
	int child = 2;
	while(child <= n){
		//RULE 1 : 더 큰 노드와  비교하고 싶다
		if(child != n){
			if(copied_heap[child].key < copied_heap[child + 1].key)
				child++;
		}
		//RULE 2 : 비교하려는 노드보다 크다면 탈출
		if(temp.key >= copied_heap[child].key) break;
		
		//RULE 3 : 더 큰 child노드를 parent로 올린다.
		copied_heap[parent] = copied_heap[child];
		
		//child를 parent로 두고 left_child를 살핀다.
		parent = child;
		child *= 2;
	}
	copied_heap[parent] = temp;
	return item;

}
element return_min(int n){
	//반납할 것
	element item = copied_heap[1];
	//일단 제일 작은
	element temp = copied_heap[n--];
	int parent = 1;
	int child = 2;
	//temp가 들어갈 자리를 찾으면서 정렬
	while(child <= n){
		//RULE 1 : 더 작은 노드와  비교
		if(child != n){
			if((copied_heap[child].key > copied_heap[child + 1].key)) child++;
		}
		//RULE 2 : 비교하려는 노드가 더 크다면 탈출
		if(temp.key <= copied_heap[child].key) break;
		//RULE 3 : 비교하려는 노드가 더 작다면 그 노드를 위로 올린다.
		copied_heap[parent] = copied_heap[child];
		//child의 left_child를 살핀다.

		parent = child;
		child *= 2;
	}
	copied_heap[parent] = temp;
	return item;
}

int main(int argc, char* argv[]){
	FILE *in;
	FILE *out;
	clock_t start = clock();
	char command[COMMAND_LENGTH];
	element num;
	//input number of arguments Handling
	if(argc != 2){
		printf("Usage: ./hw2 input_filename\n");
		return 1;
	}
	//input file error Handling
	in = fopen(argv[1], "r");
	if(in == NULL){
		printf("The input file does not exist.\n");
		return 1;	
	}
	out = fopen("hw2_result.txt","w");
	//Make Datastructure from Input File
	while(!feof(in)){
		fscanf(in,"%s %d", command, &num.key);

		if(strcmp(command,"INSERT") == 0){
			heap_num++;
			insert_max_heap(num, heap_num);
			insert_min_heap(num, heap_num);
			
		}
		if(strcmp(command,"ASCEND") == 0){
			copy_heap(min_heap);
			for(int i = 1; i <= heap_num; i++){
				element min; 
				min = return_min(heap_num - i + 1);	
				fprintf(out,"%d ", min.key);
			}
			fprintf(out,"\n");
		}
		if(strcmp(command,"DESCEND") == 0){
			copy_heap(max_heap);
			for(int i = 1; i <= heap_num; i++){
				element max;
				max = return_max(heap_num - i + 1);
				fprintf(out,"%d ",max.key);
			}
			fprintf(out,"\n");
		}
	
	}
	fclose(in);
	fclose(out);
	clock_t end = clock();
	printf("output written to hw2_result.txt.\n");
	printf("running time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

