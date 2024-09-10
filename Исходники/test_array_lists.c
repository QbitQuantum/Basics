void test_concat_append_add_union_intersection_difference(void)
{     
     List list1 = list_random(MAX_LIST_SIZE, ELEMENT_MAX_VALUE);
     list_sort_by_item(&list1);
     list_unique(&list1);
     printf("Original List 1 ::: ");
     list_print(&list1);

     List list2 = list_random(MAX_LIST_SIZE, ELEMENT_MAX_VALUE);
     list_sort_by_item(&list2);
     list_unique(&list2);
     printf("%sOriginal List 2 ::: ", brown);
     list_print(&list2);

     List concat = list_concat(&list1, &list2);
     printf("%sConcatenation List ::: ", cyan);
     list_print(&concat);

     List append = list_duplicate(&list1);
     list_append(&append, &list2);
     printf("%sList 1 appended to list 2 ::: ", magenta);
     list_print(&append);
     
     List add = list_duplicate(&list1);
     list_add(&add, &list2);
     printf("%sList 1 added to list 2 ::: ", green);
     list_print(&add);

     List union_list = list_union(&list1, &list2);	
     printf("%sList Union ::: ", blue);
     list_print(&union_list);

     List intersection_list = list_intersection(&list1, &list2);
     printf("%sList Intersection ::: ", red);
     list_print(&intersection_list);

     List difference_list = list_difference(&list1, &list2);
     printf("%sDifference List ::: ", cyan);
     list_print(&difference_list);

     uint union_size = list_union_size(&list1, &list2);
     printf("%sList Union Size = %d\n", brown, union_size);

     uint intersection_size = list_intersection_size(&list1, &list2);
     printf("%sList Intersection Size = %d\n", black, intersection_size);

     uint difference_size = list_difference_size(&list1, &list2);
     printf("%sList Difference Size = %d\n", black, difference_size);
     
     printf("%s",none);

}