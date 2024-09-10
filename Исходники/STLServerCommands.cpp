/**********************************************************************************************
    errorType STLServerCommandSetFrequency::Read(const wxString &m_device)
;will have already read the Socket command type and the command id
A polymorphic Read()
We take a sock as a parameter even though this code has access to the sock
This is because it is called from a base class and some of the polymorphic
classes derived from the base will not have a sock. This overrides that Read(sock)
***********************************************************************************************/
errorType STLServerCommandSetFrequencyXXX::Read(wxSocketBase &sock)
{
errorType rv;
wxUint16 f;

    sock.SetFlags(wxSOCKET_WAITALL);
	rv=ReadFixedFields(sock);		//reads qflag, at_tick
	if(rv)
		return rv;


//-----Read the data, a wxUint16 in this instance ----

    sock.Read(&f,sizeof(f));   //Read the str
    if(sock.Error())
        return(errFail);
	AppendToReadFromSocketString(f);
	SetFrequency(f);
	FillGSIRecord();

    SetReadFlag(true);
    return errNone;
}