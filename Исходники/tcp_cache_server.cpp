	void fetch()
	{
		std::string a;
		std::set<std::string> tags,*ptags=0;
		std::string key;
		key.assign(data_in.begin(),data_in.end());
		if(hin.operations.fetch.transfer_triggers)
			ptags=&tags;
		uint64_t generation;
		time_t timeout;
		if(!cache.fetch(key,&a,ptags,&timeout,&generation)) {
			hout.opcode=opcodes::no_data;
			return;
		}
		if(hin.operations.fetch.transfer_if_not_uptodate 
			&& generation==hin.operations.fetch.current_gen)
		{
			hout.opcode=opcodes::uptodate;
			return;
		}
		hout.opcode=opcodes::data;
		data_out.swap(a);
		hout.operations.data.data_len=data_out.size();
		if(ptags) {
			for(std::set<std::string>::iterator p=tags.begin(),e=tags.end();p!=e;++p) {
				data_out.append(p->c_str(),p->size()+1);
			}
		}
		hout.operations.data.triggers_len=data_out.size()-hout.operations.data.data_len;
		hout.size=data_out.size();
		
		hout.operations.data.generation=generation;
		time_t now=time(0);
		hout.operations.data.timeout = timeout > now ? timeout - now : 0;
	}