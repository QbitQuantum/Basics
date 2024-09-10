			/**
			 * relative seek
			 **/
			::std::streampos seekoff(::std::streamoff off, ::std::ios_base::seekdir way, ::std::ios_base::openmode which)
			{
				// absolute seek
				if ( way == ::std::ios_base::beg )
				{
					return seekpos(off,which);
				}
				// seek relative to current position
				else if ( way == ::std::ios_base::cur )
				{
					if ( which == std::ios_base::in )
					{
						return seekpos(readpos + (gptr()-eback()),which);
					}
					else if ( which == std::ios_base::out )
					{
						return seekpos(writepos + (pptr()-pbase()),which);
					}
					else
					{
						return -1;
					}
				}
				// seek relative to end of file
				else if ( way == ::std::ios_base::end )
				{
					off_t const endoff = fd->getFileSize();
					return seekpos(endoff+off,which);
				}
				else
				{
					return -1;
				}
			}