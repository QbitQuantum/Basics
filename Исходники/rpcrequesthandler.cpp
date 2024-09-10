// ==========================================================================
// METHOD RPCRequestHandler::run
// ==========================================================================
int RPCRequestHandler::run (string &uri, string &postbody, value &inhdr,
                 		    string &out, value &outhdr, value &env,
                		    tcpsocket &s)
{
	try
	{
		DEBUG.storeFile ("RPCRequestHandler","postbody", postbody, "run");
		CORE->log (log::debug, "RPC", "handle: %S %!" %format (uri, inhdr));
		value indata;
		value res;
		string origin = "rpc";
		uid_t uid = 0;
		RPCHandler hdl (sdb);
	
		indata.fromjson (postbody);
		if (inhdr.exists ("X-OpenCORE-Origin"))
		{
			origin = inhdr["X-OpenCORE-Origin"];
		}
		
		CORE->log (log::debug, "RPC", "body: %!" %format (indata));
		
		// Set up credentials if available
		s.getcredentials();
		CORE->log (log::debug, "RPC", "credentials: %d %d %d", s.peer_uid,
														s.peer_gid, s.peer_pid);
		if (s.peer_pid == 0)
		{
			string peer_name = s.peer_name;
			if (peer_name == "127.0.0.1")
			{
				if (inhdr.exists ("X-Forwarded-For"))
				{
					peer_name = inhdr["X-Forwarded-For"];
				}
			}
				
			if (origin.strchr ('/') >0) origin = origin.cutat ('/');
			if (! origin) origin = "RPC";

			origin.strcat ("/src=%s" %format (peer_name));
			env["ip"] = s.peer_name = peer_name;
		}

		if (indata.exists ("header") && indata["header"].exists ("command"))
		{
			uri.strcat ("/%s" %format (indata["header"]["command"]));
		}
	
		res = hdl.handle (indata, s.peer_uid, origin);	
		out = res.tojson ();
		
		if (inhdr.exists ("Accept-Encoding"))
		{
			string ae = inhdr["Accept-Encoding"];
			if (ae.strstr ("deflate") >= 0)
			{
				unsigned long reslen = (out.strlen() * 1.05) + 12;
				char buf[reslen];
				
				if (compress2 ((Bytef*) buf, &reslen,
							   (const Bytef*) out.str(), out.strlen(), 4) == Z_OK)
				{
					outhdr["Content-Encoding"] = "deflate";
					out.strcpy (buf+2, reslen-2);
				}
				else
				{
					log::write (log::warning, "RPC", "Compress error");
				}
			}
		}
		
		outhdr["Content-type"] = "application/json";
	}
	catch (...)
	{
		log::write (log::error, "RPC", "Exception caught");
	}
	return HTTP_OK;
}