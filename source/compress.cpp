#include <string.h>
#include <stdio.h>
#include<windows.h>
void compress(char *mouse,HWND hwnd)
{
    FILE *recMouse=fopen(mouse,"r");  //open the file to compress
    if(recMouse==nullptr)   //the program break if the user tries to read a file that doesn't exist
    {
        MessageBox(hwnd,"指定的檔案不存在","錯誤",MB_OK);
        return ;
    }
    char fileName[40]= {};
    strcpy(fileName,mouse);
    strcat(fileName,"C");
    FILE *newFile=fopen(fileName,"w");

    int time;   //keep the time data
    fscanf(recMouse,"%d",&time);
    fprintf(newFile,"%d\n",time);

    int x,y,key;
    int prex,prey,prekey;
    bool start=false;
    int i=1;
    while(fscanf(recMouse,"%d%d%d",&x,&y,&key)==3)
    {
        if(start&&(x!=prex||y!=prey||prekey!=key))     //print data and appear times
        {
            fprintf(newFile," %d\n",i);
            i=1;
            fprintf(newFile,"%d %d %d",x,y,key);
            prex=x;
            prey=y;
            prekey=key;

        }//if
        else if(start&&!(x!=prex||y!=prey||prekey!=key))
        {
            i++;
        }
        else  //!start
        {
            fprintf(newFile,"%d %d %d",x,y,key);
            prex=x;
            prey=y;
            prekey=key;
            start=true;
        }//else


    }//while fscanf
    fprintf(newFile," 1");
    fclose(newFile);//close file
    fclose(recMouse);
}//function compress
void decompress(char *mouse,HWND hwnd)
{
    char fileName[40]= {}; //open the file to decompress
    strcat(mouse,"C");
    strcpy(fileName,mouse);
    strcat(fileName,"D");
    FILE *oldFile=fopen(mouse,"r");
    if(oldFile==nullptr)   //the program break if the user tries to read a file that doesn't exist
    {
        MessageBox(hwnd,"指定的檔案不存在","錯誤",MB_OK);
        return ;
    }
    FILE *newFile=fopen(fileName,"w");

    int time;   //keep the time data
    fscanf(oldFile,"%d",&time);
    fprintf(newFile,"%d\n",time);


    int x,y,key,count;
    while(fscanf(oldFile,"%d%d%d%d",&x,&y,&key,&count)==4)   //print the data "count" times
    {
        for(int i=0; i<count; i++)
        {
            fprintf(newFile,"%d %d %d\n",x,y,key);
        }
    }

    fclose(oldFile);//close file
    fclose(newFile);
}//function decompress
