#include <windows.h>
#include <stdio.h>// for DEBUG
#include "record.hpp"
#include "play.hpp"
#include "icon.hpp"
#include <string.h>
#include <thread>
#include "myNamespace.hpp"
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);//declaration of windows procedure

char szClassName[ ] = "WindowsApp";  //class name construction
namespace handleVar
{
HWND recordButton;// button number 1
HWND inputBar;
HWND inputEnter;  //button number 2
HWND inputTips1;
HWND inputBar2;
HWND inputTips2;
HWND playButton;  //button number 3
HWND outputTip1;
HWND outputBar1;
HWND outputEnter; //button number 4
//HWND scantxt;
}

//initial point
int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
{
    HWND hwnd;               // This is the handle for our window
    MSG messages;            // Here messages to the application are saved
    WNDCLASSEX wincl;

    //set windows type
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      // This function is called by windows
    wincl.style = CS_DBLCLKS;                 // Catch double-clicks
    wincl.cbSize = sizeof (WNDCLASSEX);
    // Use IMAGE_ICON and mouse-pointer
    wincl.hIcon =(HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON),IMAGE_ICON,256,256,0);
    wincl.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON),IMAGE_ICON,16,16,0);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 //set tool bar (no need)
    wincl.cbClsExtra = 0;                      // No extra bytes after the window class
    wincl.cbWndExtra = 0;                      // structure or the window instance
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND; //set window back colour

    //register window class (break out if failed)
    if (!RegisterClassEx (&wincl))
        return 0;

    //set windows config
    hwnd = CreateWindowEx (
               0,                    //Extended possibilites for variation
               szClassName,          //class name
               "按鍵精靈",           //title of the program
               WS_OVERLAPPEDWINDOW,  //type of the window
               CW_USEDEFAULT,        //Windows decides the position
               CW_USEDEFAULT,        //where the window ends up on the screen
               544,                  //width
               375,                  //hight
               HWND_DESKTOP,         // this window i make is the sub-window of the desktop
               NULL,                 //No menu
               hThisInstance,        //Program Instance handler
               NULL                  //No Window Creation data
           );

    //show this windows on the screen
    ShowWindow (hwnd, nFunsterStil);
    //infinite loop Untill the message get 0
    while (GetMessage (&messages, NULL, 0, 0))
    {
        // Translate virtual-key messages into character messages
        TranslateMessage(&messages);
        // Send message to WindowProcedure
        DispatchMessage(&messages);

    }
    // The program return-value is 0 - The value that PostQuitMessage() gave

    return messages.wParam;
}

//  This function is called by the Windows function DispatchMessage()
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{


    switch (message)                  // handle the messages
    {
    case WM_CREATE:  //happens when the windows(hwnd) is created
    {

        handleVar::recordButton=CreateWindow("BUTTON",
                                             "錄製按鍵"/*the text to show*/,WS_VISIBLE/*can see it*/|WS_CHILD/*child of HWND*/|WS_BORDER/*has boarder*/,
                                             20,20,100,100,
                                             hwnd/*the handle of parent window*/,(HMENU) 1/*button number*/,NULL,NULL);
        handleVar::playButton=CreateWindow("BUTTON",
                                           "播放按鍵",WS_VISIBLE|WS_CHILD|WS_BORDER,
                                           140,20,100,100,
                                           hwnd,(HMENU) 3,NULL,NULL);

        /*
        scantxt=CreateWindow("EDIT","",//預設的字
                   			 WS_BORDER|WS_CHILD|WS_VISIBLE,
        					 120,120,100,20,
        					 hwnd,NULL,NULL,NULL);
        HWND enter;
        enter=CreateWindow("BUTTON","Enter",WS_VISIBLE|WS_CHILD|WS_BORDER,220,120 ,70,20,hwnd,(HMENU) 2,NULL,NULL);
        break;
        */
        break;

    }//WM_CREATE

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case 1:    //button number     //handleVar::recordButton
        {
            //MessageBeep(MB_ICONERROR);//嗶嗶叫~~~
            //MessageBox(hwnd,"注意"/*文字*/,"Button was clicked"/*標題*/,MB_OK);
            DestroyWindow(handleVar::recordButton);
            DestroyWindow(handleVar::playButton);
            //create places to input
            buildInputFileName(hwnd,&handleVar::inputBar,&handleVar::inputEnter,&handleVar::inputTips1,&handleVar::inputTips2,&handleVar::inputBar2);
            //next the program will goto case 2:
            break;
        }//case 1:

        case 2:   // handleVar::inputEnter

        {
            int getwindowtextStat=0;
            const int nameMaxLength= 20;
            char *name=(char *)calloc(sizeof(char),nameMaxLength);
            int sleepTime;
            getwindowtextStat=GetWindowText(handleVar::inputBar,name,nameMaxLength);  //scanf
            char st[9]= {};
            GetWindowText(handleVar::inputBar2,st,9);
            DestroyWindow(handleVar::inputBar);     //clean screen
            DestroyWindow(handleVar::inputEnter);
            DestroyWindow(handleVar::inputTips1);
            DestroyWindow(handleVar::inputTips2);
            DestroyWindow(handleVar::inputBar2);

            sleepTime=string2int(st);
            //puts(name);
            char text[20]="將按鍵錄製到\0";
            strcat(text,name) ;
            //printf("%d",getwindowtextStat);
            MessageBox(hwnd,text,"提示",MB_OK);

            FILE *data;
            data=fopen("data\\recordData.dat","w");
            fputs(name,data);
            printf("%s",name);
            fclose(data);
            CreateWindow("STATIC","按F11按鍵以開始、按F12結束按鍵錄製，錄製結束後將自動儲存",//default word
                         WS_BORDER|WS_CHILD|WS_VISIBLE,
                         80,100,440,20,
                         hwnd,NULL,NULL,NULL);

            // start recording
            std::thread t1(record,sleepTime,hwnd);   //create a working thread
            //record(name,sleepTime);
            t1.detach();//detach t1 thread


            free(name);
            break;
        }//case 2:
        case 3:  //handleVar::platButton
        {
            DestroyWindow(handleVar::recordButton);
            DestroyWindow(handleVar::playButton);    //clean screen
            buildOutputFileName(hwnd,&handleVar::outputTip1,&handleVar::outputBar1,&handleVar::outputEnter); //scan the output file name
            //goto case 4 as user press enter
            break;
        }//case 3:
        case 4:
        {
            const int nameMaxLength= 20;
            char *name=(char *)calloc(sizeof(char),nameMaxLength);
            GetWindowText(handleVar::outputBar1,name,nameMaxLength);  //scanf
            DestroyWindow(handleVar::outputTip1);
            DestroyWindow(handleVar::outputBar1);
            DestroyWindow(handleVar::outputEnter);
            //printf("name ");
            //puts(name);
            char text[20]="讀取檔案\0";
            strcat(text,name) ;
            MessageBox(hwnd,text,"提示",MB_OK);
            FILE *data;
            data=fopen("data\\recordData.dat","w");
            fputs(name,data);//save filename
            //printf("%s",name);
            fclose(data);

            CreateWindow("STATIC","按F11按鍵以開始播放，按F12按鍵強制停止撥放",//default
                         WS_BORDER|WS_CHILD|WS_VISIBLE,
                         80,100,440,20,
                         hwnd,NULL,NULL,NULL);

            //create a working therad and detach it
            std::thread t2(play,hwnd);   //constructor hwnd is for jumpping reading file error messages
            t2.detach();


            free(name);
            break;
        }//case 4
        }  //switch LWORD(wParam)
        break;
    }//WM_COMMAND
    case WM_DESTROY:  //when the main window is destroyed
        PostQuitMessage (0);       // send a WM_QUIT to the message queue
        break;
    default:                      // for messages that we don't deal with
        return DefWindowProc (hwnd, message, wParam, lParam);
    }//switch message

    return 0;
}//WIN PROCDURE FUNCTION

