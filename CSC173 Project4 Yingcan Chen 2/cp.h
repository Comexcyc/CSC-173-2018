//
// Created by Yingcan Chen on 4/11/18.
//

#ifndef UNTITLED9_CP_H
#define UNTITLED9_CP_H
typedef struct cp{
    char course[6];
    char prerequisite[6];
    int key;
}cp;
void insertfromcpfile();
void displaycp();
void insertcp(struct cp data);
void lookupcp(cp data);
void deletecp(cp data);
void savecp();
#endif //UNTITLED9_CP_H
