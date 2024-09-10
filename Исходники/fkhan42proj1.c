int main()
{
    int test;
    
    int terminal=-999;//this is for input text, so the loop knows when to stop

    int size=100;//Initial size
    int i=0;

    int *Data=Create(size);
    
    scanf("%d",&Data[i]);//Read in our initialize variable for our array
    //printf("i:%d and val:%d\n",i,Data[i]);
    i++;
    
    //????Even without increasing the allocated space the array was not Seg faulting
    
    while (Data[i-1]!=terminal)//This looks at the previous posi
    {
        scanf("%d",&Data[i]);
        //printf("i:%d and val:%d\n",i,Data[i]);
        i++;
        if (i==size)//this counter counts up size malloced for array, if true goes into function
        {
            size=size*2;
            Data=Inc_Cap(Data,size);
        }
    }
    printf("\nReading in Data Complete\n");
    size=i-1;//the get rid of the -999 in the array because we dont want that sorted
   
    //printf("Test_shot\n");
    
    int *lsearch_numComp_P;//This is for number of comparisons because we want to return to values from functions
    int *bsearch_numComp_P;
    
    int lsearch_numComp=0;
    int bsearch_numComp=0;
    
    lsearch_numComp_P=&lsearch_numComp;//Take the address of the right because we need to point to that space
    bsearch_numComp_P=&bsearch_numComp;
    
    
    int* toArray=Create(size);//We are mallocing because to we can free it later
    
    arrayCopy(Data,toArray,size);//self- explanatory
    
    sort(Data,size);
    
    i=0;
   
    int target;//This is the value that need to be found for binary and linear search
    scanf("%d",&target);
     //printf("Target Value: %d\n",target);
    while (target!=terminal)
    {
        
        //scanf("%d",&target);
        //printf("Target Value: %d\n",target);
    
        int Print_Lsearch=lsearch(toArray,size,target,lsearch_numComp_P);//reason for this becaue we are sending the index location
    
        if (Print_Lsearch==-1)//because of the above statement is the reason for this "if" statement
        {//we dont want to run the same function twice becasue it would be unneccassay
            printf("Value not found in Linear search\n");
        }
        else
            printf("Target Value:%d found with Linear search in Array position %d with %d comparisons\n",target,Print_Lsearch,*lsearch_numComp_P);
    
    
        int Print_Bsearch=Bsearch(Data,size,target,bsearch_numComp_P);
    
        if (Print_Bsearch==-1)
        {  //Same sort of logic as lsearch explaniation for "if"
            printf("Value not found in Binary search\n");
        }
        else
            printf("Target Value:%d found with Binary search in Array position %d with %d comparisons\n",target,Print_Bsearch,*bsearch_numComp_P);
        
        lsearch_numComp=0;
        bsearch_numComp=0;
        scanf("%d",&target);
    
    }
    
    free_space(Data);
    free_space(toArray);
    
    return 0;
}