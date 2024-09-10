/**
    @brief
    Function Resolve the hostname to ip
*/
bool turbotrace::resolve_host(wxString host)
{
    //Get hostname as a char pointer
    char *target = strdup( (char*) host.ToAscii().data());

    log( _("Will now resolve : ") + wxString(target , wxConvUTF8) );

    //Is it just a simple IP
	if( inet_addr( target ) != INADDR_NONE)
	{
		dest_ip.s_addr = inet_addr( target );
		tlog(_("Valid IP provided"));
	}
	//Domain name , resolve it
	else
	{
		char *ip = iputils::hostname_to_ip( (char*) target );

		if(ip != NULL)
		{
			tlog( wxString(target , wxConvUTF8) + _(" resolved to ") + wxString(ip , wxConvUTF8));

			//Convert domain name to IP
			dest_ip.s_addr = inet_addr( ip );
		}
		else
		{
			tlog( _("Unable to resolve hostname : ") + wxString(target , wxConvUTF8) );
			return false;
		}
	}
	return true;
}