/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * NAME : main 
 *
 * DESCRIPTION : space-commander main 
 *
 *-----------------------------------------------------------------------------*/
int main() 
{
    validate();
    set_new_handler(&out_of_memory_handler);

    commander = new Net2Com(Dcom_w_net_r, Dnet_w_com_r, 
                                                    Icom_w_net_r, Inet_w_com_r);

    if (!commander) {
        memset(log_buffer,0,MAX_BUFFER_SIZE);
        snprintf(log_buffer, MAX_BUFFER_SIZE, "[ERROR] %s:%s:%d Failed in Net2Com instanciation\n", 
                                                __FILE__, __func__, __LINE__);
        return EXIT_FAILURE; /* watch-puppy will take care of 
                              * restarting space-commander
                              */
    }

    Shakespeare::log(Shakespeare::NOTICE, LOGNAME, 
                                            "Waiting commands from ground...");

    while (true) 
    {
        memset(info_buffer, 0, sizeof(char) * NET2COM_MAX_INFO_BUFFER_SIZE);
        int bytes = commander->ReadFromInfoPipe(info_buffer, NET2COM_MAX_INFO_BUFFER_SIZE);

        if (bytes > 0) {
            perform(bytes);
        }

        sleep(COMMANER_SLEEP_TIME);
    }

    if (commander) {
        delete commander;
        commander = 0;
    }

    return 0;
}