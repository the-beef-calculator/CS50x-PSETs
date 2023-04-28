#include <pthread.h>
#include <sys/types.h>

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include <fcntl.h>
#define MEM_LIMIT 64000000
#define error(m, c) do{fprintf(stderr, "%s\n", m);exit(c);}while(0)
#define BINS 101
struct node {
  struct node *next;
  char *value;
};
typedef struct node node;
typedef struct {
  node **table;
  int size;
  int bins;
} hashset;
struct tnode{
	char* value;
	struct tnode* left;
	struct tnode* right;
};
typedef struct tnode tnode;//tnode is my binary tree node typedef
//hash set functions

tnode* talloc(){
	return (tnode*) malloc(sizeof(tnode));
}
int search(hashset h, char *val);
int insert(hashset *h, char *val);
hashset set_init();
//bst functions
tnode* talloc();
void inorder_print(tnode* root);
int bst_insert(tnode** root_p, char* val);
pthread_t pthread_t_null = (pthread_t) 0;
int MAX_WORD_LEN = 20;
hashset set_init() {
  hashset h = {(node **)malloc(BINS * sizeof(node *)), 0, BINS};
  for (int i = 0; i < BINS; i++)
    h.table[i] = NULL;
  return h;
}
static int hash(char *key, int bins) {
  unsigned hashval = 0;
  for (int i = 0; i < strlen(key); i++)
    hashval = 31 * hashval + key[i];
  return hashval % bins;
}

char *strdup(const char *s) {
    size_t size = strlen(s) + 1;
    char *p = malloc(size);
    if (p != NULL) {
        memcpy(p, s, size);
    }
    return p;
}
static void rehash(hashset*);
int insert(hashset *h, char *val) {
	if(search(*h, val)) // I found the value
		return 0;// duplicate
	if (h->size >= h->bins)//load factor >= 100%
		rehash(h);
	int index = hash(val, h->bins);
	node *new_element = (node *)malloc(sizeof(node));
	new_element->next = h->table[index];
	new_element->value = strdup(val);
	h->table[index] = new_element;
	h->size++;
	return 1;
}
static int next_prime(int min) {
  while (1) {
    int prime = 1;
    for (int div = 2; div <= sqrt(min); div++)
      if (min % div == 0) {//divisible by div
        prime = 0;//not prime
        break;
      }
    if (prime)
      return min;
    else
      min++;
  }
  return min;
}
static void rehash(hashset *h) {
	int next_size = next_prime(2 * h->bins);
	//fprintf(stderr, "Warning: rehashing from size %d to size %d\n",
		//h->bins, next_size);
	fflush(stderr);
	node **oldtable = h->table;
	int old_bins = h->bins;
	h->table = (node **)malloc(next_size * sizeof(node *));
	for (int i = 0; i < next_size; i++)
		h->table[i] = NULL;
	h->size = 0;
	h->bins = next_size;
	for (int i = 0; i < old_bins; i++){
		for (node *it = oldtable[i]; it; it = it->next){
			insert(h, it->value);
		}
	}
}
int search(hashset h, char *val) {
  int index = hash(val, h.bins);
  for (node *iterator = h.table[index]; iterator; iterator = iterator->next)
  {
	if (!strcmp(iterator->value, val))
		return 1;
  }
  return 0;
}

void* solve(void* arg) {
    int* arr = (int*)arg; // Cast the void* argument to an int* pointer
    int sum = 0;

    // Calculate the sum of the array
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }

    // Print the sum
    printf("The sum of the array is: %d\n", sum);

    // Exit the thread
    pthread_exit(NULL);
}

void print_buffer(char** sub_puzzle, int subpuzzle_rows, int subpuzzle_cols){
	//this function is used for printing the content of each buffer cell.
	//do NOT call this function anywhere in your final submission.
	printf("%d by %d\n", subpuzzle_rows, subpuzzle_cols);
	for(int i = 0; i < subpuzzle_rows;i++)
		for(int j = 0; j < subpuzzle_cols;j++)
			printf("%c%s", sub_puzzle[i][j], j == subpuzzle_cols - 1?"\n":"");
}


void inorder_print(tnode* root){
	if(root == NULL) return;
	inorder_print(root -> left);//visiting the left substree
	printf("%s ", root->value);//visitig the root
	inorder_print(root -> right);//visiting the left substree
}
int bst_insert(tnode** root_p, char* val){
	if((*root_p) == NULL){//tree is empty
		(*root_p) = talloc();
		(*root_p)->value = strdup(val);
		(*root_p)->left = (*root_p)->right = NULL;
		return 1;//successful insert
	}
	if(!strcmp((*root_p)->value, val))//duplicate!
		return 0;//unsuccessful
	if(strcmp((*root_p)->value, val) > 0)
		return bst_insert(&((*root_p)->left), val);
	return bst_insert(&((*root_p)->right), val);
}


int main(int argc, char** argv){
	if (argc < 11)
		error("Fatal Error. Usage: solve -dict dict.txt -input puzzle1mb.txt -size 1000 -nbuffer 64 -len 4:7 [-s]", 1);
	int puzzle_size = 0, buf_cells = 0, i = 0,j, fd, min_len = 0, max_len = 0, sorted = 0, buf_dimension;
	char* filename = NULL;
	FILE* dictionary_file;
	char*** buffer;
	while(++i < argc){
		if(argv[i][0] != '-')
			error("Fatal Error. Invalid CLA", 2);
		if(!strcmp(argv[i], "-size")){
			puzzle_size = atoi(argv[++i]);
			if(puzzle_size < 15 || puzzle_size > 46340)
				error("Fatal Error. Illegal value passed after -size",3);
		}
		else if(!strcmp(argv[i], "-nbuffer")){
			buf_cells = atoi(argv[++i]);
			if(buf_cells != 1 && buf_cells != 4 && buf_cells != 16
				&& buf_cells != 64)
				error("Fatal Error. Illegal value passed after -nbuffer",4);
			buf_dimension = (int)sqrt(MEM_LIMIT / buf_cells);
			//buf_cells = 1 -> buf_dimension = 8000
			//buf_cells = 4 -> buf_dimension = 4000
			//buf_cells = 16 -> buf_dimension = 2000
			//buf_cells = 64 -> buf_dimension = 1000
		}
		else if(!strcmp(argv[i], "-input")){
			filename = strdup(argv[++i]);
			fd = open(filename, O_RDONLY, 0);
			if(fd < 0)
				error("Fatal Error. Illegal value passed after -input",5);
		}else if(!strcmp(argv[i], "-dict")){
			dictionary_file = fopen(argv[++i], "r");
			if(!dictionary_file)
				error("Fatal Error. Illegal value passed after -dict",6);
		}else if(!strcmp(argv[i], "-len")){
			char* min_max = strdup(argv[++i]);
			char* max_str;
			if(strrchr(min_max, ':') != (max_str = strchr(min_max, ':'))
				|| !strchr(min_max, ':'))
				error("Fatal Error. Illegal value passed after -len",7);
			max_len = atoi(max_str+1);
			min_max[max_str - min_max] = '\0';
			min_len = atoi(min_max);
			if(min_len < 3 || max_len > 14 || min_len > max_len)
				error("Fatal Error. Illegal value passed after -len",7);
		}else if(!strcmp(argv[i], "-s"))
			sorted = 1;
		else{
			error("Fatal Error. Usage: solve -dict dict.txt -input puzzle1mb.txt -size 1000 -nbuffer 64 -len 4:7 [-s]", 1);
			break;
		}
	}
	//Read and move all words from dictionary_file to a new hash table (hashset)
	//Your code here...

	// Open dictionary file
FILE *dict_file = fopen("dict.txt", "r");
if (!dict_file) {
    error("Error: Failed to open dictionary file.", 1);
}

// Initialize hashset
hashset dictionary = set_init();

// Read words from dictionary file and insert into hashset
char *word = (char *)malloc(MAX_WORD_LEN * sizeof(char));
while (fgets(word, MAX_WORD_LEN, dict_file)) {
    // Remove newline character from word
    strtok(word, "\n");
    insert(&dictionary, word);
}

// Close dictionary file
fclose(dict_file);

// Free memory used by word
free(word);

	//allocate 64MB of buffer in the heap
	//buffer is a 3D array
	//on the outermost dimension, we have buf_cells elements
	//each element is given to one consumer thread
	//each element is going to store a (square-shape) sub-puzzle
	//each element is a square-shape 2D array of characters
	//dimension of this square-shape array is buf_dimension by buf_dimension
	buffer = (char***)malloc(buf_cells * sizeof(char**));
	for(i = 0;i < buf_cells;i++){
		buffer[i] = (char**)malloc(buf_dimension * sizeof(char*));
		for(j = 0; j < buf_dimension;j++)
			buffer[i][j] = (char*) malloc(buf_dimension);
	}
	int buf_index = 0;
	pthread_t t_id[buf_cells];
	for (i = 0; i < buf_cells; i++)
    t_id[i] = pthread_t_null;


for(int row = 0; row + max_len - 1 < puzzle_size; row += (buf_dimension - max_len + 1)){
		int subpuzzle_rows = (row + buf_dimension <= puzzle_size)?
				 buf_dimension:	puzzle_size - row;
		for(int column = 0; column + max_len - 1 < puzzle_size;column += (buf_dimension - max_len + 1)){
			long start = (long)row * (puzzle_size+1) + column;
			lseek(fd,start,SEEK_SET);
			int subpuzzle_cols = (column + buf_dimension <= puzzle_size)?
				 buf_dimension:	puzzle_size - column;
			if(t_id[buf_index])//if there is a busy consumer/solver,
				pthread_join(t_id[buf_index], NULL);//wait for it to finish the job before manipulating the buffer[buffer_index]
			for(i = 0; i < subpuzzle_rows;i++){
				int n_read = read(fd, buffer[buf_index][i], subpuzzle_cols);
				if(n_read < subpuzzle_cols)
					error("Fatal Error. Bad read from input file", 10);
				if(subpuzzle_cols < buf_dimension)l
					buffer[buf_index][i][subpuzzle_cols] = '\0';
				lseek(fd, puzzle_size-subpuzzle_cols+1, SEEK_CUR);
			}
			if(subpuzzle_rows < buf_dimension)
				buffer[buf_index][subpuzzle_rows][0] = '\0';

			fprintf(stderr, "Consuming buffer #%d\n", buf_index);
			char* message = (char*) malloc(1000);
			sprintf(message, "solving sub-puzzle of dimensions %d by %d located at index (%d,%d).",
			subpuzzle_rows, subpuzzle_cols, row, column);
			pthread_t thread_id;
			if (pthread_create(&thread_id, NULL, solve, (void*) message)) {
				fprintf(stderr, "Error: Failed to create solver thread.\n");
				exit(EXIT_FAILURE);
			}
			buf_index = (buf_index == buf_cells - 1)?0: buf_index + 1;
		}
	}
	for(int p = 0; p < buf_cells;p++)
	{
		if(t_id[p])
			pthread_join(t_id[p], NULL);
	}

		if(sorted){
	tnode* root = NULL;
	char wordd[100];
	while(scanf("%s", wordd) != EOF){
		if(bst_insert(&root, wordd))
			continue;
	}
	inorder_print(root);
}

}
