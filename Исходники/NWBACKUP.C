/* Returns non-zero value if heap is corrupted. Declare in the main program,
permit any other module to use it. Todo- place in a "general" functions 
source file and include only front end header. */
int check_heap() {
  int rc = 0;
  
  #ifdef __DOS__
  switch(_heapchk()) {
  case _HEAPOK:
    printf("OK - heap is good\n");
    break;
  case _HEAPEMPTY:
    printf("OK - heap is empty\n");
    break;
  case _HEAPBADBEGIN:
    printf("ERROR - heap is damaged\n");
    rc = -1;
    break;
  case _HEAPBADNODE:
    printf("ERROR - bad node in heap\n");
    rc = -1;
    break;
  }
  #endif
  return rc;
}