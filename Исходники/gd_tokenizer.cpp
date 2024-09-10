Vector<uint8_t> GDTokenizerBuffer::parse_code_string(const String& p_code) {

	Vector<uint8_t> buf;


	Map<StringName,int> identifier_map;
	HashMap<Variant,int,VariantHasher> constant_map;
	Map<uint32_t,int> line_map;
	Vector<uint32_t> token_array;

	GDTokenizerText tt;
	tt.set_code(p_code);
	int line=-1;
	int col=0;

	while(true) {

		if (tt.get_token_line()!=line) {

			line=tt.get_token_line();
			line_map[line]=token_array.size();
		}

		uint32_t token=tt.get_token();
		switch(tt.get_token()) {

			case TK_IDENTIFIER: {
				StringName id = tt.get_token_identifier();
				if (!identifier_map.has(id)) {
					int idx = identifier_map.size();
					identifier_map[id]=idx;
				}
				token|=identifier_map[id]<<TOKEN_BITS;
			} break;
			case TK_CONSTANT: {

				Variant c = tt.get_token_constant();
				if (!constant_map.has(c)) {
					int idx = constant_map.size();
					constant_map[c]=idx;
				}
				token|=constant_map[c]<<TOKEN_BITS;
			} break;
			case TK_BUILT_IN_TYPE: {

				token|=tt.get_token_type()<<TOKEN_BITS;
			} break;
			case TK_BUILT_IN_FUNC: {

				token|=tt.get_token_built_in_func()<<TOKEN_BITS;

			} break;
			case TK_NEWLINE: {

				token|=tt.get_token_line_indent()<<TOKEN_BITS;
			} break;
			case TK_ERROR: {

				ERR_FAIL_V(Vector<uint8_t>());
			} break;
			default: {}

		};

		token_array.push_back(token);

		if (tt.get_token()==TK_EOF)
			break;
		tt.advance();

	}

	//reverse maps

	Map<int,StringName> rev_identifier_map;
	for(Map<StringName,int>::Element *E=identifier_map.front();E;E=E->next()) {
		rev_identifier_map[E->get()]=E->key();
	}

	Map<int,Variant> rev_constant_map;
	const Variant *K =NULL;
	while((K=constant_map.next(K))) {
		rev_constant_map[constant_map[*K]]=*K;
	}

	Map<int,uint32_t> rev_line_map;
	for(Map<uint32_t,int>::Element *E=line_map.front();E;E=E->next()) {
		rev_line_map[E->get()]=E->key();
	}

	//save header
	buf.resize(24);
	buf[0]='G';
	buf[1]='D';
	buf[2]='S';
	buf[3]='C';
	encode_uint32(BYTECODE_VERSION,&buf[4]);
	encode_uint32(identifier_map.size(),&buf[8]);
	encode_uint32(constant_map.size(),&buf[12]);
	encode_uint32(line_map.size(),&buf[16]);
	encode_uint32(token_array.size(),&buf[20]);

	//save identifiers

	for(Map<int,StringName>::Element *E=rev_identifier_map.front();E;E=E->next()) {

		CharString cs = String(E->get()).utf8();
		int len = cs.length()+1;
		int extra = 4-(len%4);
		if (extra==4)
			extra=0;

		uint8_t ibuf[4];
		encode_uint32(len+extra,ibuf);
		for(int i=0;i<4;i++) {
			buf.push_back(ibuf[i]);
		}
		for(int i=0;i<len;i++) {
			buf.push_back(cs[i]^0xb6);
		}
		for(int i=0;i<extra;i++) {
			buf.push_back(0^0xb6);
		}
	}

	for(Map<int,Variant>::Element *E=rev_constant_map.front();E;E=E->next()) {

		int len;
		Error err = encode_variant(E->get(),NULL,len);
		ERR_FAIL_COND_V(err!=OK,Vector<uint8_t>());
		int pos=buf.size();
		buf.resize(pos+len);
		encode_variant(E->get(),&buf[pos],len);
	}

	for(Map<int,uint32_t>::Element *E=rev_line_map.front();E;E=E->next()) {

		uint8_t ibuf[8];
		encode_uint32(E->key(),&ibuf[0]);
		encode_uint32(E->get(),&ibuf[4]);
		for(int i=0;i<8;i++)
			buf.push_back(ibuf[i]);
	}

	for(int i=0;i<token_array.size();i++) {

		uint32_t token = token_array[i];

		if (token&~TOKEN_MASK) {
			uint8_t buf4[4];
			encode_uint32(token_array[i]|TOKEN_BYTE_MASK,&buf4[0]);
			for(int j=0;j<4;j++) {
				buf.push_back(buf4[j]);
			}
		} else {
			buf.push_back(token);
		}
	}

	return buf;

}