void QuickSort(SqList *L)
{
    int i,compare,change;
    Qsort(L,1,L->len);
    printf("\n-----快速排序后序列-----\n");
    for(i=1;i<=L->len;i++)
    printf("%d  ",L->r[i].key);
    printf("\n");
    printf("快速排序后比较次数为:%d\n",compare);
    printf("快速排序后移动次数为:%d\n",change*3);
}