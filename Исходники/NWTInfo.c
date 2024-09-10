ThreadContext* fnAddThreadCtx(long lTLSIndex, void *t)
{
        ThreadContext* tip = NULL;
        ThreadContext* temp = NULL;

        if (g_tCtxSem)
        {
                #ifdef MPK_ON
                        kSemaphoreWait(g_tCtxSem);
                #else
                        WaitOnLocalSemaphore(g_tCtxSem);
                #endif	//MPK_ON
        }

        // add a new one to the beginning of the list
        //
        tip = (ThreadContext *) malloc(sizeof(ThreadContext));
        if (tip == NULL)
        {  
                if (g_tCtxSem)
                {
                        #ifdef MPK_ON
                                kSemaphoreSignal(g_tCtxSem);
                        #else
                                SignalLocalSemaphore(g_tCtxSem);
                        #endif	//MPK_ON
                }
                return NULL;
        }

        #ifdef MPK_ON
                lTLSIndex = labs(kCurrentThread());
        #else
                lTLSIndex = GetThreadID();
        #endif	//MPK_ON

        tip->next            =  NULL;
        tip->tid             =  lTLSIndex;
        tip->tInfo			 =  t;

        if(g_ThreadCtx==NULL) {
                g_ThreadCtx = tip;
        } else {
                int count=0;
                //Traverse to the end
                temp = g_ThreadCtx;
                while(temp->next != NULL)
                {
                        temp = temp->next;
                        count++;
                }
                temp->next = tip;
        }

        if (g_tCtxSem)
        {
                #ifdef MPK_ON
                        kSemaphoreSignal(g_tCtxSem);
                #else
                        SignalLocalSemaphore(g_tCtxSem);
                #endif	//MPK_ON
        }
        return tip;
}