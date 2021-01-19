#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#define NUM_LETTERS 26
#define WORD 60

typedef struct node {
   char letter;
   long unsigned int count;
   struct node* children[NUM_LETTERS];
} node;

node* getNode(char c){
	node *newNode = (node*)malloc(sizeof(node));
	if(newNode==NULL){
	   exit(1);
	}
	newNode->count = 0;
	newNode->letter = c;
	int i;
	for(i=0; i < NUM_LETTERS; ++i){
		newNode->children[i] = NULL;
	}
	return newNode;
}
 
 void insertTrie(node *root, char *str){
	 int index;
	 node *curr = root;
	 while(*str){
		 index = *str - 'a';
		 if(!curr->children[index]){
		    curr->children[index] = getNode((char)*str);
		 }
		 curr = curr->children[index];
		 ++str;
	 }
	 curr->count++;
}
void printRec(node *p, char *str, int i){
	if(p == NULL) return;
	if(p->count != 0){
		str[i] = '\0';
		printf("%s %ld\n",str, p->count);
	}
	int j;
    	for(j=0; j<NUM_LETTERS; ++j){
        	if(p->children[j]!=NULL){    
        		str[i] = j+'a';
        		printRec(p->children[j],str,i+1);
        	}
	}
}
void printRecRSort(node *p, char *str, int i){
	if(p == NULL) return;
	
	int j;
    	for(j=NUM_LETTERS-1; j >= 0; --j){
        	if(p->children[j]!=NULL){    
        		str[i] = j+'a';
        		printRecRSort(p->children[j],str,i+1);
        	   }
	   }
		if(p->count != 0){
		str[i] = '\0';
		printf("%s %ld\n",str, p->count);
               }
}
void freeTrie(node *root){
   if(root == NULL) return;
   for(int i=0; i < NUM_LETTERS; ++i){
         if(root->children[i]!=NULL){ 
		   freeTrie(root->children[i]);
   }
   }
   free(root);
}
int main(int argc, char *argv[]){
   node *root = getNode('*');
    char str[WORD];

	if (stdin){
	   while (fscanf(stdin, "%59s", str) == 1){
	        int i;
		for(i = 0; str[i]; i++){
		    str[i] = tolower(str[i]);		     
		    if(str[i] > 122 || str[i] < 97)
		       str[i] = '\0';
	}
		insertTrie(root,str);
	}
	fclose(stdin);
	}
	 if(argc == 2 && strcmp(argv[1]," r")){
	    printRecRSort(root,str,0);
	 }
	 else
		printRec(root,str,0);
	 freeTrie(root); 
	return 0;	
    
}
