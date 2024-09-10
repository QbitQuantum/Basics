/*  init_method1(): file method  */
static int init_method1(int dev_no)
{
  FHANDLE dev_handle;           /* device handle */
  int gen_status;               /* generic error codes returned to the application */  

  dev_handle = _fsOpen(pos_setup[dev_no].dev_type, OPEN_FLAGS );

  gen_status = error_map(_fsError());  /* get the generic error status */

  if (gen_status == NORMAL)
    update_table(1, dev_no, dev_handle, -1, -1, -1, -1);  /* update the POS Device table */    

  return gen_status;    
}