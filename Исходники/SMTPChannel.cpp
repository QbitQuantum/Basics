void SMTPChannel::log(const Message& msg)
{
	try
	{
		MailMessage message;
		message.setSender(_sender);
		message.addRecipient(MailRecipient(MailRecipient::PRIMARY_RECIPIENT, _recipient));
		message.setSubject("Log Message from " + _sender);
		std::stringstream content;
		content << "Log Message\r\n"
			<< "===========\r\n\r\n"
			<< "Host: " << Environment::nodeName() << "\r\n"
			<< "Logger: " << msg.getSource() << "\r\n";

		if (_local)
		{
			DateTime dt(msg.getTime());
			content	<< "Timestamp: " << DateTimeFormatter::format(LocalDateTime(dt), DateTimeFormat::RFC822_FORMAT) << "\r\n";
		}
		else
			content	<< "Timestamp: " << DateTimeFormatter::format(msg.getTime(), DateTimeFormat::RFC822_FORMAT) << "\r\n";

		content	<< "Priority: " << NumberFormatter::format(msg.getPriority()) << "\r\n"
			<< "Process ID: " << NumberFormatter::format(msg.getPid()) << "\r\n"
			<< "Thread: " << msg.getThread() << " (ID: " << msg.getTid() << ")\r\n"
			<< "Message text: " << msg.getText() << "\r\n\r\n";

		message.addContent(new StringPartSource(content.str()));
	
		if (!_attachment.empty())
		{
			{
				Poco::FileInputStream fis(_attachment, std::ios::in | std::ios::binary | std::ios::ate);
				if (fis.good())
				{
					int size = fis.tellg();
					char* pMem = new char [size];
					fis.seekg(std::ios::beg);
					fis.read(pMem, size);
					message.addAttachment(_attachment, new StringPartSource(std::string(pMem, size), _type, _attachment));
					delete [] pMem;
				}
			}
			if (_delete) File(_attachment).remove();
		}

		SMTPClientSession session(_mailHost);
		session.login();
		session.sendMessage(message);
		session.close();
	} 
	catch (Exception&) 
	{ 
		if (_throw) throw; 
	}
}