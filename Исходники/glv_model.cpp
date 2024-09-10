	int operator()(const std::string& src){

		size_t p = src.find_first_of("{");
		if(std::string::npos == p) return 0;		// no table found, so return
		
		std::string key, val;
		const char * b = &src[p+1];	// start 1 character after opening '{'

		while(*b && *b!='}'){
			if(isalpha(*b) || *b=='_'){	// is character valid start of identifier?
				const char * e = b+1;
				while(isalnum(*e) || *e=='_') ++e;	// go to end of key name
				key.assign(b, e-b);

				while(isBlank(*e) || *e=='=') ++e;	// go to '='
				
				// find next valid token
				b=e=strpbrk(e, "\"{0123456789.-+");

				if(!b) b=e=&src[src.size()];	// no more valid tokens, so go to end of string

				if(*b){
					// munch characters until end of token
					if(*e == '\"'){
						++e; while(*e!='\"') ++e; ++e;
					}
					else if(*e == '{'){
						while(*e!='}') ++e; ++e;
					}
					else{
						while((isdigit(*e) || *e=='.' || *e=='-' || *e=='+')) ++e;
					}

					val.assign(b,e-b);

					onKeyValue(key, val);
				}
				b=e;
			}
			++b;
		}
		//printf("%d\n", b-&v[0]);
		
		if(*b == '}')	return b+1-&src[0];
		else			return b-&src[0];	
	}