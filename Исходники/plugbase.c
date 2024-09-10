/****************************************************************************
 *
 * Function: GetUniqueName(char * iface)
 *
 * Purpose: To return a string that has a high probability of being unique
 *          for a given sensor.
 *
 * Arguments: char * iface - The network interface you are sniffing
 *
 * Returns: A char * -- its a static char * so you should not free it
 *
 ***************************************************************************/
char *GetUniqueName(char * iface)
{
	char * rptr;
#ifdef WIN32
		rptr = GetHostname(); 
#else
    rptr = GetIP(iface); 
    if(rptr == NULL)
    {
        rptr = GetHostname(); 
    }
#endif
    return rptr;
}    