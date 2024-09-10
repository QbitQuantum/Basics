void grab_all_available_memory(int use_ems)
{/*
  unsigned long int precore = coreleft();
  */
  unsigned long int precore = 400000;
  unsigned long int core_left = precore /* - DAVE_FUDGE_FACTOR */;
  unsigned long int bytes = (unsigned int) (core_left);
  void *total_memory_pointer;


#ifdef MEM_DEBUG
  int result=0;
  struct heapinfo test;
/*	unsigned *_seg; */

  printf("Found: %lu\n",precore);
#endif

#ifdef MEM_DEBUG
  test.ptr=NULL;
  do
   {
	 result=heapwalk(&test);
	 printf("FarHeapSize %lu  Used: %d Ptr:%lX Res:%d\n",test.size,test.in_use,test.ptr,result);
   } while ((result!=5) && (result!=1));
   printf("Result: %d\n",result);

/*	printf("Total Memory (_dos_allocmem) Rtn: %u  SegPtr: %u\n",_dos_allocmem(0xFFFFu,_seg),(unsigned int)*_seg); */
#endif

/*	total_memory_pointer = malloc((unsigned long int)core_left); */

  DosAllocMem(&total_memory_pointer,core_left,PAG_READ | PAG_WRITE | PAG_COMMIT);

/* (char *)*total_memory_pointer=0; */

  printf("Allocated memory starting at %p\n",total_memory_pointer);

#ifdef MEM_DEBUG
  printf("Allocated: %lX\n",total_memory_pointer);

  test.ptr=NULL;
  do
   {
	 result=heapwalk(&test);
	 printf("FarHeapSize %lu  Used: %d Ptr:%lX Res:%d\n",test.size,test.in_use,test.ptr,result);
   } while ((result!=5) && (result!=1));
   printf("Result: %d\n",result);
#endif

  if (!total_memory_pointer)
  {
	printf("Could not allocate memory!\n");
	g_exit(1);
  }
  if (!tasking)
	{
	 printf("CoreLeft Begin: %ld asking for %ld \n",precore,core_left);
	 printf("We have [%ud] bytes\n",bytes);
	}
  mem_handles = 0;
  insert_memory_entry_at(0,(char *)total_memory_pointer,
					  -1,bytes,1,"EMPTY",1);

  sys_toggles.total_starting_memory=core_left;
/*	sys_toggles.total_dos_starting_memory=coreleft(); */


  use_ems=0;

#ifdef MEM_DEBUG
  g_exit(1);
#endif
}