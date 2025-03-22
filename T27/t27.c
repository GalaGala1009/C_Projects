#include "t27.h"

// 'Internal' function prototypes 
// ...


int idx(char k){
    if(k == '\'') return 0;
    else if('A'<= k && k <= 'Z') return k-'A'+1;
    else if('a'<= k && k <= 'z') return k-'a'+1;
    return -1;
}


dict* dict_init(void){
    dict* node = malloc(sizeof(dict));
    node->up = NULL;
    for(int i=0;i<27;i++){
        node->dwn[i] = NULL;
    } 
    node->terminal = false;
    node->freq = 0;

    return node;
}


bool dict_addword(dict* p, const char* wd){  
    //check illegal char
    for(int i=0;wd[i]!='\0';i++){   
        if(idx(wd[i]) == -1) return false;
    }

    dict* cur = p;
    dict* parent = NULL;

    for(int i=0;wd[i]!='\0';i++){
        if(cur->dwn[idx(wd[i])] == NULL){
            cur->dwn[idx(wd[i])] = dict_init();
            cur->up = parent;
        }
        parent = cur;
        cur = cur->dwn[idx(wd[i])];
        
    }
    

    if(cur->up == NULL) cur->up = parent;

    cur->freq += 1;
    if(cur->terminal == true ) return false;
    cur->terminal = true;

    return true;
}


void dict_free(dict** d){
    if(d==NULL || *d == NULL) return;
    
    for(int i=0;i<27;i++){
        dict_free(&((*d)->dwn[i]));
    }
    
    free(*d);
    *d = NULL;
}


int dict_wordcount(const dict* p){
    if(p == NULL) return 0;

    int cnt = p->freq;
    for(int i=0;i<27;i++){
        cnt += dict_wordcount(p->dwn[i]);
    }

    return cnt;
}


int dict_nodecount(const dict* p){
    if(p == NULL) return 0;

    int cnt = 1;
    for(int i=0;i<27;i++){
        cnt += dict_nodecount(p->dwn[i]);    
    }

    return cnt;
}


dict* dict_spell(const dict* p, const char* str){
    if(p == NULL || str == NULL || str == "\0") return NULL;

    const dict* cur = p;

    for(int i=0;str[i]!='\0';i++){
        if(cur->dwn[idx(str[i])] == NULL) return NULL;
        cur = cur->dwn[idx(str[i])]; 
    }
    
    if(cur->terminal == 0) return NULL; 

    return (dict*)cur;
}


int dict_mostcommon(const dict* p){
    if(p == NULL) return 0;
    
    int maxfreq  = 0;

    for(int i=0;i<27;i++){ 
        if(p->dwn[i] != NULL){
            if(p->dwn[i]->freq > maxfreq){
                maxfreq = p->dwn[i]->freq;
            }
        }
        int child_freq = dict_mostcommon(p->dwn[i]);

        if(child_freq > maxfreq) maxfreq = child_freq;
    }

    return maxfreq;
}


// CHALLENGE1
unsigned dict_cmp(dict* p1, dict* p2){
    unsigned distance = 0;
    
    dict* path_1[50];
    
    int length_1 = 0;
    while(p1 != NULL){
        path_1[length_1] = p1;
        length_1++;
        p1 = p1->up;
    }

    int length_2 = 0;

    bool flag = true;
   
    while(p2 != NULL&&flag){
        for(int i=0;i<length_1&&flag;i++){
            if(p2 == path_1[i]){
                distance = length_2 + i;
                flag = false;
            }
        }
        length_2++;
        p2 = p2->up;
    }
    
    return distance;
}


// CHALLENGE2

void find_freq(dict* p, int mfreq, char* ret, int i, bool* flag){
    if(p == NULL) return;

    if( i > 0 && p->freq == mfreq){
        *flag = false;
        ret[i] = '\0';
        return;
    }

    for(int j=0;j<27&&(*flag);j++){
        if(p->dwn[j] == NULL) continue;
        if(j == 0) ret[i] = '\'';
        else ret[i] = 'a'+(j-1);
        find_freq(p->dwn[j], mfreq, ret, i+1, flag);
    }

}    


void dict_autocomplete(const dict* p, const char* wd, char* ret){
    if(p == NULL || wd == NULL) return;

    const dict* cur = p;
    for(int i=0;wd[i]!='\0';i++){
        cur = cur->dwn[idx(wd[i])];
    }

    int mostFreq = dict_mostcommon(cur);

    bool* flag = malloc(sizeof(bool));
    *flag = true;
    
    find_freq((dict*)cur, mostFreq, ret, 0, flag); 


}


void test(void){
    
}
