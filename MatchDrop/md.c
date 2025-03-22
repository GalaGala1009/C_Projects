#include "mydefs.h"


bool file2str(const char* fname, char* str){  //ok
   if(fname==NULL||str==NULL) return false;

   FILE* fptr;
   fptr = fopen(fname, "r"); 
   int cur = 0;
   char temp;
   while(temp = fgetc(fptr)&&temp!=EOF){
      if(temp!='\n') str[cur] = temp;
      else str[cur] = '-';
      cur++;
   }

   str[cur-1] = '\0';

   return true;
}


state* str2state(const char* str){
   int rows = 0;
   int cols = 0;
   for(int i=1;str[i]!='\0';i++) if(str[i]=='-') rows++; 
   for(int i=2;str[i]!='\0'&&str[i]!='-';i++) cols++;
   

   state* s = (state*)malloc(sizeof(state));

   s->rows = rows;
   s->cols = cols;
   s->tail = 1;
   s->front = 0;
   
   s->list[0].parent = NULL; 
   s->list[0].hawk = str[0];    
   int r = 0, c = 0;
   for(int i=2;str[i]!='\0';i++){
      if(str[i]!='-'){
         s->list[0].bd[r][c] = str[i]; 
         c++;
      }else{
         r++;
         c = 0;
      }
   }

   return s;
}


void printBrd(board n, int r, int c){
   printf("%c\n", n.hawk);
   for(int i=0;i<r;i++){
      for(int j=0;j<c;j++){
         printf("%c", n.bd[i][j]);
      }
      printf("\n");
   }
}


void pop(state* s){
   s->front++;
}

void push(state* s , board n){
   s->list[s->tail] = n;
   s->tail++;
}


bool checkCols(board n, int col, int rows){
   for(int r=1;r<rows;r++){
      if(n.bd[r][col]!=n.bd[0][col]) return false;
   }
   return true;
}

bool checkExist(state* s, board n){
   for(int i=0;i<s->tail;i++){
      if(s->list[i].bd == n.bd && s->list[i].hawk == n.hawk) return false;
   }
   return true;
}


bool push_down(state* s, int rows, int cols){
   bool flag = true;
   int front = s->front;

   for(int c=0;c<cols;c++){
      if(checkCols(s->list[front], c, rows)==false){
         flag = false;
         board cur = s->list[front];
         for(int r=rows-1;r>0;r--){
            cur.bd[r][c] = cur.bd[r-1][c];
         }
         cur.bd[0][c] = s->list[front].hawk;
         cur.hawk = s->list[front].bd[rows-1][c];

         cur.parent = &(s->list[front]);

         if(checkExist(s, cur)==true){
            push(s, cur);
         }
      }
   }

   return flag;
}


bool checkBoard(board n, int rows, int cols){  
   int* rec = (int*)calloc(26, sizeof(int));  
   rec[n.hawk-'A']++; 

   for(int r=0;r<rows;r++){
      for(int c=0;c<cols;c++){
         rec[n.bd[r][c]-'A']++;
      }
   }
   int cnt = 0;
   for(int i=0;i<26;i++){
      if(rec[i]>=rows) cnt++;
   }
   if(cnt<cols) return false;
   return true;
}


int solve(state* s, bool verbose){
   if(checkBoard(s->list[0], s->rows, s->cols)==false) return -1;
   
   int moves = 0;
   bool flag = true;

   while(s->tail>s->front&&flag){    
      int len = s->tail-s->front;
      for(int i=0;i<len&&flag;i++){  
         if(push_down(s, s->rows, s->cols)==true) flag = false; 
         if(flag) pop(s);
      }
      if(flag) moves++;
   }

   //print solution
   if(verbose==true){
      board path[11];
      int idx = 0;
      board* cur = &(s->list[s->front]);
      while(cur!=NULL){
         path[idx] = *cur;
         cur = cur->parent;
         idx++;
      }
      for(int i=idx-1;i>=0;i--){
         printBrd(path[i], s->rows, s->cols);
      }
   }

   return moves;
}


void test(void){

}

/* Many of other functions, as required */
