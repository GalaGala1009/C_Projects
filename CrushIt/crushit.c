#include "crushit.h"
#include "mydefs.h"


bool initialise(state* s, const char* str){
    if(s==NULL||str==NULL) return false;

    for(int r=0;r<MAXROWS;r++){
        for(int c=0;c<WIDTH;c++){
            s->board[r][c] = '.';
        }
    }


    FILE *fptr;
    fptr = fopen(str, "r");
    if(fptr!=NULL){
        char text[100];
        int len = 0;
        while(1){
            char temp = fgetc(fptr);
            if(temp==EOF) break;
            if(temp>='A'&&temp<='Z'){
                text[len] = temp;
                len++;
            }
        }
        int cur = 0;
        for(int r=MAXROWS-len/WIDTH;r<MAXROWS;r++){
            for(int c=0;c<WIDTH;c++){
                s->board[r][c] = text[cur];
                cur++;
            }
        }
        return true;
    }
    int len = 0;
    //check str 
    for(int i=0;str[i]!='\0';i++){
        if(str[i]<'A'||str[i]>'Z') return false; 
        len++;
    }
    //check is len multiple of 5 or not
    if(len%5!=0) return false;

    int cur = 0;
    for(int r=MAXROWS-len/WIDTH;r<MAXROWS;r++){
        for(int c=0;c<WIDTH;c++){
            s->board[r][c] = str[cur];
            cur++;
        }
    }
    return true;
}



bool tostring(const state* s, char* str){
    if(s==NULL||str==NULL) return false;
    
    int cur = 0;
    int start_row = 0;
    for(int r=0;r<MAXROWS;r++){
        bool flag = 0;
        for(int c=0;c<WIDTH;c++){
            if(s->board[r][c]!='.'){
                start_row = r;
                flag = 1;
            }
        }
        if(flag) break;
    }
    
    if(start_row==0){
        str[0] = '\0';
        return true;
    }

    for(int r=start_row;r<MAXROWS;r++){
        for(int c=0;c<WIDTH;c++){
            str[cur] = s->board[r][c];
            cur++;
        }
    }
    str[cur]='\0';
    
    return true;
}


bool matches(state* s){
    //check is empty or not
    bool empty = 1;
    for(int r=0;r<MAXROWS;r++){
        for(int c=0;c<WIDTH;c++){
            if(s->board[r][c]!='.') empty = 0;
        }
    }
    if(empty) return false;

    int rec[240];
    int pos = 0;
    //check horization
    for(int r=14;r<MAXROWS;r++){
        int l = 1;
        char base = s->board[r][0];
        for(int c=1;c<WIDTH;c++){
            if(s->board[r][c]==base){
                l++;
            }else if(s->board[r][c]!=base){ //和base不相同
                if(l>=3) rec[pos] = r, rec[pos+1] = c, rec[pos+2] = l, rec[pos+3] = -1, pos += 4; //紀錄
                l = 1, base = s->board[r][c];
            }
        }
        if(l>=3) rec[pos] = r, rec[pos+1] = 5, rec[pos+2] = l, rec[pos+3] = -1, pos += 4; //紀錄
    }
    //check vertical
    for(int c=0;c<WIDTH;c++){
        int l = 1;
        char base = s->board[14][c];
        for(int r=15;r<MAXROWS;r++){
            if(s->board[r][c]==base){
                l++;
            }else if(s->board[r][c]!=base){
                if(l>=3) rec[pos] = r, rec[pos+1] = c, rec[pos+2] = l, rec[pos+3] = -2, pos += 4; //紀錄
                l = 1, base = s->board[r][c];
            }     
        }
        if(l>=3) rec[pos] = 20, rec[pos+1] = c, rec[pos+2] = l, rec[pos+3] = -2, pos += 4; //紀錄
    }
    //clean
    
    for(int i=0;i<pos;i+=4){
        if(rec[i+3]==-1){ 
            for(int j=1;j<=rec[i+2];j++){
                s->board[rec[i]][rec[i+1]-j] = '.';
            }
        }else{ 
            for(int j=1;j<=rec[i+2];j++){
                s->board[rec[i]-j][rec[i+1]] = '.';
            }
        }    
    }
    return true;
}



bool dropblocks(state* s){
    for(int r=14;r<MAXROWS;r++){
        for(int c=0;c<WIDTH;c++){
            if(s->board[r][c]=='.'){
                for(int i=0;i<r;i++){
                    s->board[r-i][c] = s->board[r-i-1][c];
                }
            }
            
        }
    }
    return true;
}

void test(void){

}
