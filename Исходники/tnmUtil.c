char *
TnmGetIPPort(Tcl_Interp *interp, char *protocol, struct sockaddr_in *addr)
{
    struct servent *serv;

    if (strcmp(protocol, "udp") != 0 && strcmp(protocol, "tcp") != 0) {
	if (interp) {
	    Tcl_ResetResult(interp);
	    Tcl_AppendResult(interp, "unknown IP protocol \"", 
			     protocol, "\"", (char *) NULL);
	}
	return NULL;
    }

    serv = getservbyport(addr->sin_port, protocol);
    if (! serv) {
	char buffer[20];
	sprintf(buffer, "%d", ntohs(addr->sin_port));
	if (interp) {
	    Tcl_ResetResult(interp);
	    Tcl_AppendResult(interp, "unknown ", protocol, " port \"", 
			     buffer, "\"", (char *) NULL);
	}
	return NULL;
    }

    return serv->s_name;
}