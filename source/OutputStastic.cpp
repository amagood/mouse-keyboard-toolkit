#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mySort.hpp"
int *operateSearchAndBuildArray(FILE *input,FILE *output,int wantX,int wantY,int &size)
{
    //void the scan rate
    fscanf(input,"%*c\n");
    int *arr=nullptr;
    int trash,x,y,speed;
    bool found=false;
    fscanf(input,"%d%d%d%d",&x,&y,&trash,&speed);
    while(fscanf(input,"%d%d%d%d",&x,&y,&trash,&speed)==4)
    {
        if(x==wantX&&y==wantY)
        {
            found=true;
        }
        size++;
        if(size==1)
        {
            arr=(int *)calloc(sizeof(int),size);
        }
        else  //realloc
        {
            int *tmp;
            //don't need to free the original memory because it is already freed by realloc
            tmp=(int *)realloc(arr,sizeof(int)*size);

            if(tmp==nullptr)
            {
                //allocate failed
                fprintf(output,"ERROR: Memory Shortage\n錯誤 : 記憶體不足\n (BUILD)");
                free(arr);
                return nullptr;
            }//if
            arr=tmp;
        }//else
        arr[size-1]=speed;


    }
    if(found)
    {
        fprintf(output,"found\n");
    }
    else
    {
        fprintf(output,"not found\n");
    }
    return arr;
}


void outputSort(char *fName)
{
    FILE *cfg=fopen("config\\config.cfg","r");

    //use default settings if config is missed
    if(cfg==nullptr)
    {
        //create new default config file
        cfg=fopen("config\\config.cfg","w");
        ///inside default file:
        /**
        false
        0 0
        If you want to sort the speed of your input after recording or search if your mouse have been to a place, please choose true.
        If you chose true, you should enter a position (x,y) to search
        The output file would be at statistic\output.txt
        **/
        fprintf(cfg,"false\n0 0\nIf you want to sort the speed of your input after recording or search if your mouse have been to a place, please choose true.\n");
        fprintf(cfg,"If you chose true, you should enter a position (x,y) to search\n");
        fprintf(cfg,"The output file would be at statistic\\output.txt\n");

        fclose(cfg);
        return;
    }
    char state[10];
    fscanf(cfg,"%s",state);

    //don't want to statistic
    if(strcmp(state,"false")==0 || strcmp(state,"true")!=0)  //false or not true -> dont output
    {
        fclose(cfg);
        return;
    }

    //wants to statistic
    //read in what to search
    int wantX,wantY;
    fscanf(cfg,"%d%d",&wantX,&wantY);
    fclose(cfg);

    FILE *output=fopen("statistic\\output.txt","w");

    //use the compressed file
    strcat(fName,"C");
    FILE *input=fopen(fName,"r");

    int *speed;
    int size=0;
    speed=operateSearchAndBuildArray(input,output,wantX,wantY,size);
    if(speed==nullptr)//memory shortage
    {
        fclose(input);
        fclose(output);
        return;
    }
    if(mergeSort(speed,0,size-1,size)==-1)
    {
        fprintf(output,"ERROR: Memory Shortage\n錯誤 : 記憶體不足\n (SORT)");
        free(speed);
        fclose(input);
        fclose(output);
        return;
    }
    for(int i=0;i<size;i++)
    {
        fprintf(output,"%d\n",speed[i]);
    }

    free(speed);
    fclose(input);
    fclose(output);
}
