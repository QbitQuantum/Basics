/*
** Send extended string to socket (dynamic webpages).
**
** IN:
**      HTTPSRV_STRUCT         *server - server structure.
**      HTTPSRV_SESSION_STRUCT *session - session for sending.
**      char                   *str - string to send.
**      uint_32                length - length of source string.
**
** OUT:
**      none
**
** Return Value:
**      int - number of bytes processed.
*/
static _mqx_int httpsrv_sendextstr(HTTPSRV_STRUCT *server, HTTPSRV_SESSION_STRUCT *session, char *str, uint_32 length)
{
    char *src;
    int len, res;
    int add = 0;
    char fname[HTTPSRVCFG_MAX_SCRIPT_LN + 1];
    uint_32 old_data = session->buffer.offset;
        
    src = str;
    fname[0] = 0;
    
    if (session->response.script_token)
    {
        // script token found
        len = (int)strcspn(src, " ;%<>\r\n\t");

        if (len > 1 && len < HTTPSRVCFG_MAX_SCRIPT_LN)
        {
            HTTPSRV_SCRIPT_MSG* msg_ptr;

            snprintf(fname, len+1, "%s", src);
            /* Form up message for handler task and send it */
            msg_ptr = _msg_alloc(server->script_msg_pool);
            if (msg_ptr != NULL)
            {
                msg_ptr->header.TARGET_QID = server->script_msgq;
                msg_ptr->header.SOURCE_QID = server->script_msgq;
                msg_ptr->header.SIZE = sizeof(HTTPSRV_SCRIPT_MSG);
                msg_ptr->session = session;
                msg_ptr->type = HTTPSRV_SSI_CALLBACK;
                msg_ptr->name = fname;
                msg_ptr->ses_tid = _task_get_id();
                _msgq_send(msg_ptr);
                /* wait until SSI is processed */
                _task_block();
            }
        }

        if (src[len] == '%' && src[len + 1] == '>')
        {
            session->response.script_token = 0;
            len += 1;
        }
        len++;
    }
    else
    {
        for (len = 0; *src && len < length; src++, len++)
        {
            if (src[0] == '<' && src[1] == '%')
            {
                session->response.script_token = 1;
                src += 2;
                add = 2;
                break;
            }
        }
        res = send(session->sock, str, len, 0);
        session->buffer.offset = 0;
        _mem_zero(session->buffer.data, (HTTPSRVCFG_SES_BUFFER_SIZE & PSP_MEMORY_ALIGNMENT_MASK));
        if (res < 0)
        {
            session->response.script_token = 0;
            res = errno;

            if (res != EAGAIN)
            {
                len = 0;
            }  
        }
        else if (len != res)
        {
            session->response.script_token = 0;
        }
    }
    return ((len+add)-old_data);
}