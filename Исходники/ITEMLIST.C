void print_list()
  {
  int i;
  TITEM *t;

  if (!pagelen) print_head();
  if (!grp_sort)
     {
     for(i=0,t=itlist;i<item_count;i++,t++)
        {
        endpage(i);
        print_polozka(i,t);
        }
     }
  else
     {
     TITEM *list;
     int *nums;
     list=(TITEM *)malloc(sizeof(TITEM)*item_count);
     nums=(int *)malloc(sizeof(int)*item_count);
     counting_sort(itlist,list,item_count,nums);
     for(i=0,t=list;i<item_count;i++,t++)
        {
        endpage(i);
        print_polozka(nums[i],t);
        }
     free(list);
     free(nums);
     }
  }