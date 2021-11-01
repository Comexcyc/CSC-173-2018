//
// Created by Yingcan Chen on 4/11/18.
//

#ifndef UNTITLED9_CSG_H
#define UNTITLED9_CSG_H
#include <stdio.h>
#include <stdlib.h>
//#define Size 1008;
typedef struct csg{
    char course[6];
    int studentid;
    char grade[3];
    int key;//key is studentid
}csg;
typedef struct cr{
    char course[6];
    char room[30];
    int key;
}cr;

int hashcode(int key);
int coursehash(char course[6]);
void insertcsg(struct csg data);

void displaycsg();
void insertfromcsgfile();
void lookupcsg(csg data);
void deletecsg(csg data);
void savecsg();
void insertfromcrfile();
void deletecr(cr data);
void displaycr();
void insertcr(struct cr data);
void lookupcr(cr data);
void savecr();
void lookup1(char tmpname[30],char tmpcourse[6]);
void lookup2(char tmpname[30],char tmptime[5],char tmpday[3]);
void selection(char course2[6]);
void projection(char course3[6]);
void reinsertcsg();
void stdiddisplay();

#endif //UNTITLED9_CSG_H
