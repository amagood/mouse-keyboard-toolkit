#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <algorithm>
#include <conio.h>
#include "compress.hpp"
//#include <vector>
#include "linkedList.hpp"
#include "definition.hpp"
#include "OutputStastic.hpp"

void buildInputFileName(HWND hwnd,HWND *inputBar,HWND *enter,HWND *tips,HWND *tips2,HWND *inputBar2)
{
    // const int nameMaxLength= 20;
    //  char *name=(char *)calloc(sizeof(char),nameMaxLength);
    *inputBar=CreateWindow("EDIT","",                         //create input bar
                           WS_BORDER|WS_CHILD|WS_VISIBLE,
                           100,120,100,20,
                           hwnd,NULL,NULL,NULL);
    *enter=CreateWindow("BUTTON","Enter",WS_VISIBLE|WS_CHILD|WS_BORDER,200,160,70,20,hwnd,(HMENU) 2,NULL,NULL);  //create enter box

    *tips=CreateWindow("STATIC","將錄製完的檔案命名為:(免寫附檔名)(檔案將放入\\records)必填!",     //create tips box
                       WS_BORDER|WS_CHILD|WS_VISIBLE,
                       100,100,420,20,
                       hwnd,NULL,NULL,NULL);

    *tips2=CreateWindow("STATIC","錄製檔案的精細度(多久錄一次，單位毫秒，最大10^9)預設為1",        //create tips box
                        WS_BORDER|WS_CHILD|WS_VISIBLE,
                        100,140,420,20,
                        hwnd,NULL,NULL,NULL);
    *inputBar2= CreateWindow("EDIT","",                                                            //create input bar
                             WS_BORDER|WS_CHILD|WS_VISIBLE,
                             100,160,100,20,
                             hwnd,NULL,NULL,NULL);

}
int string2int(char * name)      //change the number-string to string
{

    int length=strlen(name);
    char *s=(char*)calloc(sizeof(name),1);
    strcpy(s,name);
    std::reverse(s,s+length);
    int ans=0;
    for(int i=0,j=1; i<length; i++,j*=10)
    {
        ans+=(s[i]-'0')*j;
    }
    return ans;
}
int ButtonState()                   //check all of the button and return the pressed key's virtual key
{
    for(int i=0; i<255; i++)
        if((GetKeyState(i)&0x8000))
            return i;
    return 0;
}

void record(int sleepTime,HWND hwnd)       //record mouse and keyboard action
{
    //show tips.

    FILE *data=fopen("data\\recordData.dat","r+");    //insert the file name to save in
    char fileName[20]= {};
    fscanf(data,"%s",fileName);
    fclose(data);



    //printf("t=%d  S=%s\n",sleepTime,fileName);

    //puts(fileName);
    char *mouse=(char *)calloc(sizeof(fileName)+16,1);  //string process of the inside file name
    char *name=(char *)calloc(sizeof(fileName)+10,1);

    //filename process
    //records\\[filename]Mouse.amagoodR
    strcpy(name,"records\\");
    strcat(name,fileName);
    strcpy(mouse,name);
    strcat(mouse,"Mouse.amagoodR");

    FILE *recMouse;
    //puts(mouse);
    //puts(keyboard);
    recMouse=fopen(mouse,"w");



    //create linked list for instance data storage
    dataStructure::NODE *x=allocateNode();        //std::vector<int> x;
    dataStructure::NODE *y=allocateNode();        //std::vector<int> y;
    dataStructure::NODE *Button=allocateNode();   //std::vector<int> Button;

    //remember the head node's pointer of the linked list
    dataStructure::NODE *xHead=x;
    dataStructure::NODE *yHead=y;
    dataStructure::NODE *ButtonHead=Button;

    //x.reserve(68435000);
    //y.reserve(68435000);
    //Button.reserve(68435000);
    //printf("max=%d  %d\n",x.max_size(),y.max_size());


    //wating for user press F11 (virtual key=122)  &0x8000 in order to mask the thing don't want
    while(!(GetKeyState(F11)&0x8000))
        Sleep(1);
    printf("開始錄製按鍵!\n");//debug message

    POINT aPos;//aPos is for getting mouse position(aPos.x , aPos.y)

    //in the file , we first record sleeptime then record the position and key
    /**
    [time]
    [x] [y] [key ID (if pressed)]
    **/
    fprintf(recMouse,"%d\n",sleepTime);
    int i=0;
    while(!(GetKeyState(F12)&0x8000))//press F12 to stop(virtual key=123)
    {
        GetCursorPos(&aPos);      //record mouse position
        //save x position
        pushBackAtEnd(x);         //x.push_back(aPos.x);
        x=x->next;
        x->data=aPos.x;
        //save y position
        pushBackAtEnd(y);         //y.push_back(aPos.y);
        y=y->next;
        y->data=aPos.y;
        //save the number of the pressed button
        pushBackAtEnd(Button);    //Button.push_back(ButtonState());
        Button=Button->next;
        Button->data=ButtonState();

        i++;
        Sleep(sleepTime);

    }// while get key state
    //printf("\n停止記錄\n");

    for(int j=0; j<i; j++)
    {
        if(xHead!=nullptr&&yHead!=nullptr&&ButtonHead!=nullptr)  // go through linked lists
            fprintf(recMouse,"%d %d %d\n",xHead->data,yHead->data,ButtonHead->data);  //save data into file
        xHead=xHead->next;  // linked list push back
        yHead=yHead->next;
        ButtonHead=ButtonHead->next;
    }//for j

    MessageBox(hwnd,"錄製完成","提示",MB_OK);  //noticification of record complete
    //printf("\n儲存完成\n");
    fclose(recMouse);    //close all file

    //set the original file name and delete command into a string
    char *deleteFile=(char *)malloc(30*sizeof(char));
    strcpy(deleteFile,"del ");
    strcat(deleteFile,mouse);

    compress(mouse,hwnd);     //compress the record file

    system(deleteFile);  //delete the original file

    //statistic
    outputSort(mouse);

    free(mouse);      //free memory
    free(name);
    free(deleteFile);
    freeAll(x);
    freeAll(y);
    freeAll(Button);
}// function record
