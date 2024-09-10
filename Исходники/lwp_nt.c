int LWP_InitializeProcessSupport(int priority, PROCESS *pid)
{
    PROCESS pcb;
    register int i;
    char* value;

    Debug(0, ("Entered LWP_InitializeProcessSupport"))
    if (lwp_init != NULL) return LWP_SUCCESS;

    if (priority >= MAX_PRIORITIES) return LWP_EBADPRI;

    pcb = (PROCESS)malloc(sizeof(*pcb));
    if (pcb == NULL)
	Abort_LWP("Insufficient Storage to Initialize LWP PCB");
    (void) memset((void*)pcb, 0, sizeof(*pcb));
    pcb->fiber = ConvertThreadToFiber(pcb);
    if (pcb == NULL) 
	Abort_LWP("Cannot convert main thread to LWP fiber");

    lwp_init = (struct lwp_ctl *) malloc(sizeof(struct lwp_ctl));
    if (lwp_init == NULL)
	Abort_LWP("Insufficient Storage to Initialize LWP CTL");
    (void) memset((void*)lwp_init, 0, sizeof(struct lwp_ctl));

    for (i=0; i<MAX_PRIORITIES; i++) {
	runnable[i].head = NULL;
	runnable[i].count = 0;
    }
    blocked.head = NULL;
    blocked.count = 0;

    LWPANCHOR.processcnt = 1;
    LWPANCHOR.outerpid = pcb;
    LWPANCHOR.outersp = NULL;


    Initialize_PCB(pcb, priority, 0, NULL, NULL,
		"Main Process [created by LWP]");   

    lwp_cpptr = pcb;
    Debug(10, ("Init: Insert 0x%p into runnable at priority %d\n", pcb, priority))
    insert(pcb, &runnable[priority]);

    if ( ( value = getenv("AFS_LWP_STACK_SIZE")) == NULL )
	lwp_MinStackSize = AFS_LWP_MINSTACKSIZE;	
    else
	lwp_MinStackSize = (AFS_LWP_MINSTACKSIZE>atoi(value)?
				AFS_LWP_MINSTACKSIZE : atoi(value));
   
    *pid = pcb;

    return LWP_SUCCESS;
}