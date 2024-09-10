void Qsort(SqList *L,int low,int high)    /*Qsort() sub-function */
{  int pivotloc;
   if(low<high)                    /*长度大于1*/
   {  pivotloc=Partition(L,low,high);
      Qsort(L,low,pivotloc-1);
      Qsort(L,pivotloc+1,high);
   }
}