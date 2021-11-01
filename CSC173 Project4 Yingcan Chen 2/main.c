#include <stdio.h>
#include "csg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snap.h"
#include "cp.h"
#include "cdh.h"
FILE *csgfile;
FILE *snapfile;
FILE *cpfile;
FILE *cdhfile;
FILE *crfile;





int main() {

    printf("Begin test for part1\n\n\n");


    printf("Test the Course-Studentid-Grade Relation\n");
    printf("create csg.txt and put the data into it");
    csgfile=fopen("../csg.txt","w+");
    fputs("CS101,23426,A,\nCS101,23412,B,\nEE200,12345,C,\nEE200,22222,B+,\nCS101,33333,A-,\nPH100,67890,C+,\nCS265,23426,B,\nCS273,23412,B",csgfile);
    fclose(csgfile);


    printf("\ninsert the data to the hashtable\n");
    insertfromcsgfile();
    displaycsg();
    printf("\ninsert two more tuples and save them in csg.txt\n");
    csg csg1,csg2;
    csg1.studentid=12345;
    strcpy(csg1.course,"CS200");
    strcpy(csg1.grade,"A+");
    csg1.key=csg1.studentid;
    csg2.studentid=12333;
    strcpy(csg2.course,"CS102");
    strcpy(csg2.grade,"B+");
    csg2.key=csg2.studentid;
    insertcsg(csg1);
    insertcsg(csg2);
    displaycsg();

    printf("\nlook up function, type -1 if the information is unknown(preset lookup -1 -1 B+)\n");
    csg csglookup;
    csglookup.studentid=-1;
    strcpy(csglookup.course,"-1");
    strcpy(csglookup.grade,"B+");

    lookupcsg(csglookup);

    printf("\ndelete function test and save it in csg.txt after deleted it(delete -1 -1 B+)\n");
    deletecsg(csglookup);
    savecsg();

    printf("\ninsert the data we deleted again and save it\n");
    insertcsg(csglookup);
    displaycsg();
    savecsg();
    printf("\n\n\n");



    printf("\n\nTest the Studentid-Name-Adress-Phone\n");
    printf("create snap.txt and put the data into it\n");
    snapfile=fopen("../snap.txt","w+");
    fputs("12345,C. Brown,12 Apple St.,555-1234,\n67890,L. Van Pelt,34 Pear Ave.,555-5678,\n22222,P.Patty,56 Grape Blvd,555-9999,",snapfile);
    fclose(snapfile);
    printf("insert the data to the hashtable\n");
    insertfromsnapfile();
    displaysnap();


    printf("\ninsert one more tuples and save them in csg.txt\n");
    snap snap1;
    snap1.studentid=23426;
    strcpy(snap1.name,"Yingcan");
    strcpy(snap1.address,"300 Kendrick RD");
    strcpy(snap1.phone,"747-2062");
    snap1.key=snap1.studentid;
    insertsnap(snap1);
    displaysnap();


    printf("\ninsert one more tuples and save them in csg.txt\n");
    snap snap2;
    snap2.studentid=23412;
    strcpy(snap2.name,"Zhifan");
    strcpy(snap2.address,"400 Kendrick RD");
    strcpy(snap2.phone,"520-7970");
    snap2.key=snap2.studentid;
    insertsnap(snap2);
    displaysnap();



    printf("\nlook up function, type -1 if the information is unknown(preset lookup -1 L. Van Pelt -1 555-5678)\n");
    snap snaplookup;
    snaplookup.studentid=-1;
    strcpy(snaplookup.name,"L. Van Pelt");
    strcpy(snaplookup.address,"-1");
    strcpy(snaplookup.phone,"555-5678");
    snaplookup.key=snaplookup.studentid;
    lookupsnap(snaplookup);



    printf("\ndelete function test and save it in snap.txt after deleted it(delete -1 -1 -1 555-9999)\n");
    snap snapdelete;
    snapdelete.studentid=-1;
    strcpy(snapdelete.name,"-1");
    strcpy(snapdelete.address,"-1");
    strcpy(snapdelete.phone,"555-9999");
    snapdelete.key=snapdelete.studentid;
    deletesnap(snapdelete);
    savesnap();
    printf("\n\n\n");





    printf("\n\nTest the Course-Prerequisite\n");
    printf("create cp.txt and put the data into it\n");
    cpfile=fopen("../cp.txt","w+");
    fputs("CS101,CS100,\nCS206,CS121,\nCS206,CS205,\nEE200,EE005,\nEE200,CS100,\nCS120,CS101,\nCS121,CS120,\nCS205,CS101,\nCS173,CS161",cpfile);
    fclose(cpfile);
    printf("insert the data to the hashtable\n");
    insertfromcpfile();
    displaycp();

    printf("\ninsert one more tuples and save them in csg.txt\n");
    cp cp1;
    strcpy(cp1.course,"PH142");
    strcpy(cp1.prerequisite,"MA162");
    cp1.key=coursehash(cp1.course);
    insertcp(cp1);
    displaycp();

    printf("\nlook up function, type -1 if the information is unknown(preset lookup cs206 -1)\n");
    cp cplookup;
    strcpy(cplookup.course,"CS206");
    strcpy(cplookup.prerequisite,"-1");
    cplookup.key=coursehash(cplookup.course);
    lookupcp(cplookup);

    printf("\ndelete function test and save it in cp.txt after deleted it(delete CS206 -1)\n");
    deletecp(cplookup);
    savecp();

    printf("\n\n\n");



    printf("\n\nTest the Course-Day-Hour\n");
    printf("create cdh.txt and put the data into it\n");
    cdhfile=fopen("../cdh.txt","w+");
    fputs("CS101,M,9AM,\nCS101,W,9AM,\nEE200,W,1PM,\nEE200,Tu,10AM,\nCS101,F,9AM,\nEE200,Th,10AM,",cdhfile);
    fclose(cdhfile);
    printf("insert the data to the hashtable\n");
    insertfromcdhfile();
    displaycdh();

    printf("\ninsert one more tuples and save them in cdh.txt\n");
    cdh cdh1;
    strcpy(cdh1.course,"PH142");
    strcpy(cdh1.day,"Th");
    strcpy(cdh1.hour,"10AM");
    cdh1.key=coursehash(cdh1.course);
    insertcdh(cdh1);
    displaycdh();

    printf("\nlook up function, -1 means the information in unknown(preset lookup -1 W -1)\n");
    cdh cdhlookup;
    strcpy(cdhlookup.course,"-1");
    strcpy(cdhlookup.day,"W");
    strcpy(cdhlookup.hour,"-1");
    cdhlookup.key=coursehash(cdhlookup.course);
    lookupcdh(cdhlookup);


    printf("\ndelete function test and save it in cp.txt after deleted it(delete -1 W -1)\n");
    deletecdh(cdhlookup);
    savecdh();
    printf("\n\n\n");




    printf("\n\nTest the Course-Room\n");
    printf("create cr.txt and put the data into it\n");
    crfile=fopen("../cr.txt","w+");
    fputs("CS101,Turing Aud.,\nEE200,25 Ohm Hall,\nPH100,Newton Lab.,",crfile);
    fclose(crfile);
    printf("insert the data to the hashtable\n");
    insertfromcrfile();
    displaycr();

    printf("\ninsert one more tuples and save it in cr.txt\n");
    cr cr1;
    strcpy(cr1.course,"PH142");
    strcpy(cr1.room,"Hoyt Aud.");
    cr1.key=coursehash(cr1.course);
    insertcr(cr1);
    displaycr();

    printf("\nlook up function, type -1 if the information is unknown(preset lookup PH100 -1.)\n");
    cr crlookup;
    strcpy(crlookup.course,"PH100");
    strcpy(crlookup.room,"-1");
    crlookup.key=coursehash(crlookup.course);
    lookupcr(crlookup);


    printf("\ndelete function test and save it in cr.txt after deleted it(delete PH100 -1)\n");
    deletecr(crlookup);
    savecr();
    printf("\n\n\n");


    displaycsg();
    displaysnap();
    displaycr();
    displaycp();
    displaycdh();

    char tmpname[30];
    char tmpcourse[6];
    printf("\n\npart 2 Q1 \n");
    printf("What Grade did StudentName get in Course-Name?  Yingcan and Zhifan are two pretty good choice to put in\n");
    printf("Please input a StudentName\n");
    scanf ("%[^\n]%*c", tmpname);
    printf("Please input a Course name\n");
    scanf("%[^\n]%*c",tmpcourse);

    printf("Start lookup\n");
    printf("%s %s\n",tmpname,tmpcourse);
    lookup1(tmpname, tmpcourse);



    char tmpday2[3];
    char tmptime2[5];
    printf("\n\n part 2 Q2 \n");
    printf("Where is Student name at time and day??\n");
    printf("Please input a StudentName\n");
    scanf ("%[^\n]%*c", tmpname);
    printf("Please input a time\n");
    scanf("%[^\n]%*c",tmptime2);
    printf("Please input a day\n");
    scanf("%[^\n]%*c",tmpday2);
    lookup2(tmpname, tmptime2,tmpday2);

    char course3[30];


    printf("\n\npart 3 8.13 \n");
    printf("reinsert the data into csg file\n");
    reinsertcsg();
    printf("what is the specified course? (for CSG)\n");
    printf("Please input a course\n");
    scanf ("%[^\n]%*c", course3);
    printf("function projection initiated");
    projection(course3);
    stdiddisplay();





    printf("\n\npart 3 8.12 \n");
    printf("what is the specified course? (for CSG)\n");
    printf("Please input a course\n");
    scanf ("%[^\n]%*c", course3);
    printf("function selection initiated");
    selection(course3);
    printf("the selected course-studentid-grade is:\n");
    displaycsg();




    printf("\n\n 8.14\n");

    return 0;
}