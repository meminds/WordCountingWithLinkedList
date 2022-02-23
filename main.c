#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct Dugum{
    int count;
    char data[100];
    struct Dugum *sonraki;
};

void printList(struct Dugum *n){
        while(n!=NULL){
            printf("%s : %d\n",n->data,n->count);
            n=n->sonraki;
        }

}


bool varMi(struct Dugum *n,char *world){
    while(n!=NULL){
        int sonuc = strcasecmp(n->data,world);
        if(sonuc == 0)
            return true;
        n=n->sonraki;
    }
    return false;


}

void sonaEkle(struct Dugum **kokdugum ,int newCount,char *newData){
        struct Dugum *yeni_dugum = (struct Dugum*)malloc(sizeof(struct Dugum));
        struct Dugum *kokdugumSonuncu=*kokdugum;
        yeni_dugum->count=newCount;

        strcpy(yeni_dugum->data,newData);
        yeni_dugum->sonraki=NULL;
            if(*kokdugum==NULL)
            {
                *kokdugum=yeni_dugum;
                return;
            }

            while(kokdugumSonuncu->sonraki!=NULL)
                {

                        kokdugumSonuncu=kokdugumSonuncu->sonraki;
                }
             kokdugumSonuncu->sonraki=yeni_dugum;

}
void basaEkle(struct Dugum **kokdugum,int newCount,char *newData){
        struct Dugum *yeni_dugum=(struct Dugum*)malloc(sizeof(struct Dugum));

        yeni_dugum->count=newCount;
        strcpy(yeni_dugum->data,newData);
        yeni_dugum->sonraki=(*kokdugum);
        (*kokdugum)=yeni_dugum;

}

void arayaEkle(struct Dugum **kokdugum,int newCount , char *newData){
            struct Dugum *yeni_dugum =(struct Dugum*)malloc(sizeof(struct Dugum));
            struct Dugum *kokGez=*kokdugum;
            yeni_dugum->count=newCount;
            strcpy(yeni_dugum->data,newData);

                while(kokGez->sonraki!=NULL)
                {
                    if(kokGez->sonraki->count<=newCount){
                            yeni_dugum->sonraki=kokGez->sonraki;
                            kokGez->sonraki=yeni_dugum;
                            return;
                    }
                    kokGez=kokGez->sonraki;
                }
}


int main(){
    struct Dugum* yeni = NULL;
    char kelime[100];
    char kelime2[100];
    int maxAdet=1;
    int minAdet=1;
    FILE * dosya = fopen("prolab3.txt","r");
    if(dosya==NULL)
    {
        printf("dosya yok...");
        exit(1);
    }
    while(fscanf(dosya,"%99s",kelime) != EOF)
    {
        int adet = 1;
        int i=0;
        while(kelime[i] != '\0')
            i++;
        int gosterge = ftell(dosya);
        fseek(dosya,gosterge,SEEK_SET);
        if(varMi(yeni,kelime))
            continue;
        while(fscanf(dosya,"%99s",kelime2) != EOF)
        {
            int j=0;
            while(kelime2[j] != '\0')
                j++;
            int sonuc = strcasecmp(kelime,kelime2);
            if (sonuc == 0)
                adet++;
        }
        if(adet>=maxAdet){
            basaEkle(&yeni,adet,&kelime);
            maxAdet=adet;
        }
        else if(adet<=minAdet){
            sonaEkle(&yeni,adet,&kelime);
            minAdet=adet;
        }
        else{
           arayaEkle(&yeni,(adet),&kelime);
        }

        fseek(dosya,gosterge,SEEK_SET);
    }
    printf("\n");
    printList(yeni);
    fclose(dosya);
    free(yeni);
    return 0;
}






