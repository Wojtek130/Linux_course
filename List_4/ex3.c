#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h>

void main(){
    setuid(0);
    setgid(0);
    // printf("haha");x
    system("ps");
    // system("ps");
}