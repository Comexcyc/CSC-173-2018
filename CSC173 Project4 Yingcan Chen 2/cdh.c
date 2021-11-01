//
// Created by Yingcan Chen on 4/11/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdh.h"
#include "csg.h"
FILE *csgfile;
FILE *snapfile;
FILE *cpfile;
FILE *cdhfile;
FILE *crfile;
#define Size 1008




struct cdh *cdhhtarray[Size];

void insertcdh(struct cdh data)
{
    struct cdh *item =(struct cdh*)malloc(sizeof(struct cdh));
    strcpy(item->course,data.course);
    strcpy(item->day, data.day);
    strcpy(item->hour, data.hour);
    item->key=coursehash(data.course);
    int hashindex=item->key;
    while(cdhhtarray[hashindex]!=NULL )
    {
        hashindex++;
        hashindex=hashindex%Size;
    }
    cdhhtarray[hashindex]=item;
}

void lookupcdh(cdh data)
{
    int flag=0;
    if(strcmp(data.course,"-1")!=0)
    {
        int index=coursehash(data.course);
        while(cdhhtarray[index]!=NULL )
        {
            if(strcmp(cdhhtarray[index]->course,data.course)==0 && (strcmp(cdhhtarray[index]->day,data.day)==0 || strcmp(data.day,"-1")==0)&& (strcmp(cdhhtarray[index]->hour,data.day)==0 || strcmp(data.day,"-1")==0) )
            {
                printf("%s,%s,%s\n", cdhhtarray[index]->course, cdhhtarray[index]->day,cdhhtarray[index]->hour);
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
        if(cdhhtarray[i] != NULL)
        {
            if( (strcmp(cdhhtarray[i]->day,data.day)==0 || strcmp(data.day,"-1")==0) && (strcmp(cdhhtarray[i]->hour,data.hour)==0 || strcmp(data.hour,"-1")==0) )
            {
                printf("%s,%s,%s\n", cdhhtarray[i]->course, cdhhtarray[i]->day,cdhhtarray[i]->hour);
                flag++;
            }
        }
    }
    if(flag==0)
    {
        printf("data not found\n");
    }
}

void displaycdh()
{
    int i = 0;
    for(i = 0; i<Size; i++)
    {
        if(cdhhtarray[i] != NULL)
        {
            printf("%s,%s,%s\n", cdhhtarray[i]->course, cdhhtarray[i]->day,cdhhtarray[i]->hour);
        }
    }
}

void deletecdh(cdh data)
{
    int flag=0;
    if(strcmp(data.course,"-1")!=0)
    {
        int index=coursehash(data.course);
        while(cdhhtarray[index]!=NULL )
        {
            if(strcmp(cdhhtarray[index]->course,data.course)==0 && (strcmp(cdhhtarray[index]->day,data.day)==0 || strcmp(data.day,"-1")==0)&& (strcmp(cdhhtarray[index]->hour,data.day)==0 || strcmp(data.day,"-1")==0) )
            {
                printf("delete:%s,%s,%s\n", cdhhtarray[index]->course, cdhhtarray[index]->day,cdhhtarray[index]->hour);
                cdhhtarray[index]=NULL;
                flag++;
            }
            index++;
            index=index%Size;
        }
        if(flag==0)
        {
            printf("data not found\n");
        }
        else
        {
            displaycdh();
        }
        return;
    }
    int i=0;
    for(i = 0; i<Size; i++)
    {
        if(cdhhtarray[i] != NULL)
        {
            if( (strcmp(cdhhtarray[i]->day,data.day)==0 || strcmp(data.day,"-1")==0) && (strcmp(cdhhtarray[i]->hour,data.hour)==0 || strcmp(data.hour,"-1")==0) )
            {
                printf("delete:%s,%s,%s\n", cdhhtarray[i]->course, cdhhtarray[i]->day,cdhhtarray[i]->hour);
                cdhhtarray[i]=NULL;
                flag++;
            }
        }
    }
    if(flag==0)
    {
        printf("data not found\n");
    }
    else
    {
        displaycdh();
    }
}

void savecdh()
{
    char tmp[3000]="";

    int i = 0;
    for(i = 0; i<Size; i++)
    {
        if(cdhhtarray[i] != NULL)
        {
            char tmp1[200]="";
            strcat(tmp1,cdhhtarray[i]->course);
            strcat(tmp1,",");
            strcat(tmp1,cdhhtarray[i]->day);
            strcat(tmp1,",");
            strcat(tmp1,cdhhtarray[i]->hour);
            strcat(tmp1,",\n");
            strcat(tmp,tmp1);
        }
    }
    cdhfile=fopen("../cdh.txt","w+");
    fputs(tmp,cdhfile);
    fclose(cdhfile);
}

void insertfromcdhfile()
{   char tempstring[100];
    cdhfile=fopen("../cdh.txt","r");
    cdh tmp;
    int count=0;
    while(fgets(tempstring, 255,  cdhfile)!=NULL)
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
            if(count==1)//day
            {
                strcpy(tmp.day,b);
            }
            if(count==2)//hour
            {
                strcpy(tmp.hour,b);
            }
            count++;
            b=strtok(NULL,s);
        }
        insertcdh(tmp);
    }
    fclose(cdhfile);
}

