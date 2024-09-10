/**
 * 	\brief	Free network ressources
 */
void net_exit(void)
{
#ifdef OS_WIN
    WSACleanup();
#endif
}