void *Clear_realloc(void *OldPtr,size_t OldSize,size_t NewSize)

{
void *NewPtr ;

NewPtr = REALLOC(OldPtr,NewSize) ;

if (!NewPtr)
  {
  printf("ERROR - No more memory\n") ;
/*  werror(E_OUT_OF_MEM,__FILE__,NewSize);*/
  exit (1);
  }

if (NewPtr)
  if (NewSize > OldSize)
    memset((char *) NewPtr + OldSize,0x00,NewSize - OldSize) ;

return NewPtr ;
}