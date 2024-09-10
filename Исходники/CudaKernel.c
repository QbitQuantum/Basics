__global__ void entry(int * handles, int * exceptions, int numBlocks, 
  int usingKernelTemplates){

  int loop_control = getThreadId();
  if(loop_control < numBlocks){
    int exception = 0; 
    int handle;
    if(usingKernelTemplates){
      handle = handles[0];
    } else {
      handle = handles[loop_control];
    }
    %%invoke_run%%(handle, &exception);  