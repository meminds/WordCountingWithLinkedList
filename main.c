#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct Node{
    int count;
    char data[100];
    struct Node *next;
};

void printList(struct Node *n){
        while(n!=NULL){
            printf("%s : %d\n",n->data,n->count);
            n=n->next;
        }

}


bool varMi(struct Node *n,char *world){
    while(n!=NULL){
        int sonuc = strcasecmp(n->data,world);
        if(sonuc == 0)
            return true;
        n=n->next;
    }
    return false;


}

void sonaEkle(struct Node **kokdugum ,int newCount,char *newData){
        struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
        struct Node *kokdugumSonuncu=*kokdugum;
        new_node->count=newCount;

        strcpy(new_node->data,newData);
        new_node->next=NULL;
            if(*kokdugum==NULL)
            {
                *kokdugum=new_node;
                return;
            }

            while(kokdugumSonuncu->next!=NULL)
                {

                        kokdugumSonuncu=kokdugumSonuncu->next;
                }
             kokdugumSonuncu->next=new_node;

}
void basaEkle(struct Node **kokdugum,int newCount,char *newData){
        struct Node *new_node=(struct Node*)malloc(sizeof(struct Node));

        new_node->count=newCount;
        strcpy(new_node->data,newData);
        new_node->next=(*kokdugum);
        (*kokdugum)=new_node;

}

void arayaEkle(struct Node **kokdugum,int newCount , char *newData){
            struct Node *new_node =(struct Node*)malloc(sizeof(struct Node));
            struct Node *kokGez=*kokdugum;
            new_node->count=newCount;
            strcpy(new_node->data,newData);

                while(kokGez->next!=NULL)
                {
                    if(kokGez->next->count<=newCount){
                            new_node->next=kokGez->next;
                            kokGez->next=new_node;
                            return;
                    }
                    kokGez=kokGez->next;
                }
}


int main(){
    struct Node* yeni = NULL;
    char word[100];
    char word2[100];
    int maxAdet=1;
    int minAdet=1;
    FILE * dosya = fopen("prolab3.txt","r");
    if(dosya==NULL)
    {
        printf("File not found...");
        exit(1);
    }
    while(fscanf(dosya,"%99s",word) != EOF)
    {
        int adet = 1;
        int i=0;
        while(word[i] != '\0')
            i++;
        int gosterge = ftell(dosya);
        fseek(dosya,gosterge,SEEK_SET);
        if(varMi(yeni,word))
            continue;
        while(fscanf(dosya,"%99s",word2) != EOF)
        {
            int j=0;
            while(word2[j] != '\0')
                j++;
            int sonuc = strcasecmp(word,word2);
            if (sonuc == 0)
                adet++;
        }
        if(adet>=maxAdet){
            basaEkle(&yeni,adet,&word);
            maxAdet=adet;
        }
        else if(adet<=minAdet){
            sonaEkle(&yeni,adet,&word);
            minAdet=adet;
        }
        else{
           arayaEkle(&yeni,(adet),&word);
        }

        fseek(dosya,gosterge,SEEK_SET);
    }
    printf("\n");
    printList(yeni);
    fclose(dosya);
    free(yeni);
    return 0;
}






