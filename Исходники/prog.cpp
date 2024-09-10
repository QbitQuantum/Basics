bool App::on_char(char ch)
{
	switch( ch )
	{
		case 3: // ^C.
		case 4: // ^D.
		{
			write(this->out_fd, "\n", 1);
			this->loop_cont = false;
			break;
		}

		case 8:    // ^H.
		case 0x7F: // DEL.
		{
			int del_width = this->wkbuf.delete_char();
			for( int i=0; i<del_width; ++i )
			{
				// shoud use delete-one-char (dc), etc. capabilities?
				write(this->out_fd, "\x08 \x08", 3);
			}
			break;
		}

		case '\n': // 10:^J.
		{
			// see also: c_iflag/ICRNL.
			this->wkbuf.put_enter();
			break;
		}

		case 21: // ^U.
		{
			this->term.carriage_return();
			this->term.clear_to_end_of_line();
			this->wkbuf.clear_line();
			break;
		}

		case 26: // ^Z.
		{
			int ret;

			kill(getpid(), SIGSTOP);

			// after SIGCONT.
			ret = tcsetattr(this->in_fd, TCSANOW, &this->tio_cur);
			if( ret != 0 )
			{
				perror("tcsetattr(cont)");
				return false;
			}
			break;
		}

		default:
		{
			this->wkbuf.put_char(ch);
			break;
		}
	}

	return true;
}