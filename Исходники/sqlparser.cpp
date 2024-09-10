// Generate output
void SqlParser::CreateOutputString(const char **output, int *out_size)
{
	if(output == NULL)
		return;

	Token *token = _tokens.GetFirst();

	int len = 0;

	int not_removed = 0;
	int removed = 0;

	// Calculate the output size in bytes and format output
	while(token != NULL)
	{
		bool r = false;
		bool n = false;

		// If token removed its target length is 0
		len += token->GetTargetLength();

		if(token->IsRemoved() == false)
		{
			r = token->Compare('\r', L'\r');

			if(r == false)
				n = token->Compare('\n', L'\n');
		}

		// Check if we need to remove newline (0D0A \r\n on Windows, 0D on Unix)
		if(r == true || n == true)
		{
			// String was not empty and all tokens removed
			if(not_removed == 0 && removed != 0)
			{
				Token::Remove(token);
				len--;

				// If current is \r and next is \n remove \n 
				if(r == true && token->next != NULL && token->next->Compare('\n', L'\n') == true)
				{
					// Its size will be reduced in the next iteration
					Token::Remove(token->next);
				}

				// Remove all spaces in this empty line
				Token *cur = token->prev;

				while(cur != NULL)
				{
					// Remove until new line
					if(cur->Compare('\n', L'\n') || cur->Compare('\r', L'\r'))
						break;

					if(cur->IsBlank() == true && cur->IsRemoved() == false)
					{
						Token::Remove(cur);
						len--;
					}

					cur = cur->prev;
				}
			}

			not_removed = 0;
			removed = 0;
		}
		// Calculate the number of removed and not removed tokens in line
		else
		{
			if(token->IsBlank() == false)
			{
				if(token->IsRemoved() == true)
					removed++;
				else
					not_removed++;
			}
		}

		token = _tokens.GetNext();
	}
	
	if(len == 0)
	{
		*output = NULL;

		if(out_size != NULL)
			*out_size = 0;

		return;
	}

	// Allocate buffer
	char *out = new char[len + 1]; *out = 0;

	token = _tokens.GetFirst();
	int cur_len = 0;

	while(token != NULL)
	{
		token->AppendTarget(out, &cur_len);

		token = _tokens.GetNext();
	}

	out[cur_len] = 0;

	*output = out; 

	if(out_size != NULL)
		*out_size = cur_len;
}