void ExternalCommandListener::CommandPipeThread(const String& commandPath)
{
	Utility::SetThreadName("Command Pipe");

	struct stat statbuf;
	bool fifo_ok = false;

	if (lstat(commandPath.CStr(), &statbuf) >= 0) {
		if (S_ISFIFO(statbuf.st_mode) && access(commandPath.CStr(), R_OK) >= 0) {
			fifo_ok = true;
		} else {
			if (unlink(commandPath.CStr()) < 0) {
				BOOST_THROW_EXCEPTION(posix_error()
				    << boost::errinfo_api_function("unlink")
				    << boost::errinfo_errno(errno)
				    << boost::errinfo_file_name(commandPath));
			}
		}
	}

	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

	if (!fifo_ok && mkfifo(commandPath.CStr(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) < 0) {
		Log(LogCritical, "ExternalCommandListener")
		    << "mkfifo() for fifo path '" << commandPath << "' failed with error code " << errno << ", \"" << Utility::FormatErrorNumber(errno) << "\"";
		return;
	}

	/* mkfifo() uses umask to mask off some bits, which means we need to chmod() the
	 * fifo to get the right mask. */
	if (chmod(commandPath.CStr(), mode) < 0) {
		Log(LogCritical, "ExternalCommandListener")
		    << "chmod() on fifo '" << commandPath << "' failed with error code " << errno << ", \"" << Utility::FormatErrorNumber(errno) << "\"";
		return;
	}

	for (;;) {
		int fd = open(commandPath.CStr(), O_RDWR | O_NONBLOCK);

		if (fd < 0) {
			Log(LogCritical, "ExternalCommandListener")
			    << "open() for fifo path '" << commandPath << "' failed with error code " << errno << ", \"" << Utility::FormatErrorNumber(errno) << "\"";
			return;
		}

		FIFO::Ptr fifo = new FIFO();
		Socket::Ptr sock = new Socket(fd);
		StreamReadContext src;

		for (;;) {
			sock->Poll(true, false);

			char buffer[8192];
			size_t rc;

			try {
				rc = sock->Read(buffer, sizeof(buffer));
			} catch (const std::exception& ex) {
				/* We have read all data. */
				if (errno == EAGAIN)
					continue;

				Log(LogWarning, "ExternalCommandListener")
				    << "Cannot read from command pipe." << DiagnosticInformation(ex);
				break;
			}

			/* Empty pipe (EOF) */
			if (rc == 0)
				continue;

			fifo->Write(buffer, rc);

			for (;;) {
				String command;
				StreamReadStatus srs = fifo->ReadLine(&command, src);

				if (srs != StatusNewItem)
					break;

				try {
					Log(LogInformation, "ExternalCommandListener")
					    << "Executing external command: " << command;

					ExternalCommandProcessor::Execute(command);
				} catch (const std::exception& ex) {
					Log(LogWarning, "ExternalCommandListener")
					    << "External command failed: " << DiagnosticInformation(ex, false);
					Log(LogNotice, "ExternalCommandListener")
					    << "External command failed: " << DiagnosticInformation(ex, true);
				}
			}
		}
	}
}