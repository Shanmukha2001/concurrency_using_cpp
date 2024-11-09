#include<string.h>
#include<stdio.h>

void exchange(char *src,size_t size,char *dest){
    memcpy(dest,src,size);
}

int main(){
    char *inp = "sample";
    size_t size = 7;
    char dest[7];
    exchange(inp,size,dest);
    printf("%s",dest);
}