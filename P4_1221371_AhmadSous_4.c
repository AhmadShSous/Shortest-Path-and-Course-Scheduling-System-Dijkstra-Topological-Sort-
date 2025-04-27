// Name : Ahmad Shaher Sous       Num :1221371
// Doctor : Radi Jarrar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count =0;
int count2=-1;

//----------------------------------------------------------------------------
struct buildingNode{  //linked list to store all building
int index;            //index of each  building to Know the path with other building
char building[50];    //to store each building
char* preBuilding;////to store the pre building
int destence;  //to store the distence
int visited;     //if visited 1 if not 0
struct buildingNode* Next;
};
typedef struct buildingNode* Build;
typedef struct buildingNode build;


struct nodeHeap{  //to create structNode have the index of building  and the cost of it
int destence;     //to store the destance in each node
int index;
};

struct heap{      //to create array of struct
struct nodeHeap* arr;
int size;
};
typedef struct heap* Heap;


struct topologicalNode{                            //node for toplogicalSort
int indgree;
char course[50];
int index;                                         //the index for each node is the index in matrix
int visited;
};
typedef struct topologicalNode Gragh;


struct nodestack{                                       //node to create stack
struct nodestack* next;                                 //pointer to point next node
int index;                                              //index of courses and the the connection between courses
};
typedef struct nodestack* stack;


struct nodestack1{                                      //node to create stack
struct nodestack1* next;                                //pointer to point next node
char* word;
};
typedef struct nodestack1* stack1;


//----------------------------------------------------------------------------
void deleteFirstAndLastSpaces(char str[]);
void loadingTwoFiles(Gragh table[][50],int building[][50],Build allBuilding );

void insertIndgreeAndConection(Gragh eachLine[],Gragh table[][50],int indgree);
void insertInTable(Gragh table[][50],char* course);
Gragh* topologicalSort(Gragh table[][50]);
void printTopologicalSort(Gragh* sorted);
int isFound(Gragh table[][50], char* word);
void print(Gragh table[][50]);

void insertInWeightedGragh(int building[][50],Build allBuilding,char* word1,char* word2,int weighted);
int findBuilding(Build allBuilding,char* word);
Build findNodeBuilding(Build allBuilding,char* word);
Build findFromIndex(Build allBuilding, int index);
void calculateShortestDest(int building[][50],Build allBuilding,char* source,char* destenation,int flag);

stack createStack();
void push(stack top,int index);
int pop(stack Stack);
stack1 createStack1();
void push1(stack1 top,char* word);

void creatHeap(Heap heap);
void insertHeap(Heap heap,struct nodeHeap* node);
void rerangeAfterInsert(Heap heap,int index);
struct nodeHeap* dequeueHeap(Heap heap);
void rerangeAfterDelete(Heap heap,int index);
void deleteHeap(Heap heap);
//-----------------------------------------------------------------



//------------------main---------------------------------------

int main()
{
int building[50][50]; //initialize the array ...... AdjMatrix
for(int i=0;i<50;i++){
    for(int j =0;j<50;j++){
        building[i][j]=0;
    }
}
Build headAllBuilding;  //linked list to store all building
headAllBuilding = (Build)malloc(sizeof(struct buildingNode));
headAllBuilding->Next=NULL;
Gragh table [50][50];  //Adj matrix to toplogicalSort
Gragh* sort=NULL;   // to store the sorted courses
int selection=0;
int b = 1;
do{
printf("please enter number between 1-6: ");
printf("\n\n1. Load the two files.");
printf("\n2. Calculate the shortest distance between two buildings.");
printf("\n3. Print the shortest route between two buildings and the total distance.");
printf("\n4. Sort the courses using the topological sort.");
printf("\n5. Print the sorted courses.");
printf("\n6. Exit the application.\n\n");
printf("The selection is:- ");
scanf("%d", &selection);
printf("\n");
if(selection == 1) {
    loadingTwoFiles(table,building,headAllBuilding);
    b=1;//to print path or not
 }
else if(selection == 2){
char word1[50];
char word2[50];
printf("please enter the source word the path starts from what:-\n");
scanf("%s",word1);
printf("please enter the destenation word the path end where:-\n");
scanf("%s",word2);
int flag=0;
calculateShortestDest(building, headAllBuilding,word1,word2,flag);
}
else if(selection ==3){
char word1[50];
char word2[50];
printf("please enter the source word the path starts from what:-\n");
scanf("%s",word1);
printf("please enter the destenation word the path end where:-\n");
scanf("%s",word2);
int flag=1;
calculateShortestDest(building, headAllBuilding,word1,word2,flag);
}
else if(selection == 4){
  if(b==1){
  sort=topologicalSort(table);
  }
  b=0;
}
else if(selection == 5){
   print(table);
   printTopologicalSort(sort);
}
else if (selection== 6){
    printf("\t!Thank you!");
}
printf("\n\n");
 }while(selection !=6);

      //  print1(building, headAllBuilding);
    return 0;
}



//----------------------------------loading in file------------------------------------
void deleteFirstAndLastSpaces(char str[]) {
    int len = strlen(str);
    int i = 0;

    // Find the index of the first character that without space
    while (str[i]==' ') {  //to check if space or not
        i++;
    }

    if (i > 0) {
        for (int j = 0; j < len - i + 1; j++) {//shifting character in left and the first space delete
            str[j] = str[j + i];
        }
    }

    len = strlen(str);
    while (str[len - 1]==' ') {// to remove all spaces in last of string
        str[len - 1] = '\0';
        len--;
    }
}



 //to loading two files divided the lines and divided words in each lines in each file and insert in two graghs
void loadingTwoFiles(Gragh table[][50],int building[][50],Build allBuilding ){
count =0;
FILE* in1;
FILE* in2;
in1 = fopen("input_buildings.txt","r");
char token1[100];
while(fgets(token1,100,in1)!=NULL){ //divided the words in first file and insert in Adj matrix and linked list of building
  char b[3][50];
  int i=0;

  if(token1!=NULL){
    strtok(token1,"\n");
    char* word;
    word =strtok(token1,"#");
    while(word!=NULL){
    deleteFirstAndLastSpaces(word);
    strcpy(b[i],word);
    i++;
    word =strtok(NULL,"#");
    }
    int weighted =atoi(b[2]);
    insertInWeightedGragh(building,allBuilding,b[0],b[1],weighted);//b[0]: the first word , b[1]: the second word
  }

 }
  fclose(in1);
  in2 = fopen("input_courses.txt","r");
  char token2[100];
  while(fgets(token2,100,in2) !=NULL){ //divided the words in second file and insert in Adj matrix for topological sort
  if(token2!=NULL){
    strtok(token2,"\n");
    char* word;
    word =strtok(token2,"#");
    Gragh eachLine[10];  // store the all words without reiteration
    int i=0;
    int indgree=-1;
    while(word!=NULL){
    deleteFirstAndLastSpaces(word);
    strcpy(eachLine[i].course,word);
        i++;
    int is =isFound(table,word); //to check if found
    if(!is){
    insertInTable(table,word);
    }
    indgree++;
    word =strtok(NULL,"#");
    }
    insertIndgreeAndConection(eachLine,table,indgree);
  }
 }
  fclose(in2);
}



//------------------------------------Dijkstra--------------------------------
int findBuilding(Build allBuilding,char* word){ //to find index of struct node to insert in matrix
Build current = allBuilding->Next;
while(current!=NULL){
  if(!strcmp(current->building,word)) return current->index;
  current=current->Next;
 }
return -1;
}



void insertInWeightedGragh(int building[][50],Build allBuilding,char* word1,char* word2,int weighted){ //to insert in Adj matrix with weighted after finding the index of node in matrix
int index1=0;
int index2=0;
if(findBuilding(allBuilding,word1)==-1){ //if the building is not found in building linked list insert it
count2++;
index1 =count2;
Build current = allBuilding->Next;
allBuilding->Next =(Build)malloc(sizeof(struct buildingNode));
allBuilding->Next->index=index1;
strcpy(allBuilding->Next->building,word1);
allBuilding->Next->Next=current;
}
else{
    index1 =findBuilding(allBuilding,word1);
 }
if(findBuilding(allBuilding,word2)==-1){ // same in building two
count2++;
index2 =count2;
Build current = allBuilding->Next;
allBuilding->Next =(Build)malloc(sizeof(struct buildingNode));
allBuilding->Next->index=index2;
strcpy(allBuilding->Next->building,word2);
allBuilding->Next->Next=current;
}
else{
    index2 = findBuilding(allBuilding,word2);
}
building[index1][index2]= weighted;
}



Build findNodeBuilding(Build allBuilding,char* word){ //to find struct Node from linked lists by word
Build current = allBuilding->Next;
while(current!=NULL){
  if(!strcmp(current->building,word)) return current;
  current=current->Next;
 }
return NULL;
}


Build findFromIndex(Build allBuilding, int index){ //to find struct Node from linked lists by index
Build current = allBuilding->Next;
while(current!=NULL){
  if(current->index==index) return current;
  current=current->Next;
 }
return NULL;
}


//....................Dijkstra..........................................
void calculateShortestDest(int building[][50],Build allBuilding,char* source,char* destenation,int flag){//.....Dijkstra to find shortest path
Build current = allBuilding->Next;
Heap heap = (Heap)malloc(sizeof(struct heap)); //craetheap
creatHeap(heap);

while(current !=NULL){  //to making all nodes unvisited and make the distence of source 0 rhen insert the source in heap
   if(!strcmp(current->building,source)){
     current ->preBuilding =NULL;
     current->destence=0;
        current->visited=0;
     struct nodeHeap* h = (struct nodeHeap*)malloc(sizeof(struct nodeHeap));
     h->destence =current->destence;
     h->index = current->index;
     insertHeap(heap,h);
   }
   else{
   current->destence =INT_MAX;
   current->visited=0;
   }
    current=current->Next;
 }
  //dijkstra

 Build current2 =NULL;
    while(1){ //when the heap == NULL breaking f loop
        current2 = allBuilding->Next;   //to knowing the all building that having connection with building that having
        struct nodeHeap* min =dequeueHeap(heap);  //to fetch the min cost in heap
        if (min == NULL) break;   //if the heap is null  break the loop
        if(findFromIndex(allBuilding,min->index)->visited==1)  continue; //if the building is visited A,B then B,A A مابوخذها لانه مزيورة
        findFromIndex(allBuilding,min->index)->visited =1;// making min visited
    while (current2!=NULL){ //to change the distence after Knowing all building that have connection with min cost building
    int row =min->index;   //row the index of min cost building
    int column = findNodeBuilding(allBuilding,current2->building)->index; //column the index of nodes that having connection with min cost building
    if(building[row][column]>0){ //if there are connection(distance) between min cost building with other building
    if(min->destence + building[row][column] <  findFromIndex(allBuilding,column)->destence){ //if the path and cost min smaller than the cost of building that have connection with min cost change distance and prebuilding and insert in heap
       findFromIndex(allBuilding,column)->destence = min->destence + building[row][column]; //change destence
       findFromIndex(allBuilding,column)->preBuilding=findFromIndex(allBuilding,row)->building; //change pre
       struct nodeHeap* h; //insert in heap
       h = (struct nodeHeap*)malloc(sizeof(struct nodeHeap));
       h->destence =findFromIndex(allBuilding,column)->destence;
       h->index = findFromIndex(allBuilding,column)->index;
       insertHeap(heap,h);
      }
    }
    current2 = current2->Next;
   }
 }
   Build curr = findNodeBuilding(allBuilding,destenation); //know the node of destenation to know the cost of it
   if(curr->destence == INT_MAX) printf("\n\nNO PATH!\n"); //if there are no path between source and destenation the cost doesnot change
   else{
    printf("\n\nThe shorted destenation between %s and %s is:- %d\n",source,destenation,curr->destence);
    // if there are path insert the pre in stack لانه عكسي
    if(flag==1){
            if(!strcmp(source,destenation)) printf("\nThe shortest path between %s and %s is:   %s  ->  %s",source,destenation,source,destenation);
    else{
    stack1 s = createStack1();
    push1(s,destenation);
    while(strcmp(curr->preBuilding,source)){
    push1(s,curr->preBuilding);
    curr = findNodeBuilding(allBuilding,curr->preBuilding);
    }
    push1(s,source);
    //print the path by pop from stack
    printf("\nThe shortest path between %s and %s is:   ",source,destenation);
    while(s->next!=NULL){
     char* word =s->next->word;
     printf("%s   ",word);
     if(s->next->next!=NULL)  printf("->   ");
     s=s->next;
    }
   while (s != NULL) {
        stack1 temp = s;
        s = s->next;
        free(temp);
    }
   }
   }
}
   //free heap after finish
   free(heap->arr);
   free(heap);
 }




//---------------------TopolodicalSort----------------------------------
void insertInTable(Gragh table[][50],char* course){ //insert in Adj matrix for topological the matrix is 2D from vertix
count++;
strcpy(table[count][0].course,course);//0,1  1,0
table[count][0].index=count;
table[count][0].visited=0;
strcpy(table[0][count].course,course);
table[0][count].index=count;
table[0][count].visited=0;
}


void insertIndgreeAndConection(Gragh eachLine[],Gragh table[][50],int indgree){ //insert the indgree and connection if there are
table[isFound(table,eachLine[0].course)][0].indgree = indgree; // is found return the index of word then insert the indgree of the first in each line
table[0][isFound(table,eachLine[0].course)].indgree = indgree;

for(int i=1;i<=indgree;i++){ //insert the indgree of vertix
        int row = isFound(table,eachLine[i].course);
        int column = isFound(table,eachLine[0].course);
   table[row][column].index =1;
}
  }



int isFound(Gragh table[][50], char* word){ //to return the index of course in matrix
for(int i=0;i<=count;i++){
  if(strcmp(table[i][0].course,word)==0) return i;
 }
 return 0;
}


Gragh* topologicalSort(Gragh table[][50]){
    stack s= createStack();
    Gragh* sorted= (Gragh*)malloc(sizeof(Gragh)*50); //to store the sorted courses vertixes
    int j=0; // index of sorted
for(int i=1;i<=count;i++){ //push the indgree zero in stack
    if(table[i][0].indgree==0 && table[i][0].visited==0){
        push(s,i);
        strcpy(sorted[j].course,table[0][i].course);
        j++;
        table[i][0].visited=1;
        table[0][i].visited=1;
    }
}

while(s->next!= NULL){ //if stack null
        int ind = pop(s);    //pop return the index of course with index zero
  for(int k=1;k<=count;k++){ //to select the course have connection wih course have indgree zero
    if(table[ind][k].index==1){ //index is if there are connection
        table[0][k].indgree--;  //decrease the indgree that course indicate by the course have ingree zero
        table[k][0].indgree--;
      if(table[k][0].visited==0 &&table[k][0].indgree == 0){ //if indgree zero
        strcpy(sorted [j].course,table[k][0].course);       //push in stack
        j++;
        table[k][0].visited=1;
        table[0][k].visited=1;
        push(s,table[k][0].index);
      }

    }
   }
}

printf("The sorted is successful!");
  return sorted;
}

void printTopologicalSort(Gragh* sorted){ //to print the toplogicalSort in sorted array
    int i=0;
    printf("The Topological Sort order is:-\n");
while(i<count){
    printf("%d) %s\n",i+1,sorted[i].course);
    i++;

 }
}


void print(Gragh table[][50]){ // to print the gragh and if there are relation between courses
for(int i=1;i<=count;i++){
    printf("\t     %s  ", table[0][i].course);
}
printf("\n");
for(int i=1;i<=count;i++){  //print relation of each course with other courses
    printf("%s %d\t", table[i][0].course ,table[i][0].indgree);
    for(int j=1;j<=count;j++){
   printf("%d\t\t",table[i][j].index);
  }
  printf("\n");
 }

}



//---------------------------------------------------------------------------------

stack createStack(){                        //to create undostack and redostack
struct nodestack* top = (struct nodestack*)malloc(sizeof(stack)); //to create top
top->next=NULL;
if(top==NULL) printf("out space of memory");
return top;
}



void push(stack top,int index){ // to insert integer in undoStack and redoStack
stack temp = (struct nodestack*)malloc(sizeof(struct nodestack));
temp->index=index;
if(top->next ==NULL){   //if we want insert in first and the stack empty
 top->next= temp;
 temp->next= NULL;
 }
else{                   //if we want insert in first but not empty
 temp->next =top->next;
 top->next=temp;
 }
}



int pop(stack Stack){    //to remove from stack
    int index = Stack->next->index; //to return the index of top
    stack copy;
if(Stack->next!=NULL){    //if stack not empty
 copy =Stack->next;
 Stack->next=copy->next;
 free(copy);
 }
 return index;
}


stack1 createStack1(){                        //to create stack
struct nodestack1* top = (struct nodestack1*)malloc(sizeof(struct nodestack1)); //to create top
top->next=NULL;
if(top==NULL) printf("out space of memory");
return top;
}


void push1(stack1 top,char* word){ // to insert the word in stack
stack1 temp = (struct nodestack1*)malloc(sizeof(struct nodestack1));
temp->word= (char*)malloc(sizeof(word));
strcpy(temp->word,word);
if(top->next ==NULL){   //if we want insert in first and the stack empty
 top->next= temp;
 temp->next= NULL;
 }
else{                   //if we want insert in first but not empty
 temp->next =top->next;
 top->next=temp;
 }
}


//....heap...


void creatHeap(Heap heap){
  heap->arr=(struct nodeHeap*)malloc(sizeof(struct nodeHeap)*count2*2);  //to create array heap of struct
  heap->size=0;    //increase when adding every struct
}


void insertHeap(Heap heap,struct nodeHeap* node){
heap->arr[heap->size].destence = node->destence;   //adding every struct in array heap
heap->arr[heap->size].index = node->index;
rerangeAfterInsert(heap,heap->size); //to making smaller cost in root arr[0]
heap->size++;   //increase the size one when adding every struct
}


void rerangeAfterInsert(Heap heap,int index){
    if(index == 0) return ; // if the struct is root then  leave function
int parent = (index -1)/2; // to find parent to every node
if(heap->arr[index].destence < heap->arr[parent].destence) { //if parent cost larger than children do swaping
        // ....swap......
    int desTemp = heap->arr[index].destence;
    heap->arr[index].destence = heap->arr[parent].destence;
    heap->arr[parent].destence =  desTemp;
     int indexTemp = heap->arr[index].index;
    heap->arr[index].index = heap->arr[parent].index;
    heap->arr[parent].index = indexTemp ;
    rerangeAfterInsert(heap,parent);

 }
}



struct nodeHeap* dequeueHeap(Heap heap){
if(heap->size == 0) return NULL; //if not any node in array return NULL
    struct nodeHeap* min=(struct nodeHeap*)malloc(sizeof(struct nodeHeap));//return the STUCT OF min cost
    min->destence=heap->arr[0].destence;
    min->index = heap->arr[0].index;
    heap->arr[0].destence = heap->arr[heap->size-1].destence; //the last node become in root
    heap->arr[0].index = heap->arr[heap->size-1].index;
    heap->size--;
    rerangeAfterDelete(heap,0);  //to  make root the min cost and every parent smaller than children
    return min;
 }



void rerangeAfterDelete(Heap heap,int index){
  int left = 2*index + 1;  //to select the left of parent
  int right = 2*index + 2;  //to select the right of parent
  //then we will check if children is larger
  int small = index;
  if(heap ->arr[left].destence < heap->arr[small].destence)  small = left;
  if(heap ->arr[right].destence < heap->arr[small].destence) small = right;

  // ....swap between parent and smallest children......
  if(small != index){
    int desTemp = heap->arr[index].destence;
    heap->arr[index].destence = heap->arr[small].destence;
    heap->arr[small].destence =  desTemp;
     int indexTemp = heap->arr[index].index;
    heap->arr[index].index = heap->arr[small].index;
    heap->arr[small].index = indexTemp ;
    rerangeAfterDelete(heap,small);
  }
}

