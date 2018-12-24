#include <windows.h>
#include <stdio.h>  //for debugging
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#include "linkedList.hpp"
#include "compress.hpp"
#include "definition.hpp"
void buildOutputFileName(HWND hwnd,HWND *outputTip1,HWND *outputBar1,HWND *outputEnter)
{
    *outputTip1=CreateWindow("STATIC","想要播放的檔名為為:(免寫附檔名)(檔案需在\\records內)必填!",  //create window of tip
                             WS_BORDER|WS_CHILD|WS_VISIBLE,
                             100,100,420,20,
                             hwnd,NULL,NULL,NULL);
    *outputBar1=CreateWindow("EDIT","",                                                             //create window of input bar
                             WS_BORDER|WS_CHILD|WS_VISIBLE,
                             100,120,100,20,
                             hwnd,NULL,NULL,NULL);
    *outputEnter=CreateWindow("BUTTON","Enter",                                                     //create window of enter button
                              WS_VISIBLE|WS_CHILD|WS_BORDER,
                              200,120,70,20,
                              hwnd,(HMENU) 4,NULL,NULL);

}
void play(HWND hwnd)        //the function to play action from file
{
    FILE *data=fopen("data\\recordData.dat","r+");   ////insert the file name to read from
    char fileName[20]= {};
    fscanf(data,"%s",fileName);
    fclose(data);  //load file name


    char *mouse=(char *)calloc(sizeof(fileName)+16,1);   //string process of file name
    char *name=(char *)calloc(sizeof(fileName)+10,1);
    strcpy(name,"records\\");
    strcat(name,fileName);
    strcpy(mouse,name);
    strcat(mouse,"Mouse.amagoodR");


    decompress(mouse,hwnd);   //decompress the file we read

    strcat(mouse,"D");

    char *deleteFile=(char *)malloc(30*sizeof(char));   //string process of the command to delete the original file
    strcpy(deleteFile,"del ");
    strcat(deleteFile,mouse);

    FILE *recMouse;     //open the decompressed file
    //puts(mouse);
    //puts(keyboard);
    recMouse=fopen(mouse,"r");

    if(recMouse==nullptr)   //the program break if the user tries to read a file that doesn't exist
    {
        MessageBox(hwnd,"指定的檔案不存在","錯誤",MB_OK);
        return ;
    }

    //create linked list for instance storage
    dataStructure::NODE *x=allocateNode();        //std::vector<int> x;
    dataStructure::NODE *y=allocateNode();        //std::vector<int> y;
    dataStructure::NODE *Button=allocateNode();   //std::vector<int> Button;

    //remember the head of the linked list
    dataStructure::NODE *xHead=x;
    dataStructure::NODE *yHead=y;
    dataStructure::NODE *ButtonHead=Button;

    int i=0;
    int mouseX,mouseY,key,sleepTime;
    fscanf(recMouse,"%d",&sleepTime);  //read the sleep time
    while(fscanf(recMouse,"%d%d%d",&mouseX,&mouseY,&key)==3)  //load the file into linked list
    {
        pushBackAtEnd(x);         //x.push_back(mouseX);
        x=x->next;
        x->data=mouseX;
        pushBackAtEnd(y);         //y.push_back(mouseY);
        y=y->next;
        y->data=mouseY;

        pushBackAtEnd(Button);    //Button.push_back(key);
        Button=Button->next;
        Button->data=key;
        i++;
    }//while fscanf

    while(!(GetKeyState(F11)&0x8000))   //wating for user press F11 (virtual key=122)  &0x8000 in order to mask the thing don't want
        Sleep(1);

    int lastkey=0;  //this is to see if the original pressed ley is toggeled
    for(int j=0; j<i; j++)
    {
        SetCursorPos(xHead->data,yHead->data);   //set the cursor position
        if(lastkey!=ButtonHead->data&&lastkey!=0)   //toggel the button
        {
            if(lastkey==1)
                mouse_event (MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 ) ;
            else if(lastkey==2)
                mouse_event (MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 ) ;
            else
                keybd_event(lastkey,0,KEYEVENTF_KEYUP,0);

            lastkey=0;//nothing is pressed now
        }//if

        if(ButtonHead->data!=0&&ButtonHead->data!=lastkey)  //press the button
        {
            if(ButtonHead->data==1)
                mouse_event (MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 ) ;
            else if(ButtonHead->data==2)
                mouse_event (MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 ) ;
            else
                keybd_event(ButtonHead->data,0,0,0);

            lastkey=ButtonHead->data;  //remember the pressed button
        }//if

        Sleep(sleepTime);


        if((GetKeyState(F12)&0x8000))//press F12 to stop (virtual key =123)
        {
            MessageBox(hwnd,"強制停止撥放","提示",MB_OK);
            break;
        }

        //the node points to the next node
        xHead=xHead->next;
        yHead=yHead->next;
        ButtonHead=ButtonHead->next;
    }//for i
    MessageBox(hwnd,"撥放完成","提示",MB_OK);//noticification of play complete
    fclose(recMouse);//close file
    system(deleteFile);  // delete the original file
    freeAll(xHead);// free memory
    freeAll(yHead);
    free(deleteFile);
    freeAll(ButtonHead);
}//function play
