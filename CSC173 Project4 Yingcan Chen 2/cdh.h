//
// Created by Yingcan Chen on 4/11/18.
//

#ifndef UNTITLED9_CDH_H
#define UNTITLED9_CDH_H
typedef struct cdh{
    char course[6];
    char day[3];
    char hour[5];
    int key;
}cdh;


void insertfromcdhfile();
void displaycdh();
void insertcdh(struct cdh data);
void lookupcdh(cdh data);
void deletecdh(cdh data);
void savecdh();



#endif //UNTITLED9_CDH_H
