int isdn_divert_icall(isdn_ctrl *ic)
{ int retval = 0;
  unsigned long flags;
  struct call_struc *cs = NULL; 
  struct deflect_struc *dv;
  char *p,*p1;
  u_char accept;

  /* first check the internal deflection table */
  for (dv = table_head; dv ; dv = dv->next )
   { /* scan table */
     if (((dv->rule.callopt == 1) && (ic->command == ISDN_STAT_ICALLW)) ||
         ((dv->rule.callopt == 2) && (ic->command == ISDN_STAT_ICALL)))
       continue; /* call option check */  
     if (!(dv->rule.drvid & (1L << ic->driver))) 
       continue; /* driver not matching */ 
     if ((dv->rule.si1) && (dv->rule.si1 != ic->parm.setup.si1)) 
       continue; /* si1 not matching */
     if ((dv->rule.si2) && (dv->rule.si2 != ic->parm.setup.si2)) 
       continue; /* si2 not matching */

     p = dv->rule.my_msn;
     p1 = ic->parm.setup.eazmsn;
     accept = 0;
     while (*p)
      { /* complete compare */
        if (*p == '-')
	  { accept = 1; /* call accepted */
            break;
          }
        if (*p++ != *p1++) 
          break; /* not accepted */
        if ((!*p) && (!*p1))
          accept = 1;
      } /* complete compare */
     if (!accept) continue; /* not accepted */
 
     if ((strcmp(dv->rule.caller,"0")) || (ic->parm.setup.phone[0]))
      { p = dv->rule.caller;
        p1 = ic->parm.setup.phone;
        accept = 0;
        while (*p)
	 { /* complete compare */
           if (*p == '-')
	    { accept = 1; /* call accepted */
              break;
            }
           if (*p++ != *p1++) 
             break; /* not accepted */
           if ((!*p) && (!*p1))
             accept = 1;
         } /* complete compare */
        if (!accept) continue; /* not accepted */
      }  

     switch (dv->rule.action)
       { case DEFLECT_IGNORE:
           return(0);
           break;

         case DEFLECT_ALERT:
         case DEFLECT_PROCEED:
         case DEFLECT_REPORT:
         case DEFLECT_REJECT:
           if (dv->rule.action == DEFLECT_PROCEED)
	    if ((!if_used) || ((!extern_wait_max) && (!dv->rule.waittime))) 
              return(0); /* no external deflection needed */  
           if (!(cs = (struct call_struc *) kmalloc(sizeof(struct call_struc), GFP_ATOMIC))) 
             return(0); /* no memory */
           init_timer(&cs->timer);
           cs->info[0] = '\0';
           cs->timer.function = deflect_timer_expire;
           cs->timer.data = (ulong) cs; /* pointer to own structure */
           
           cs->ics = *ic; /* copy incoming data */
           if (!cs->ics.parm.setup.phone[0]) strcpy(cs->ics.parm.setup.phone,"0");
           if (!cs->ics.parm.setup.eazmsn[0]) strcpy(cs->ics.parm.setup.eazmsn,"0");
	   cs->ics.parm.setup.screen = dv->rule.screen;  
           if (dv->rule.waittime) 
             cs->timer.expires = jiffies + (HZ * dv->rule.waittime);
           else
            if (dv->rule.action == DEFLECT_PROCEED)
              cs->timer.expires = jiffies + (HZ * extern_wait_max); 
            else  
              cs->timer.expires = 0;
           cs->akt_state = dv->rule.action;                
           save_flags(flags);
           cli();
           cs->divert_id = next_id++; /* new sequence number */
           restore_flags(flags);
           cs->prev = NULL;
           if (cs->akt_state == DEFLECT_ALERT)
             { strcpy(cs->deflect_dest,dv->rule.to_nr);
               if (!cs->timer.expires)
		 { strcpy(ic->parm.setup.eazmsn,"Testtext direct");
                   ic->parm.setup.screen = dv->rule.screen;
                   strcpy(ic->parm.setup.phone,dv->rule.to_nr);
                   cs->akt_state = DEFLECT_AUTODEL; /* delete after timeout */
                   cs->timer.expires = jiffies + (HZ * AUTODEL_TIME);
                   retval = 5; 
                 }
               else
                 retval = 1; /* alerting */                 
             }
           else
             { cs->deflect_dest[0] = '\0';
	       retval = 4; /* only proceed */
             }  
           sprintf(cs->info,"%d 0x%lx %s %s %s %s 0x%x 0x%x %d %d %s\n",
                   cs->akt_state,
                   cs->divert_id,
                   divert_if.drv_to_name(cs->ics.driver),
                   (ic->command == ISDN_STAT_ICALLW) ? "1":"0", 
                   cs->ics.parm.setup.phone, 
                   cs->ics.parm.setup.eazmsn,
                   cs->ics.parm.setup.si1,
                   cs->ics.parm.setup.si2,
                   cs->ics.parm.setup.screen,
                   dv->rule.waittime,
                   cs->deflect_dest);
           if ((dv->rule.action == DEFLECT_REPORT) ||
               (dv->rule.action == DEFLECT_REJECT))
	    { put_info_buffer(cs->info);
	      kfree(cs); /* remove */
              return((dv->rule.action == DEFLECT_REPORT) ? 0:2); /* nothing to do */ 
            }              
           break;
  
         default:
           return(0); /* ignore call */
           break;
       } /* switch action */    
     break; 
   } /* scan_table */

  if (cs) 
   { cs->prev = NULL;
     save_flags(flags);
     cli();
     cs->next = divert_head;
     divert_head = cs; 
     if (cs->timer.expires) add_timer(&cs->timer);
     restore_flags(flags);

     put_info_buffer(cs->info); 
     return(retval);
   }
  else
     return(0);
} /* isdn_divert_icall */