/* Display info about an individual Erlang process */
void
print_process_info(int to, void *to_arg, Process *p)
{
    time_t approx_started;
    int garbing = 0;
    int running = 0;
    struct saved_calls *scb;
    erts_aint32_t state;

    /* display the PID */
    erts_print(to, to_arg, "=proc:%T\n", p->common.id);

    /* Display the state */
    erts_print(to, to_arg, "State: ");

    state = erts_smp_atomic32_read_acqb(&p->state);
    erts_dump_process_state(to, to_arg, state);
    if (state & ERTS_PSFLG_GC) {
        garbing = 1;
        running = 1;
    } else if (state & (ERTS_PSFLG_RUNNING
			| ERTS_PSFLG_DIRTY_RUNNING))
        running = 1;

    /*
     * If the process is registered as a global process, display the
     * registered name
     */
    if (p->common.u.alive.reg)
	erts_print(to, to_arg, "Name: %T\n", p->common.u.alive.reg->name);

    /*
     * Display the initial function name
     */
    erts_print(to, to_arg, "Spawned as: %T:%T/%bpu\n",
	       p->u.initial[INITIAL_MOD],
	       p->u.initial[INITIAL_FUN],
	       p->u.initial[INITIAL_ARI]);
    
    if (p->current != NULL) {
	if (running) {
	    erts_print(to, to_arg, "Last scheduled in for: ");
	} else {
	    erts_print(to, to_arg, "Current call: ");
	}
	erts_print(to, to_arg, "%T:%T/%bpu\n",
		   p->current[0],
		   p->current[1],
		   p->current[2]);
    }

    erts_print(to, to_arg, "Spawned by: %T\n", p->parent);
    approx_started = (time_t) p->approx_started;
    erts_print(to, to_arg, "Started: %s", ctime(&approx_started));
    ERTS_SMP_MSGQ_MV_INQ2PRIVQ(p);
    erts_print(to, to_arg, "Message queue length: %d\n", p->msg.len);

    /* display the message queue only if there is anything in it */
    if (!ERTS_IS_CRASH_DUMPING && p->msg.first != NULL && !garbing) {
	ErtsMessage* mp;
	erts_print(to, to_arg, "Message queue: [");
	for (mp = p->msg.first; mp; mp = mp->next)
	    erts_print(to, to_arg, mp->next ? "%T," : "%T", ERL_MESSAGE_TERM(mp));
	erts_print(to, to_arg, "]\n");
    }

    {
       int frags = 0;
       ErlHeapFragment *m = p->mbuf;
       while (m != NULL) {
	   frags++;
	   m = m->next;
       }
       erts_print(to, to_arg, "Number of heap fragments: %d\n", frags);
    }
    erts_print(to, to_arg, "Heap fragment data: %beu\n", MBUF_SIZE(p));

    scb = ERTS_PROC_GET_SAVED_CALLS_BUF(p);
    if (scb) {
       int i, j;

       erts_print(to, to_arg, "Last calls:");
       for (i = 0; i < scb->n; i++) {
	     erts_print(to, to_arg, " ");
	     j = scb->cur - i - 1;
	     if (j < 0)
		j += scb->len;
	     if (scb->ct[j] == &exp_send)
		erts_print(to, to_arg, "send");
	     else if (scb->ct[j] == &exp_receive)
		erts_print(to, to_arg, "'receive'");
	     else if (scb->ct[j] == &exp_timeout)
		   erts_print(to, to_arg, "timeout");
	     else
		 erts_print(to, to_arg, "%T:%T/%bpu\n",
			    scb->ct[j]->code[0],
			    scb->ct[j]->code[1],
			    scb->ct[j]->code[2]);
       }
       erts_print(to, to_arg, "\n");
    }

    /* display the links only if there are any*/
    if (ERTS_P_LINKS(p) || ERTS_P_MONITORS(p)) {
	PrintMonitorContext context = {1,to}; 
	erts_print(to, to_arg,"Link list: [");
	erts_doforall_links(ERTS_P_LINKS(p), &doit_print_link, &context);	
	erts_doforall_monitors(ERTS_P_MONITORS(p), &doit_print_monitor, &context);
	erts_print(to, to_arg,"]\n");
    }

    if (!ERTS_IS_CRASH_DUMPING) {

	/* and the dictionary */
	if (p->dictionary != NULL && !garbing) {
	    erts_print(to, to_arg, "Dictionary: ");
	    erts_dictionary_dump(to, to_arg, p->dictionary);
	    erts_print(to, to_arg, "\n");
	}
    }
    
    /* print the number of reductions etc */
    erts_print(to, to_arg, "Reductions: %beu\n", p->reds);

    erts_print(to, to_arg, "Stack+heap: %beu\n", p->heap_sz);
    erts_print(to, to_arg, "OldHeap: %bpu\n",
               (OLD_HEAP(p) == NULL) ? 0 : (OLD_HEND(p) - OLD_HEAP(p)) );
    erts_print(to, to_arg, "Heap unused: %bpu\n", (p->hend - p->htop));
    erts_print(to, to_arg, "OldHeap unused: %bpu\n",
	       (OLD_HEAP(p) == NULL) ? 0 : (OLD_HEND(p) - OLD_HTOP(p)) );
    erts_print(to, to_arg, "Memory: %beu\n", erts_process_memory(p, !0));

    if (garbing) {
	print_garb_info(to, to_arg, p);
    }
    
    if (ERTS_IS_CRASH_DUMPING) {
	erts_program_counter_info(to, to_arg, p);
    } else {
	erts_print(to, to_arg, "Stack dump:\n");
#ifdef ERTS_SMP
	if (!garbing)
#endif
	    erts_stack_dump(to, to_arg, p);
    }

    /* Display all states */
    erts_print(to, to_arg, "Internal State: ");
    erts_dump_extended_process_state(to, to_arg, state);
}