/*************************************************
* Unlock a previously locked region of memory    *
*************************************************/
void unlock_mem(void* ptr, u32bit bytes)
   {
   VirtualUnlock(ptr, bytes);
   }