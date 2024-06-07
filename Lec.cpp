#include "Lec.h"

static struct IDS DAT[12];

void lec(FILE *f){

    uint16_t IDL;
    uint16_t ID;
    uint16_t Lower;
    uint16_t IdLower;
    uint16_t DID;
    uint16_t TypeNH;
    uint16_t Info;
    uint16_t TypeNL;
    uint16_t Type;
    uint16_t Upper;
    uint16_t Valv;
    int CPU=0,Concentrator=0,TempS=0,Valve=0;

    while(!feof(f)){

        fread(&IDL,sizeof(uint16_t),1,f);
        fread(&DID,sizeof(uint16_t),1,f);
        fread(&Upper,sizeof(uint16_t),1,f);

        TypeNH=DID<<3;
        TypeNH=TypeNH>>15;
        TypeNH=TypeNH<<1;
        //printf("TypeNH : %u\n",TypeNH);

        TypeNL=DID<<12;
        TypeNL=TypeNL>>15;
        
        //printf("TypeNL : %u\n",TypeNL);
        Type=TypeNH+TypeNL;
        
        //printf("Type : %u\n",Type);

        if(Type==0){
            CPU=CPU+1;
        }
        if(Type==3){
            Concentrator=Concentrator+1;
        }
        if(Type==2){
            Valv=DID<<9;
            Valv=Valv>>15;
            //printf("Valv : %u\n",Valv);
            if(Valv==0){
                Valve=Valve+1;
            }
        }
        if(Type==1){
            
            Info=DID<<6;
            Info=Info>>14;
            // printf("Info :%u\n",Info);
            if(Info==1){
                TempS=TempS+1;
            }
        }

        ID=IDL>>6;
        //printf("ID : %u\n",ID);
        
        ID=ID<<6;
        Lower=IDL-ID;
       // printf("Lower %u\n",Lower);

        for(int i=0;i<Lower;i++){
            fread(&IdLower,sizeof(uint16_t),1,f);
           // printf("IdLower : %u\t",IdLower);
        }
        //printf("\n");
        
    }
    printf("CPU : %d \n",CPU);
    printf("Concentrator : %d \n", Concentrator);
    printf("TEMP SENSOR : %d \n", TempS-1);
    printf("VALVE : %d \n",Valve);
    
}

void PID(FILE *f){

    uint16_t IDL;
    uint16_t ID;
    uint16_t IDR;
    uint16_t Lower;
    uint16_t IdLower;
    uint16_t DID;
    uint16_t Info;
    uint16_t Upper;

    int h,w=0;
    printf("Secuencia a seguir\t");
    scanf("%d",&h);

    while(!feof(f)){
        

        fread(&IDL,sizeof(uint16_t),1,f);
        fread(&DID,sizeof(uint16_t),1,f);
        fread(&Upper,sizeof(uint16_t),1,f);

        IDR=IDL>>6;
        //printf("ID : %u\n",IDR);
        
        ID=IDR<<6;

        DAT[w].id=IDR;

        Lower=IDL-ID;
        //printf("Lower %u\n",Lower);

        for(int i=0;i<Lower;i++){
            fread(&DAT[w].lid[i],sizeof(uint16_t),1,f);
           // printf("IdLower : %u\t",IdLower);
        }
        //printf("\n");
        w=w+1;
        //printf("%d\n",w);
    }

    printf("ID %u",DAT[h].id-1);
    int j=DAT[h].id-1;
    int ww[10],n=0;
    h=1;
    while(j>1){
        for(int z=0;z<11;z++){
            for(int g=0;g<3;g++){
                if(j==DAT[z].lid[g]){
                    if(ww[n-1]!=DAT[z].id){
                        printf("-> ID %u",DAT[z].id);
                    }
                    
                    ww[n]=DAT[z].id;
                    n=n+1;
                    j=j-1;
                }
            }
        }
    }

}



