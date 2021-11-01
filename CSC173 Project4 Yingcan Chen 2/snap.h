//
// Created by Yingcan Chen on 4/11/18.
//

#ifndef UNTITLED9_SNAP_H
#define UNTITLED9_SNAP_H
typedef struct snap{
    int studentid;
    char name[30];
    char address[50];
    char phone[9];
    int key;
}snap;

void insertsnap(struct snap data);
void insertfromsnapfile();
void displaysnap();
void lookupsnap(snap data);
void deletesnap(snap data);
void savesnap();
#endif //UNTITLED9_SNAP_H
