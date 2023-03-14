#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<math.h>


char* take_name(int size, char** array){
    char* name = (char*)malloc(sizeof(char)* 18);
    int y = 1;
    if(size > 0)  name = array[y];
    return name;
}

char*  return_size(char* name){
    char* str = (char*)malloc(sizeof(char)*400);
    int fd = open(name,O_RDONLY), shower, in = 0 ;
    char a;
    while((shower = read(fd, &a, 1)) != 0){
        if(a == '\n') return str;
        if(a >= '0' && a <= '9') str[in++] = a;
    }
    return str;
}

char* take_content(char* name){
    char* str = (char*)malloc(sizeof(char)*400);
    int fd = open(name,O_RDONLY), shower, in = 0 ;
    char a;
    while((shower = read(fd, &a, 1)) != 0){
        if(a == 'o' || a == '.') str[in++] = a;
    }
    return str;
}

int minem(int a, int b, int c, int index ){
    int min;
    if(index == 0) return 0;
    if( a == 0 || b == 0 || c == 0) return 0;
    if( (a<b) && (a<c)) min = a;
    else if(b<c) min = b;
    else min = c;
    return min;
}

void sign_bsq(int size_map, int size_square, int index, char* content){
    int T_lef, top_right, left, n_ind = index, tgis_inedes = index;
    for(int y = 0; y  < size_square - 1; y++) index--;
    left = index;
    int topFind = left;
    for(int y = 0; y  < size_square - 1; y++) n_ind -= size_map;
    top_right = n_ind;
    for(int y = 0; y  < size_square - 1; y++) topFind -= size_map;
    T_lef = topFind;
    int looper = 0, sign_stop = 0;
    int a = T_lef, b = top_right;
    while(content[looper]){
        if(looper % size_map == 0){ 
            if(looper != 0)printf("\n");
        }
        if(!sign_stop){
            if(looper >= a && looper <= b){
                printf("x");
            if(looper == b){
                a += size_map;
                b += size_map;
            } 
                if(looper == tgis_inedes) sign_stop = 1;
            }
            else printf("%c", content[looper]);
        }
        else printf("%c", content[looper]);
        looper++;
    }
}

void my_bsq(int size, char** array){
    char*name = take_name(size, array);
    char* content = take_content(name);
    int measure = atoi(return_size(name)), total_util = measure * measure + 1, left_top, right_top, left, square_here;
    int matrix[total_util], index = 0, sq_size_biggest[total_util], ind_next = 0, mine;
    for(int y = 0; content[y]; y++){
        switch(content[y]){
            case '.' :
                matrix[index] = 1;
            break;
            case 'o':
                matrix[index] = 0;
            break;
        }
        index++;
  }
    int loop = 0;
    while(loop < total_util - 1){
        if(loop < measure){
            sq_size_biggest[ind_next] = matrix[loop];
            ind_next++;
        }
        else if(loop % measure == 0){
            sq_size_biggest[ind_next] = matrix[loop];
            ind_next++;            
        } 
        else{
            right_top = abs(loop - measure);
            left = abs(loop - 1);
            left_top = abs((measure + 1) - loop);
            mine = minem(sq_size_biggest[left_top], sq_size_biggest[right_top], sq_size_biggest[left], matrix[loop]);
            if(mine != 0) {
                square_here = mine + 1;
            }
            else square_here = matrix[loop];
            sq_size_biggest[ind_next] = square_here;
            ind_next++;
        }
        loop++;
    }
  int big = 0, indexim ;
  for(int l = 0; l < measure; l++){
    for(int y = 0; y < total_util - 1; y++){
        if(sq_size_biggest[y] > 1){
            if(big < sq_size_biggest[y]) {
                big = sq_size_biggest[y];
                indexim = y;
            }
        }
  } 
} 
  sign_bsq(measure, big,  indexim, content);
}

int main(int ac, char** array)
{
    my_bsq(ac, array);
    return 0;
}
