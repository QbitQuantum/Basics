	lucene::analysis::Token* next1(lucene::analysis::Token* token, int& retTokenLength)
	{
		int32_t length = 0;
		retTokenLength = 0;

		/** the position used to create Token */
		int32_t start = m_offset;

		while (true) {
			/** current character */
            TCHAR c;
            int charlen = 1;

			m_offset++;

			if (m_bufferIndex >= m_dataLen) {
				m_dataLen = input->read(m_ioBuffer, 1, LUCENE_IO_BUFFER_SIZE);
				m_bufferIndex = 0;
			}

			if (m_dataLen == -1) {
				if (length > 0) {
					if (m_preIsTokened == true) {
						length = 0;
						m_preIsTokened = false;
					}

					break;
				} else {
					return NULL;
				}
			} else {
				//get current character
				c = m_ioBuffer[m_bufferIndex++];
			}

			//to support surrogates, we'll need to convert the incoming utf16 into
			//ucs4(c variable). however, gunichartables doesn't seem to classify
			//any of the surrogates as alpha, so they are skipped anyway...
			//so for now we just convert to ucs4 so that we dont corrupt the input.
            if ( c >= 0xd800 || c <= 0xdfff ){
                TCHAR c2 = m_ioBuffer[m_bufferIndex];
				if ( c2 >= 0xdc00 && c2 <= 0xdfff ){
					m_bufferIndex++;
					m_offset++;
					charlen=2;

					c = (((c & 0x03ffL) << 10) | ((c2 & 0x03ffL) <<  0)) + 0x00010000L;
				}
			}

			//if the current character is ASCII or Extend ASCII
			if ((c <= 0xFF) //is BASIC_LATIN
                || (c>=0xFF00 && c<=0xFFEF) //ascii >0x74 cast to unsigned...
				) {
					if (c >= 0xFF00) {
						//todo: test this... only happens on platforms where char is signed, i think...
						/** convert  HALFWIDTH_AND_FULLWIDTH_FORMS to BASIC_LATIN */
						c -= 0xFEE0;
					}

					////不是CJK////
					// if the current character is a letter or "_" "+" "#"
                    if (iswalnum(c) || ((c == '_') || (c == '+') || (c == '#')) ) {
						if (length == 0) {
							// "javaC1C2C3C4linux" <br>
							//      ^--: the current character begin to token the ASCII
							// letter
							start = m_offset - 1;
						} else if (m_tokenType == tokenTypeDouble) {
							// "javaC1C2C3C4linux" <br>
							//              ^--: the previous non-ASCII
							// : the current character
							m_offset-=charlen;
							m_bufferIndex-=charlen;
							m_tokenType = tokenTypeSingle;

							if (m_preIsTokened == true) {
								// there is only one non-ASCII has been stored
								length = 0;
								m_preIsTokened = false;

								break;
							} else {
								break;
							}
						}

						// store the LowerCase(c) in the buffer
                        m_buffer[length++] = towlower((TCHAR)c);
						m_tokenType = tokenTypeSingle;

						// break the procedure if buffer overflowed!
						if (length == LUCENE_MAX_WORD_LEN) {
							break;
						}
					} else if (length > 0) {
						if (m_preIsTokened == true) {
							length = 0;
							m_preIsTokened = false;
						} else {
							break;
						}
					}
			} 
			else 
			{
				// CJK
				// non-ASCII letter, eg."C1C2C3C4"
                if ( iswalpha(c) || (!m_ignoreSurrogates && c>=0x10000) )
				{
					if (length == 0) {
                        start = m_offset - 1;
                        if ( c < 0x00010000L )
                            m_buffer[length++] = (TCHAR)c;
                        else{
                            TCHAR ucs4 = c - 0x00010000L;
                            m_buffer[length++] = (TCHAR)((ucs4 >> 10) & 0x3ff) | 0xd800;
                            m_buffer[length++] = (TCHAR)((ucs4 >>  0) & 0x3ff) | 0xdc00;
                        }

						m_tokenType = tokenTypeDouble;
					} else {
						if (m_tokenType == tokenTypeSingle) {
							m_offset-=charlen;
							m_bufferIndex-=charlen;

							//return the previous ASCII characters
							break;
						} else {
							if ( c < 0x00010000L )
								m_buffer[length++] = (TCHAR)c;
							else{
                                TCHAR ucs4 = c - 0x00010000L;
								m_buffer[length++] = (TCHAR)((ucs4 >> 10) & 0x3ff) | 0xd800;
								m_buffer[length++] = (TCHAR)((ucs4 >>  0) & 0x3ff) | 0xdc00;
							}
                            m_tokenType = tokenTypeDouble;

							if (length >= 2) {
								m_offset-=charlen;
								m_bufferIndex-=charlen;
								m_preIsTokened = true;

								break;
							}
						}
					}
				} 
				else if (length > 0) 