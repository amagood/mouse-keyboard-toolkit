#include <stdlib.h>
int merge(int *arr,int low,int high,int mid,int size)
{
	int i,j,k;   //k is the control for tmp  and i,j is for left and right
	int *tmp=(int *)calloc(sizeof(int),size);
    if(tmp==nullptr)
    {
        return -1;
    }
	//initialization
	i=low;
	k=0;
	j=mid+1;


	while(i<=mid&&j<=high)
	{
		if(arr[i]<arr[j])   //let tmp be the smaller one
		{
			tmp[k]=arr[i];
			i++;
			k++;
		}
		else
		{
			tmp[k]=arr[j];
			j++;
			k++;
		}
	}//while(i<=mid&&j<=high)

    //process the lefts   it can either be i or j 'cause the upper loop breaks only when one side is finished
	while(i<=mid)
	{
		tmp[k]=arr[i];
		i++;
		k++;
	}//while(i<=mid)

	//process right
	while(j<=high)
	{
		tmp[k]=arr[j];
		j++;
		k++;
	}//while(j<=high)

	//copy back to the original array
	for(i=low,j=0;i<=high;i++,j++)
	{
		arr[i]=tmp[j];
	}//for (i=low,j=0;i<=high;i++,j++)

	//deallocate
	free(tmp);
	return 0;
}

int mergeSort(int *arr,int low,int high,int size)
{
	if(low<high)//continue doing recursive
	{
		int mid=(low+high)/2;


		//disassembla the big array into small arrays
		if(mergeSort(arr,low,mid,size)==-1) //left recursion
        {
            return -1;
        }
        if(mergeSort(arr,mid+1,high,size)==-1)//right recursion
        {
            return -1;
        }

		//end recursion, start putting small arrays togetheer
		if(merge(arr,low,high,mid,size)==-1)//sorting
        {
            return -1;
        }
        return 0;
	}//if(low<high)
}
