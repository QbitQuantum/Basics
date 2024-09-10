OWindow::~OWindow() 
{ 
 destroy(); 
#ifdef __IBMCPP__ 
   _heapmin();  // return all unused memory to OS/2
#endif
}