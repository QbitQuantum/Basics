static Eina_Bool
_ecore_con_local_win32_client_add(void *data, Ecore_Win32_Handler *wh)
{
   Ecore_Con_Client *cl = NULL;
   Ecore_Con_Server *svr;
   Ecore_Win32_Handler *handler_read;
   Ecore_Win32_Handler *handler_peek;

   svr = (Ecore_Con_Server *)data;

   if (!svr->pipe)
     return ECORE_CALLBACK_CANCEL;

   if (svr->dead)
     return ECORE_CALLBACK_CANCEL;

   if (svr->delete_me)
     return ECORE_CALLBACK_CANCEL;

   if ((svr->client_limit >= 0) && (!svr->reject_excess_clients) &&
       (svr->client_count >= (unsigned int)svr->client_limit))
     return ECORE_CALLBACK_CANCEL;

   cl = calloc(1, sizeof(Ecore_Con_Client));
   if (!cl)
     {
        ERR("allocation failed");
        return ECORE_CALLBACK_CANCEL;
     }

   cl->host_server = svr;
   ECORE_MAGIC_SET(cl, ECORE_MAGIC_CON_CLIENT);

   cl->host_server->event_read = CreateEvent(NULL, TRUE, FALSE, NULL);
   if (!cl->host_server->event_read)
     {
        ERR("Can not create event read");
        goto free_cl;
     }

   handler_read = ecore_main_win32_handler_add(cl->host_server->event_read,
                                               _ecore_con_local_win32_server_read_client_handler,
                                               cl);
   if (!handler_read)
     {
        ERR("Can not create handler read");
        goto close_event_read;
     }

   cl->host_server->event_peek = CreateEvent(NULL, TRUE, FALSE, NULL);
   if (!cl->host_server->event_peek)
     {
        ERR("Can not create event peek");
        goto del_handler_read;
     }

   handler_peek = ecore_main_win32_handler_add(cl->host_server->event_peek,
                                               _ecore_con_local_win32_server_peek_client_handler,
                                               cl);
   if (!handler_peek)
     {
        ERR("Can not create handler peek");
        goto close_event_peek;
     }

   cl->host_server->read_stopped = EINA_TRUE;
   cl->host_server->thread_read = (HANDLE)_beginthreadex(NULL, 0, _ecore_con_local_win32_server_read_client_thread, cl, CREATE_SUSPENDED, NULL);
   if (!cl->host_server->thread_read)
     {
        ERR("Can not launch thread");
        goto del_handler_peek;
     }

   svr->clients = eina_list_append(svr->clients, cl);
   svr->client_count++;

   if (!cl->delete_me)
     ecore_con_event_client_add(cl);

   ecore_main_win32_handler_del(wh);

   ResumeThread(cl->host_server->thread_read);
   return ECORE_CALLBACK_DONE;

 del_handler_peek:
   ecore_main_win32_handler_del(handler_peek);
 close_event_peek:
   CloseHandle(cl->host_server->event_peek);
 del_handler_read:
   ecore_main_win32_handler_del(handler_read);
 close_event_read:
   CloseHandle(cl->host_server->event_read);
 free_cl:
   free(cl);

   return ECORE_CALLBACK_CANCEL;
}