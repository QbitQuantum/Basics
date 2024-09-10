void SMTPCommand::writeToSocket(shared_ptr <socket> sok, shared_ptr <tracer> tr)
{
	sok->send(m_text + "\r\n");

	if (tr)
		tr->traceSend(m_traceText);
}