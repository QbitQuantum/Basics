int nx_eventhandler(NXHANDLE handle)
{
  FAR struct nxfe_conn_s *conn = (FAR struct nxfe_conn_s *)handle;
  struct nxsvrmsg_s      *msg;
  struct nxbe_window_s   *wnd;
  char                    buffer[NX_MXCLIMSGLEN];
  int                     nbytes;

  /* Get the next message from our incoming message queue */

  do
    {
      nbytes = mq_receive(conn->crdmq, buffer, NX_MXCLIMSGLEN, 0);
      if (nbytes < 0)
        {
          /* EINTR is not an error.  The wait was interrupted by a signal and
           * we just need to try reading again.
           */

          if (errno != EINTR)
            {
              if (errno == EAGAIN)
                {
                  /* EAGAIN is not an error.  It occurs because the MQ is opened with
                   * O_NONBLOCK and there is no message available now.
                   */

                  return OK;
                }
              else
                {
                  gdbg("mq_receive failed: %d\n", errno);
                  return ERROR;
                }
            }
        }
    }
  while (nbytes < 0);

  DEBUGASSERT(nbytes >= sizeof(struct nxclimsg_s));

  /* Dispatch the message appropriately */

  msg = (struct nxsvrmsg_s *)buffer;
  gvdbg("Received msgid=%d\n", msg->msgid);
  switch (msg->msgid)
    {
    case NX_CLIMSG_CONNECTED:
      nx_connected(conn);
      break;

    case NX_CLIMSG_DISCONNECTED:
      nx_disconnected(conn);
      set_errno(EHOSTDOWN);
      return ERROR;

    case NX_CLIMSG_REDRAW:
      {
        FAR struct nxclimsg_redraw_s *redraw = (FAR struct nxclimsg_redraw_s *)buffer;
        wnd = redraw->wnd;
        DEBUGASSERT(wnd);
        if (wnd->cb->redraw)
          {
            wnd->cb->redraw((NXWINDOW)wnd, &redraw->rect, redraw->more, wnd->arg);
          }
      }
      break;

    case NX_CLIMSG_NEWPOSITION:
      {
        FAR struct nxclimsg_newposition_s *postn = (FAR struct nxclimsg_newposition_s *)buffer;
        wnd = postn->wnd;
        DEBUGASSERT(wnd);
        if (wnd->cb->position)
          {
            wnd->cb->position((NXWINDOW)wnd, &postn->size, &postn->pos, &postn->bounds, wnd->arg);
          }
      }
      break;

#ifdef CONFIG_NX_XYINPUT
    case NX_CLIMSG_MOUSEIN:
      {
        FAR struct nxclimsg_mousein_s *mouse = (FAR struct nxclimsg_mousein_s *)buffer;
        wnd = mouse->wnd;
        DEBUGASSERT(wnd);
        if (wnd->cb->mousein)
          {
            wnd->cb->mousein((NXWINDOW)wnd, &mouse->pos, mouse->buttons, wnd->arg);
          }
        }
      break;
#endif

#ifdef CONFIG_NX_KBD
    case NX_CLIMSG_KBDIN:
      {
        FAR struct nxclimsg_kbdin_s *kbd = (FAR struct nxclimsg_kbdin_s *)buffer;
        wnd = kbd->wnd;
        DEBUGASSERT(wnd);
        if (wnd->cb->kbdin)
          {
            wnd->cb->kbdin((NXWINDOW)wnd, kbd->nch, kbd->ch, wnd->arg);
          }
        }
      break;
#endif

    case NX_CLIMSG_BLOCKED:
      {
        FAR struct nxclimsg_blocked_s *blocked = (FAR struct nxclimsg_blocked_s *)buffer;
        wnd = blocked->wnd;
        DEBUGASSERT(wnd);
        if (wnd->cb->blocked)
          {
            wnd->cb->blocked((NXWINDOW)wnd, wnd->arg, blocked->arg);
          }
        }
      break;

    default:
      gdbg("Unrecognized message opcode: %d\n", ((FAR struct nxsvrmsg_s *)buffer)->msgid);
      break;
    }

  return OK;
}