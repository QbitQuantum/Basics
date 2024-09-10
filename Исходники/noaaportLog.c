/**
 * Adds a variadic log-message to the message-list for the current thread.
 *
 * This function is thread-safe.
 *
 * @retval 0            Success
 * @retval EAGAIN       Failure due to the buffer being too small for the
 *                      message.  The buffer has been expanded and the client
 *                      should call this function again.
 * @retval EINVAL       There are insufficient arguments. Error message logged.
 * @retval EILSEQ       A wide-character code that doesn't correspond to a
 *                      valid character has been detected. Error message logged.
 * @retval ENOMEM       Out-of-memory. Error message logged.
 * @retval EOVERFLOW    The length of the message is greater than {INT_MAX}.
 *                      Error message logged.
 */
int nplVadd(
    const char* const   fmt,  /**< The message format or NULL for no message */
    va_list             args) /**< The arguments referenced by the format. */
{
    int                 status = 0; /* default success */

    if (NULL != fmt) {
        List*   list = getList();

        if (NULL != list) {
            Message*    msg = (NULL == list->last) ? list->first :
                list->last->next;

            status = 0;

            if (msg == NULL) {
                msg = (Message*)malloc(sizeof(Message));

                if (msg == NULL) {
                    status = errno;

                    lock();
                    serror("nplVadd(): malloc(%lu) failure",
                        (unsigned long)sizeof(Message));
                    unlock();
                }
                else {
                    char*   string = (char*)malloc(DEFAULT_STRING_SIZE);

                    if (NULL == string) {
                        status = errno;

                        lock();
                        serror("nplVadd(): malloc(%lu) failure",
                            (unsigned long)DEFAULT_STRING_SIZE);
                        unlock();
                    }
                    else {
                        msg->string = string;
                        msg->size = DEFAULT_STRING_SIZE;
                        msg->next = NULL;

                        if (NULL == list->first)
                            list->first = msg;  /* very first message */
                    }
                }
            }

            if (0 == status) {
                int nbytes = vsnprintf(msg->string, msg->size, fmt, args);

                if (0 > nbytes) {
                    status = errno;

                    lock();
                    serror("nplVadd(): vsnprintf() failure");
                    unlock();
                }
                else if (msg->size <= nbytes) {
                    /* The buffer is too small for the message */
                    size_t  size = nbytes + 1;
                    char*   string = (char*)malloc(size);

                    if (NULL == string) {
                        status = errno;

                        lock();
                        serror("nplVadd(): malloc(%lu) failure",
                            (unsigned long)size);
                        unlock();
                    }
                    else {
                        free(msg->string);

                        msg->string = string;
                        msg->size = size;
                        status = EAGAIN;
                    }
                }
                else {
                    if (NULL != list->last)
                        list->last->next = msg;

                    list->last = msg;
                }
            }                               /* have a message structure */
        }                                   /* message-list isn't NULL */
    }                                       /* arguments aren't NULL */

    return status;
}