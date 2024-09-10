bool session_cookies::load(session_interface &session,string &data,time_t &timeout_out)
{
	string cdata=session.get_session_cookie();
	if(cdata.empty()) return false;
	if(cdata[0]!='C') {
		session.clear_session_cookie();
		return false;
	}
	time_t timeout;
	string tmp;
	if(!encryptor_->decrypt(cdata.substr(1),tmp,&timeout))
		return false;
	if(timeout < time(0))
		return false;
	data.swap(tmp);
	timeout_out=timeout;
	return true;
}