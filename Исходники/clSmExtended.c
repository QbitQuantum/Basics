/**
 *  Creates a new Extended State machine Instance.
 *
 *  This API creates a new Extended State macine Instance of given
 *  state machine type.  The extended state machine shall include
 *  all the regular state machine instance functionalities, plus
 *  additional event queue, history, and lock capabilities.
 *                                                                        
 *  @param sm       State machine type 
 *  @param instance [out] newly created extended state machine instance
 *
 *  @returns 
 *    CL_OK on CL_OK <br/>
 *    CL_SM_RC(CL_ERR_NO_MEMORY) on memory allocation FAILURE <br/>
 *    CL_SM_RC(CL_ERR_NULL_POINTER) on invalid/null sm / instance <br/>
 *
 *  @see #clEsmInstanceDelete
 */
ClRcT
clEsmInstanceCreate(ClSmTemplatePtrT sm, 
                  ClExSmInstancePtrT* instance
                  )
{
  ClRcT ret = CL_OK;

  CL_FUNC_ENTER();
  CL_ASSERT(instance);  
  CL_ASSERT(sm);  

  clLogTrace(ESM_LOG_AREA,ESM_LOG_CTX_CREATE,"Create Extended State Machine Instance");

  if(sm && instance) 
    {
      /* allocate the instance space */
      *instance = (ClExSmInstancePtrT) mALLOC(sizeof(ClExSmInstanceT));
      if(*instance!=0) 
        {
          memset(*instance, 0, sizeof(ClExSmInstanceT));
          /* call sm create here */
          ret = clSmInstanceCreate(sm, &(*instance)->fsm);
          if(ret == CL_OK)
            {
              ret = clOsalMutexCreate(&(*instance)->lock);
              if (CL_OK != ret)
              {
                  clSmInstanceDelete((*instance)->fsm);
                  mFREE(*instance);
                  ret = SM_ERR_NO_SEMA;
              }
              else
              {
              /* create queue and init */
              ret = SMQ_CREATE((*instance)->q);
              if(ret == CL_OK)
                {
                  /* init log buffer */
                  ESM_LOG_INIT((*instance)->log, ESM_LOG_ENTRIES);
                }
              if(!(*instance)->log.buffer || ret != CL_OK)
                {
                  /* delete the instance */
                  ret = clSmInstanceDelete((*instance)->fsm);
                  /* delete the mutex */
                  clOsalMutexDelete((*instance)->lock);
                  /* check if q init succeeded */
                  if(ret == CL_OK)
                    {
                      /* delete the queue */
                      clQueueDelete(&((*instance)->q));
                    }
                  /* free the instance */
                  mFREE(*instance);
                  ret = CL_SM_RC(CL_ERR_NO_MEMORY);
                }
              }
            }
          
        } else 
          {
            ret = CL_SM_RC(CL_ERR_NO_MEMORY);
          }
    } else 
      {
        ret = CL_SM_RC(CL_ERR_NULL_POINTER);
      }
  
  CL_FUNC_EXIT();
  return ret;
}