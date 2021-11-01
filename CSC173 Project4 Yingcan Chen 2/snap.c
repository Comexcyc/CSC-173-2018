//
// Created by Yingcan Chen on 4/11/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snap.h"
#include "csg.h"
#define Size 1008
FILE *csgfile;
FILE *snapfile;
FILE *cpfile;
FILE *cdhfile;
FILE *crfile;


struct snap *snaphtarray[Size];

void insertsnap(struct snap data)
{
    struct snap *item =(struct snap*)malloc(sizeof(struct snap));
    strcpy(item->name,data.name);
    strcpy(item->address, data.address);
    strcpy(item->phone,data.phone);
    item->studentid=data.studentid;
    item->key=data.studentid;
    int hashindex=hashcode(data.studentid);
    while(snaphtarray[hashindex]!=NULL )
    {
        hashindex++;
        hashindex=hashindex%Size;
    }
    snaphtarray[hashindex]=item;
}

void lookupsnap(snap data)
{
    int flag=0;
    if(data.studentid!=-1)
    {
        int index=hashcode(data.studentid);
        while(snaphtarray[index]!=NULL)
        {
            if(snaphtarray[index]->studentid==data.studentid && (strcmp(snaphtarray[index]->name,data.name)==0 || strcmp(data.name,"-1")==0) && (strcmp(snaphtarray[index]->address,data.address)==0 || strcmp(data.address,"-1")==0) && (strcmp(snaphtarray[index]->phone,data.phone)==0 || strcmp(data.phone,"-1")==0) )
            {
                printf("%d,%s,%s,%s\n", snaphtarray[index]->studentid, snaphtarray[index]->name, snaphtarray[index]->address, snaphtarray[index]->phone);
                flag++;
            }
            index++;
            index=index%Size;
        }
        if(flag==0)
        {
            printf("data not found\n");
        }
        return ;
    }
    int i=0;
    for(i = 0; i<Size; i++)
    {
        if(snaphtarray[i] != NULL)
        {
            if( (strcmp(snaphtarray[i]->name,data.name)==0 || strcmp(data.name,"-1")==0) && (strcmp(snaphtarray[i]->address,data.address)==0 || strcmp(data.address,"-1")==0) && (strcmp(snaphtarray[i]->phone,data.phone)==0 || strcmp(data.phone,"-1")==0) )
            {
                printf("%d,%s,%s,%s\n", snaphtarray[i]->studentid, snaphtarray[i]->name, snaphtarray[i]->address, snaphtarray[i]->phone);
                flag++;
            }
        }
    }
    if(flag==0)
    {
        printf("data not found\n");
    }
}

void displaysnap()
{
    int i = 0;
    for(i = 0; i<Size; i++)
    {
        if(snaphtarray[i] != NULL) {
            printf("%d,%s,%s,%s\n", snaphtarray[i]->studentid, snaphtarray[i]->name, snaphtarray[i]->address,
                   snaphtarray[i]->phone);
        }
    }
}

void deletesnap(snap data)
{
    int flag=0;
    if(data.studentid!=-1)
    {
        int index=hashcode(data.studentid);
        while(snaphtarray[index]!=NULL)
        {
            if(snaphtarray[index]->studentid==data.studentid && (strcmp(snaphtarray[index]->name,data.name)==0 || strcmp(data.name,"-1")==0) && (strcmp(snaphtarray[index]->address,data.address)==0 || strcmp(data.address,"-1")==0) && (strcmp(snaphtarray[index]->phone,data.phone)==0 || strcmp(data.phone,"-1")==0) )
            {
                printf("delete:%d,%s,%s,%s\n", snaphtarray[index]->studentid, snaphtarray[index]->name, snaphtarray[index]->address, snaphtarray[index]->phone);
                snaphtarray[index]=NULL;
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
            displaysnap();
        }
        return ;
    }
    int i=0;
    for(i = 0; i<Size; i++)
    {
        if(snaphtarray[i] != NULL)
        {
            if( (strcmp(snaphtarray[i]->name,data.name)==0 || strcmp(data.name,"-1")==0) && (strcmp(snaphtarray[i]->address,data.address)==0 || strcmp(data.address,"-1")==0) && (strcmp(snaphtarray[i]->phone,data.phone)==0 || strcmp(data.phone,"-1")==0) )
            {
                printf("delete:%d,%s,%s,%s\n", snaphtarray[i]->studentid, snaphtarray[i]->name, snaphtarray[i]->address, snaphtarray[i]->phone);
                snaphtarray[i]=NULL;
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
        displaysnap();
    }
}

void savesnap()
{
    char tmp[3000]="";

    int i = 0;
    for(i = 0; i<Size; i++)
    {
        if(snaphtarray[i] != NULL)
        {
            char tmp1[200]="";
            int tmpk=snaphtarray[i]->studentid;
            char* id = malloc( 5 + 1 );
            snprintf( id, 5 + 1, "%d", tmpk );
            strcat(tmp1,id);
            strcat(tmp1,",");
            strcat(tmp1,snaphtarray[i]->name);
            strcat(tmp1,",");
            strcat(tmp1,snaphtarray[i]->address);
            strcat(tmp1,",");
            strcat(tmp1,snaphtarray[i]->phone);
            strcat(tmp1,",\n");

            strcat(tmp,tmp1);
            free(id);

        }
    }
    snapfile=fopen("../snap.txt","w+");
    fputs(tmp,snapfile);
    fclose(snapfile);
}

void insertfromsnapfile()
{   char tempstring[100];
    snapfile=fopen("../snap.txt","r");
    snap tmp;
    int count=0;
    while(fgets(tempstring, 255,  snapfile)!=NULL)
    {
        count =0;
        const char s[2]=",";
        char *b;
        b=strtok(tempstring,s);
        while(b!=NULL)
        {
            if(count==0)//studentid
            {
                tmp.studentid=(b[0]-48)*10000+(b[1]-48)*1000+(b[2]-48)*100+(b[3]-48)*10+(b[4]-48)*1;
            }
            if(count==1)//name
            {
                strcpy(tmp.name,b);
            }
            if(count==2)//address
            {
                strcpy(tmp.address,b);
            }
            if(count==3)//phone
            {
                strcpy(tmp.phone,b);
            }
            b=strtok(NULL,s);
            count++;
        }
        insertsnap(tmp);
    }
    fclose(snapfile);
}

