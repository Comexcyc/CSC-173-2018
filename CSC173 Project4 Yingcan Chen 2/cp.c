//
// Created by Yingcan Chen on 11/20/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cp.h"
#include "csg.h"
FILE *csgfile;
FILE *snapfile;
FILE *cpfile;
FILE *cdhfile;
FILE *crfile;
#define Size 1008
typedef struct snap{
    int studentid;
    char name[30];
    char address[50];
    char phone[9];
    int key;
}snap;

struct snap *snaphtarray[Size];



struct cp *cphtarray[Size];

void insertcp(struct cp data)
{

    struct cp *item =(struct cp*)malloc(sizeof(struct cp));
    strcpy(item->course,data.course);
    strcpy(item->prerequisite, data.prerequisite);
    item->key=coursehash(data.course);
    int hashindex=item->key;
    while(cphtarray[hashindex]!=NULL )
    {
        hashindex++;
        hashindex=hashindex%Size;
    }
    cphtarray[hashindex]=item;


}

void lookupcp(cp data)
{
    int flag=0;
    if(strcmp(data.course,"-1")!=0)
    {
        int index=coursehash(data.course);
        while(cphtarray[index]!=NULL )
        {
            if(strcmp(cphtarray[index]->course,data.course)==0 && (strcmp(cphtarray[index]->prerequisite,data.prerequisite)==0 || strcmp(data.prerequisite,"-1")==0) )
            {
                printf("%s,%s\n", cphtarray[index]->course, cphtarray[index]->prerequisite);
                flag++;
            }
            index++;
            index=index%Size;
        }
        if(flag==0)
        {
            printf("data not found\n");
        }
        return;
    }
    int i=0;
    for(i = 0; i<Size; i++)
    {
        if(cphtarray[i] != NULL)
        {
            if( strcmp(cphtarray[i]->prerequisite,data.prerequisite)==0 || strcmp(data.prerequisite,"-1")==0  )
            {
                printf("%s,%s\n", cphtarray[i]->course, cphtarray[i]->prerequisite);
                flag++;
            }
        }
    }
    if(flag==0)
    {
        printf("data not found\n");
    }

}

void displaycp()
{

    int i = 0;
    for(i = 0; i<Size; i++)
    {

        if(cphtarray[i] != NULL)
        {
            printf("%s,%s\n", cphtarray[i]->course, cphtarray[i]->prerequisite);
        }
    }
}

void deletecp(cp data)
{
    int flag=0;
    if(strcmp(data.course,"-1")!=0)
    {
        int index=coursehash(data.course);
        while(cphtarray[index]!=NULL )
        {
            if(strcmp(cphtarray[index]->course,data.course)==0 && (strcmp(cphtarray[index]->prerequisite,data.prerequisite)==0 || strcmp(data.prerequisite,"-1")==0) )
            {
                printf("delete:%s,%s\n", cphtarray[index]->course, cphtarray[index]->prerequisite);
                cphtarray[index]=NULL;
                flag++;
            }
            index++;
            index=index%Size;
        }
        if(flag==0)
        {
            printf("data not found\n");
        }
        else {
            displaycp();
        }
        return;
    }
    int i=0;
    for(i = 0; i<Size; i++)
    {
        if(cphtarray[i] != NULL)
        {
            if( strcmp(cphtarray[i]->prerequisite,data.prerequisite)==0 || strcmp(data.prerequisite,"-1")==0  )
            {
                printf("delete:%s,%s\n", cphtarray[i]->course, cphtarray[i]->prerequisite);
                cphtarray[i]=NULL;
                flag++;
            }
        }
    }
    if(flag==0)
    {
        printf("data not found\n");
    }
    else {
        displaycp();
    }
}

void savecp()
{
    char tmp[3000]="";

    int i = 0;
    for(i = 0; i<Size; i++)
    {
        if(cphtarray[i] != NULL)
        {
            char tmp1[200]="";
            strcat(tmp1,cphtarray[i]->course);
            strcat(tmp1,",");
            strcat(tmp1,cphtarray[i]->prerequisite);
            strcat(tmp1,",\n");
            strcat(tmp,tmp1);
        }
    }
    cpfile=fopen("../cp.txt","w+");
    fputs(tmp,cpfile);
    fclose(cpfile);
}

void insertfromcpfile()
{   char tempstring[100];
    cpfile=fopen("../cp.txt","r");
    cp tmp;
    int count=0;
    while(fgets(tempstring, 255, cpfile)!=NULL)
    {
        count =0;
        const char s[2]=",";
        char *b;
        b=strtok(tempstring,s);
        while(b!=NULL)
        {

            if(count==0)//course
            {

                strcpy(tmp.course,b);
            }
            else if(count==1)//prerequisite
            {

                strcpy(tmp.prerequisite,b);

            }
            count++;


            b=strtok(NULL,s);


        }
        insertcp(tmp);
    }
    fclose(cpfile);
}
