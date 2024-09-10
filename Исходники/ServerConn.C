void ServerConn::send(string _sendStr)
{
    _outputBuffer += _sendStr;
    int len = _outputBuffer.size();	          // Check output buffer size

    if (len)                                      // Have something to send
    {
        int wrote = 0;
        try {
            wrote = (*_s)->write(_outputBuffer.data(),len); 
            // Write all possible
        }
        catch (const sockerr & e)
        {
            if (e.serrno()==ETIMEDOUT) return;
            if (e.serrno()==EPIPE) wrote = 0;   //keep going
            else {
                killConn();
                string s = "ConnectionError: Unspecified network write error, ";
                throw ConnectionError(s.c_str());
            }
        }
        catch (int partial) {
            wrote = partial;                      // keep going
        }
        if (wrote==len) {
            _outputBuffer.erase();		  // Sent it all, flush
        } 
        else 
	    if (wrote>0)                          // Partial write!
	    {	
            _outputBuffer.erase(0,wrote);     // Strip off what we shipped
	    } 
	    else // got an EPIPE or partial was negative?? 
	    {
            killConn();
            string s = "ConnectionResetError: Connection lost during network write!";
            throw ConnectionResetError(s.c_str());
	    }
    }
}