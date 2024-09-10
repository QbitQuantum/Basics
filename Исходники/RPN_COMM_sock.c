/* obtain own host's IPV4 address 
*/
static int get_own_ip_address()  /*   %ENTRY%   */
{
     char buf[1024];
     if(GetHostName(buf,sizeof buf)){
       fprintf(stderr,"Can't find hostname\n");
       return(-1);
       }
     return get_ip_address(buf);

}