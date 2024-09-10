/**
 *  Create a new State machine type.
 *
 *  API to create a new State macine Type. Maximum states in the
 *  state machine is passed in the parameter. Each state is 
 *  identified by a state id (index) and captures the transition
 *  table at each table.
 *                                                                        
 *  @param maxStates maximum states in State Machine 
 *  @param sm        [out] handle to the newly created state machine type
 *
 *  @returns 
 *    CL_OK on CL_OK <br/>
 *    CL_SM_RC(CL_ERR_NO_MEMORY) on memory allocation FAILURE <br/>
 *    CL_SM_RC(CL_ERR_NULL_POINTER) on invalid/null state machine handle <br/>
 *
 *  @see #clSmTypeDelete
 */
ClRcT
clSmTypeCreate(ClUint16T maxStates,
             ClSmTemplatePtrT* sm
             )
{
  ClRcT ret = CL_OK;
  int sz = 0;

  CL_FUNC_ENTER();
  CL_ASSERT(sm);  

  CL_DEBUG_PRINT(CL_DEBUG_TRACE, ("Create State Machine Type [%d]", maxStates));

  if(sm && (maxStates > 0)) {
    /* allocate the states and assign to top */
    *sm = (ClSmTemplatePtrT) mALLOC(sizeof(ClSmTemplateT));
    if(*sm!=0) 
      {
        sz = sizeof(ClSmStatePtrT)*(int)maxStates;
        /* allocate space to hold maxStates handles  */
        (*sm)->top = (ClSmStatePtrT*) mALLOC((size_t)sz);
        if((*sm)->top) 
          {
            (*sm)->maxStates = maxStates;
            (*sm)->objects = 0;
            /* Introduced a semaphore for handling concurrent
             * SM Instance creation/deletion
             */
            ret = clOsalMutexCreate( &((*sm)->sem));
            if (CL_OK != ret)
            {
                mFREE((*sm)->top);
                mFREE(*sm);
                ret = SM_ERR_NO_SEMA;
            }
            else
            {
                /* 
                 * default initial state to first state
                 */
                (*sm)->init = (*sm)->top[0];
                (*sm)->type = SIMPLE_STATE_MACHINE;
#ifdef DEBUG
                (*sm)->name[0] = 0;
#endif
            }
          }
        else
          {
            mFREE(*sm);
          }
      }
    if(!(*sm) || !(*sm)->top)
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