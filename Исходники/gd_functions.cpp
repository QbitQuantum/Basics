void GDFunctions::call(Function p_func,const Variant **p_args,int p_arg_count,Variant &r_ret,Variant::CallError &r_error) {

	r_error.error=Variant::CallError::CALL_OK;
#ifdef DEBUG_ENABLED

#define VALIDATE_ARG_COUNT(m_count) \
	if (p_arg_count<m_count) {\
		r_error.error=Variant::CallError::CALL_ERROR_TOO_FEW_ARGUMENTS;\
		r_error.argument=m_count;\
		return;\
	}\
	if (p_arg_count>m_count) {\
		r_error.error=Variant::CallError::CALL_ERROR_TOO_MANY_ARGUMENTS;\
		r_error.argument=m_count;\
		return;\
	}

#define VALIDATE_ARG_NUM(m_arg) \
	if (!p_args[m_arg]->is_num()) {\
		r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;\
		r_error.argument=m_arg;\
		r_error.expected=Variant::REAL;\
		return;\
	}

#else

#define VALIDATE_ARG_COUNT(m_count)
#define VALIDATE_ARG_NUM(m_arg)
#endif

	//using a switch, so the compiler generates a jumptable

	switch(p_func) {

		case MATH_SIN: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::sin(*p_args[0]);
		} break;
		case MATH_COS: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::cos(*p_args[0]);
		} break;
		case MATH_TAN: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::tan(*p_args[0]);
		} break;
		case MATH_SINH: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::sinh(*p_args[0]);
		} break;
		case MATH_COSH: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::cosh(*p_args[0]);
		} break;
		case MATH_TANH: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::tanh(*p_args[0]);
		} break;
		case MATH_ASIN: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::asin(*p_args[0]);
		} break;
		case MATH_ACOS: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::acos(*p_args[0]);
		} break;
		case MATH_ATAN: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::atan(*p_args[0]);
		} break;
		case MATH_ATAN2: {
			VALIDATE_ARG_COUNT(2);
			VALIDATE_ARG_NUM(0);
			VALIDATE_ARG_NUM(1);
			r_ret=Math::atan2(*p_args[0],*p_args[1]);
		} break;
		case MATH_SQRT: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::sqrt(*p_args[0]);
		} break;
		case MATH_FMOD: {
			VALIDATE_ARG_COUNT(2);
			VALIDATE_ARG_NUM(0);
			VALIDATE_ARG_NUM(1);
			r_ret=Math::fmod(*p_args[0],*p_args[1]);
		} break;
		case MATH_FPOSMOD: {
			VALIDATE_ARG_COUNT(2);
			VALIDATE_ARG_NUM(0);
			VALIDATE_ARG_NUM(1);
			r_ret=Math::fposmod(*p_args[0],*p_args[1]);
		} break;
		case MATH_FLOOR: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::floor(*p_args[0]);
		  } break;
		case MATH_CEIL: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::ceil(*p_args[0]);
		} break;
		case MATH_ROUND: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::round(*p_args[0]);
		} break;
		case MATH_ABS: {
			VALIDATE_ARG_COUNT(1);
			if (p_args[0]->get_type()==Variant::INT) {

				int64_t i = *p_args[0];
				r_ret=ABS(i);
			} else if (p_args[0]->get_type()==Variant::REAL) {

				real_t r = *p_args[0];
				r_ret=Math::abs(r);
			} else {

				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::REAL;
			}
		} break;
		case MATH_SIGN: {
				VALIDATE_ARG_COUNT(1);
				if (p_args[0]->get_type()==Variant::INT) {

					int64_t i = *p_args[0];
					r_ret= i < 0 ? -1 : ( i > 0 ? +1 : 0);
				} else if (p_args[0]->get_type()==Variant::REAL) {

					real_t r = *p_args[0];
					r_ret= r < 0.0 ? -1.0 : ( r > 0.0 ? +1.0 : 0.0);
				} else {

					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::REAL;
				}
		} break;
		case MATH_POW: {
			VALIDATE_ARG_COUNT(2);
			VALIDATE_ARG_NUM(0);
			VALIDATE_ARG_NUM(1);
			r_ret=Math::pow(*p_args[0],*p_args[1]);
		} break;
		case MATH_LOG: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::log(*p_args[0]);
		} break;
		case MATH_EXP: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::exp(*p_args[0]);
		} break;
		case MATH_ISNAN: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::is_nan(*p_args[0]);
		} break;
		case MATH_ISINF: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::is_inf(*p_args[0]);
		} break;
		case MATH_EASE: {
			VALIDATE_ARG_COUNT(2);
			VALIDATE_ARG_NUM(0);
			VALIDATE_ARG_NUM(1);
			r_ret=Math::ease(*p_args[0],*p_args[1]);
		} break;
		case MATH_DECIMALS: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::decimals(*p_args[0]);
		} break;
		case MATH_STEPIFY: {
			VALIDATE_ARG_COUNT(2);
			VALIDATE_ARG_NUM(0);
			VALIDATE_ARG_NUM(1);
			r_ret=Math::stepify(*p_args[0],*p_args[1]);
		} break;
		case MATH_LERP: {
			VALIDATE_ARG_COUNT(3);
			VALIDATE_ARG_NUM(0);
			VALIDATE_ARG_NUM(1);
			VALIDATE_ARG_NUM(2);
			r_ret=Math::lerp(*p_args[0],*p_args[1],*p_args[2]);
		} break;
		case MATH_DECTIME: {
			VALIDATE_ARG_COUNT(3);
			VALIDATE_ARG_NUM(0);
			VALIDATE_ARG_NUM(1);
			VALIDATE_ARG_NUM(2);
			r_ret=Math::dectime(*p_args[0],*p_args[1],*p_args[2]);
		} break;
		case MATH_RANDOMIZE: {
			Math::randomize();
			r_ret=Variant();
		} break;
		case MATH_RAND: {
			r_ret=Math::rand();
		} break;
		case MATH_RANDF: {
			r_ret=Math::randf();
		} break;
		case MATH_RANDOM: {
			VALIDATE_ARG_COUNT(2);
			VALIDATE_ARG_NUM(0);
			VALIDATE_ARG_NUM(1);
			r_ret=Math::random(*p_args[0],*p_args[1]);
		} break;
		case MATH_SEED: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			uint32_t seed=*p_args[0];
			Math::seed(seed);
			r_ret=Variant();
		} break;
		case MATH_RANDSEED: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			uint32_t seed=*p_args[0];
			int ret = Math::rand_from_seed(&seed);
			Array reta;
			reta.push_back(ret);
			reta.push_back(seed);
			r_ret=reta;

		} break;
		case MATH_DEG2RAD: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::deg2rad(*p_args[0]);
		} break;
		case MATH_RAD2DEG: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::rad2deg(*p_args[0]);
		} break;
		case MATH_LINEAR2DB: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::linear2db(*p_args[0]);
		} break;
		case MATH_DB2LINEAR: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			r_ret=Math::db2linear(*p_args[0]);
		} break;
		case LOGIC_MAX: {
			VALIDATE_ARG_COUNT(2);
			if (p_args[0]->get_type()==Variant::INT && p_args[1]->get_type()==Variant::INT) {

				int64_t a = *p_args[0];
				int64_t b = *p_args[1];
				r_ret=MAX(a,b);
			} else {
				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);

				real_t a = *p_args[0];
				real_t b = *p_args[1];

				r_ret=MAX(a,b);
			}

		} break;
		case LOGIC_MIN: {
			VALIDATE_ARG_COUNT(2);
			if (p_args[0]->get_type()==Variant::INT && p_args[1]->get_type()==Variant::INT) {

				int64_t a = *p_args[0];
				int64_t b = *p_args[1];
				r_ret=MIN(a,b);
			} else {
				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);

				real_t a = *p_args[0];
				real_t b = *p_args[1];

				r_ret=MIN(a,b);
			}
		} break;
		case LOGIC_CLAMP: {
			VALIDATE_ARG_COUNT(3);
			if (p_args[0]->get_type()==Variant::INT && p_args[1]->get_type()==Variant::INT && p_args[2]->get_type()==Variant::INT) {

				int64_t a = *p_args[0];
				int64_t b = *p_args[1];
				int64_t c = *p_args[2];
				r_ret=CLAMP(a,b,c);
			} else {
				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);
				VALIDATE_ARG_NUM(2);

				real_t a = *p_args[0];
				real_t b = *p_args[1];
				real_t c = *p_args[2];

				r_ret=CLAMP(a,b,c);
			}
		} break;
		case LOGIC_NEAREST_PO2: {
			VALIDATE_ARG_COUNT(1);
			VALIDATE_ARG_NUM(0);
			int64_t num = *p_args[0];
			r_ret = nearest_power_of_2(num);
		} break;
		case OBJ_WEAKREF: {
			VALIDATE_ARG_COUNT(1);
			if (p_args[0]->get_type()!=Variant::OBJECT) {

				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::OBJECT;
				return;

			}

			if (p_args[0]->is_ref()) {

				REF r = *p_args[0];
				if (!r.is_valid()) {
					r_ret=Variant();
					return;
				}

				Ref<WeakRef> wref = memnew( WeakRef );
				wref->set_ref(r);
				r_ret=wref;
			} else {
				Object *obj = *p_args[0];
				if (!obj) {
					r_ret=Variant();
					return;
				}
				Ref<WeakRef> wref = memnew( WeakRef );
				wref->set_obj(obj);
				r_ret=wref;
			}




		} break;
		case FUNC_FUNCREF: {
			VALIDATE_ARG_COUNT(2);
			if (p_args[0]->get_type()!=Variant::OBJECT) {

				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::OBJECT;
				r_ret=Variant();
				return;

			}
			if (p_args[1]->get_type()!=Variant::STRING && p_args[1]->get_type()!=Variant::NODE_PATH) {

				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=1;
				r_error.expected=Variant::STRING;
				r_ret=Variant();
				return;

			}

			Ref<FuncRef> fr = memnew( FuncRef);

			Object *obj = *p_args[0];
			fr->set_instance(*p_args[0]);
			fr->set_function(*p_args[1]);

			r_ret=fr;

		} break;
		case TYPE_CONVERT: {
			VALIDATE_ARG_COUNT(2);
			VALIDATE_ARG_NUM(1);
			int type=*p_args[1];
			if (type<0 || type>=Variant::VARIANT_MAX) {

				ERR_PRINT("Invalid type argument to convert()");
				r_ret=Variant::NIL;

			} else {


				r_ret=Variant::construct(Variant::Type(type),p_args,1,r_error);
			}
		} break;
		case TYPE_OF: {

			VALIDATE_ARG_COUNT(1);
			r_ret = p_args[0]->get_type();

		} break;
		case TEXT_STR: {

			String str;
			for(int i=0;i<p_arg_count;i++) {

				String os = p_args[i]->operator String();;

				if (i==0)
					str=os;
				else
					str+=os;
			}

			r_ret=str;

		} break;
		case TEXT_PRINT: {

			String str;
			for(int i=0;i<p_arg_count;i++) {

				str+=p_args[i]->operator String();
			}

			//str+="\n";
			print_line(str);
			r_ret=Variant();


		} break;
		case TEXT_PRINT_TABBED: {

			String str;
			for(int i=0;i<p_arg_count;i++) {

				if (i)
					str+="\t";
				str+=p_args[i]->operator String();
			}

			//str+="\n";
			print_line(str);
			r_ret=Variant();


		} break;
		case TEXT_PRINT_SPACED: {

			String str;
			for(int i=0;i<p_arg_count;i++) {

				if (i)
					str+=" ";
				str+=p_args[i]->operator String();
			}

			//str+="\n";
			print_line(str);
			r_ret=Variant();


		} break;

		case TEXT_PRINTERR: {

			String str;
			for(int i=0;i<p_arg_count;i++) {

				str+=p_args[i]->operator String();
			}

			//str+="\n";
			OS::get_singleton()->printerr("%s\n",str.utf8().get_data());
			r_ret=Variant();

		} break;
		case TEXT_PRINTRAW: {
			String str;
			for(int i=0;i<p_arg_count;i++) {

				str+=p_args[i]->operator String();
			}

			//str+="\n";
			OS::get_singleton()->print("%s",str.utf8().get_data());
			r_ret=Variant();

		} break;
		case VAR_TO_STR: {
			VALIDATE_ARG_COUNT(1);
			String vars;
			VariantWriter::write_to_string(*p_args[0],vars);
			r_ret=vars;
		} break;
		case STR_TO_VAR: {
			VALIDATE_ARG_COUNT(1);
			if (p_args[0]->get_type()!=Variant::STRING) {
				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::STRING;
				r_ret=Variant();
				return;
			}

			VariantParser::StreamString ss;
			ss.s=*p_args[0];

			String errs;
			int line;
			Error err = VariantParser::parse(&ss,r_ret,errs,line);

			if (err!=OK) {
				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::STRING;
				r_ret=Variant();
			}

		} break;
		case VAR_TO_BYTES: {
			VALIDATE_ARG_COUNT(1);

			ByteArray barr;
			int len;
			Error err = encode_variant(*p_args[0],NULL,len);
			if (err) {
				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::NIL;
				r_ret=Variant();
				return;
			}

			barr.resize(len);
			{
				ByteArray::Write w = barr.write();
				encode_variant(*p_args[0],w.ptr(),len);

			}
			r_ret=barr;
		} break;
		case BYTES_TO_VAR: {
			VALIDATE_ARG_COUNT(1);
			if (p_args[0]->get_type()!=Variant::RAW_ARRAY) {
				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::RAW_ARRAY;
				r_ret=Variant();
				return;
			}

			ByteArray varr=*p_args[0];
			Variant ret;
			{
				ByteArray::Read r=varr.read();
				Error err = decode_variant(ret,r.ptr(),varr.size(),NULL);
				if (err!=OK) {
					ERR_PRINT("Not enough bytes for decoding..");
					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::RAW_ARRAY;
					r_ret=Variant();
					return;
				}

			}

			r_ret=ret;

		} break;
		case GEN_RANGE: {

			switch(p_arg_count) {

				case 0: {

					r_error.error=Variant::CallError::CALL_ERROR_TOO_FEW_ARGUMENTS;
					r_error.argument=1;

				} break;
				case 1: {

					VALIDATE_ARG_NUM(0);
					int count=*p_args[0];
					Array arr(true);
					if (count<=0) {
						r_ret=arr;
						return;
					}
					Error err = arr.resize(count);
					if (err!=OK) {
						r_error.error=Variant::CallError::CALL_ERROR_INVALID_METHOD;
						r_ret=Variant();
						return;
					}

					for(int i=0;i<count;i++) {
						arr[i]=i;
					}

					r_ret=arr;
				} break;
				case 2: {

					VALIDATE_ARG_NUM(0);
					VALIDATE_ARG_NUM(1);

					int from=*p_args[0];
					int to=*p_args[1];

					Array arr(true);
					if (from>=to) {
						r_ret=arr;
						return;
					}
					Error err = arr.resize(to-from);
					if (err!=OK) {
						r_error.error=Variant::CallError::CALL_ERROR_INVALID_METHOD;
						r_ret=Variant();
						return;
					}
					for(int i=from;i<to;i++)
						arr[i-from]=i;
					r_ret=arr;
				} break;
				case 3: {

					VALIDATE_ARG_NUM(0);
					VALIDATE_ARG_NUM(1);
					VALIDATE_ARG_NUM(2);

					int from=*p_args[0];
					int to=*p_args[1];
					int incr=*p_args[2];
					if (incr==0) {

						ERR_EXPLAIN("step argument is zero!");
						r_error.error=Variant::CallError::CALL_ERROR_INVALID_METHOD;
						ERR_FAIL();
					}

					Array arr(true);
					if (from>=to && incr>0) {
						r_ret=arr;
						return;
					}
					if (from<=to && incr<0) {
						r_ret=arr;
						return;
					}

					//calculate how many
					int count=0;
					if (incr>0) {

						count=((to-from-1)/incr)+1;
					} else {

						count=((from-to-1)/-incr)+1;
					}


					Error err = arr.resize(count);

					if (err!=OK) {
						r_error.error=Variant::CallError::CALL_ERROR_INVALID_METHOD;
						r_ret=Variant();
						return;
					}

					if (incr>0) {
						int idx=0;
						for(int i=from;i<to;i+=incr) {
							arr[idx++]=i;
						}
					} else {

						int idx=0;
						for(int i=from;i>to;i+=incr) {
							arr[idx++]=i;
						}
					}

					r_ret=arr;
				} break;
				default: {

					r_error.error=Variant::CallError::CALL_ERROR_TOO_MANY_ARGUMENTS;
					r_error.argument=3;
				} break;
			}

		} break;
		case RESOURCE_LOAD: {
			VALIDATE_ARG_COUNT(1);
			if (p_args[0]->get_type()!=Variant::STRING) {
				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_ret=Variant();
			}
			r_ret=ResourceLoader::load(*p_args[0]);

		} break;
		case INST2DICT: {

			VALIDATE_ARG_COUNT(1);

			if (p_args[0]->get_type()==Variant::NIL) {
				r_ret=Variant();
			} else if (p_args[0]->get_type()!=Variant::OBJECT) {
				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_ret=Variant();
			} else {

				Object *obj = *p_args[0];
				if (!obj) {
					r_ret=Variant();

				} else if (!obj->get_script_instance() || obj->get_script_instance()->get_language()!=GDScriptLanguage::get_singleton()) {

					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::DICTIONARY;
					ERR_PRINT("Not a script with an instance");

				} else {

					GDInstance *ins = static_cast<GDInstance*>(obj->get_script_instance());
					Ref<GDScript> base = ins->get_script();
					if (base.is_null()) {

						r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
						r_error.argument=0;
						r_error.expected=Variant::DICTIONARY;
						ERR_PRINT("Not based on a script");
						return;

					}


					GDScript *p = base.ptr();
					Vector<StringName> sname;

					while(p->_owner) {

						sname.push_back(p->name);
						p=p->_owner;
					}
					sname.invert();


					if (!p->path.is_resource_file()) {
						r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
						r_error.argument=0;
						r_error.expected=Variant::DICTIONARY;
						print_line("PATH: "+p->path);
						ERR_PRINT("Not based on a resource file");

						return;
					}

					NodePath cp(sname,Vector<StringName>(),false);

					Dictionary d(true);
					d["@subpath"]=cp;
					d["@path"]=p->path;


					p = base.ptr();

					while(p) {

						for(Set<StringName>::Element *E=p->members.front();E;E=E->next()) {

							Variant value;
							if (ins->get(E->get(),value)) {

								String k = E->get();
								if (!d.has(k)) {
									d[k]=value;
								}
							}
						}

						p=p->_base;
					}

					r_ret=d;

				}
			}

		} break;
		case DICT2INST: {

			VALIDATE_ARG_COUNT(1);

			if (p_args[0]->get_type()!=Variant::DICTIONARY) {

				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::DICTIONARY;
				return;
			}

			Dictionary d = *p_args[0];

			if (!d.has("@path")) {

				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::OBJECT;
				return;
			}

			Ref<Script> scr = ResourceLoader::load(d["@path"]);
			if (!scr.is_valid()) {

				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::OBJECT;
				return;
			}

			Ref<GDScript> gdscr = scr;

			if (!gdscr.is_valid()) {

				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_error.expected=Variant::OBJECT;
				return;
			}

			NodePath sub;
			if (d.has("@subpath")) {
				sub=d["@subpath"];
			}

			for(int i=0;i<sub.get_name_count();i++) {

				gdscr = gdscr->subclasses[ sub.get_name(i)];
				if (!gdscr.is_valid()) {

					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::OBJECT;
					return;
				}
			}

			r_ret = gdscr->_new(NULL,0,r_error);

            GDInstance *ins = static_cast<GDInstance*>(static_cast<Object*>(r_ret)->get_script_instance());
            Ref<GDScript> gd_ref = ins->get_script();

            for(Map<StringName,GDScript::MemberInfo>::Element *E = gd_ref->member_indices.front(); E; E = E->next()) {
                if(d.has(E->key())) {
                    ins->members[E->get().index] = d[E->key()];
                }
            }

		} break;
		case HASH: {

			VALIDATE_ARG_COUNT(1);
			r_ret=p_args[0]->hash();

		} break;
		case COLOR8: {

			if (p_arg_count<3) {
				r_error.error=Variant::CallError::CALL_ERROR_TOO_FEW_ARGUMENTS;
				r_error.argument=3;
				return;
			}
			if (p_arg_count>4) {
				r_error.error=Variant::CallError::CALL_ERROR_TOO_MANY_ARGUMENTS;
				r_error.argument=4;
				return;
			}

			VALIDATE_ARG_NUM(0);
			VALIDATE_ARG_NUM(1);
			VALIDATE_ARG_NUM(2);

			Color color(*p_args[0],*p_args[1],*p_args[2]);

			if (p_arg_count==4) {
				VALIDATE_ARG_NUM(3);
				color.a=*p_args[3];
			}

			r_ret=color;

		} break;

		case PRINT_STACK: {

			ScriptLanguage* script = GDScriptLanguage::get_singleton();
			for (int i=0; i < script->debug_get_stack_level_count(); i++) {

				print_line("Frame "+itos(i)+" - "+script->debug_get_stack_level_source(i)+":"+itos(script->debug_get_stack_level_line(i))+" in function '"+script->debug_get_stack_level_function(i)+"'");
			};
		} break;

		case INSTANCE_FROM_ID: {

			VALIDATE_ARG_COUNT(1);
			if (p_args[0]->get_type()!=Variant::INT && p_args[0]->get_type()!=Variant::REAL) {
				r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
				r_error.argument=0;
				r_ret=Variant();
				break;
			}

			uint32_t id=*p_args[0];
			r_ret=ObjectDB::get_instance(id);

		} break;
		case FUNC_MAX: {

			ERR_FAIL();
		} break;

	}

}