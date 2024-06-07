#include "Lec.h"

int main(){

    FILE *f=fopen("network_structure.dat","rb");
    if(f==NULL){
        printf("sin archivo\n");
        return -1;
    }

    lec(f);
    rewind (f);
    PID(f);

}