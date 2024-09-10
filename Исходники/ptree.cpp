obj* php_load_impl(const char* base, const char*& beg, const char* end) {
#define THROW_INPUT_ERROR2(msg, ptr) \
	do{ char buf[256]; \
		int blen = snprintf(buf, sizeof(buf), "%s at pos: %ld", msg, long(ptr-base)); \
		std::string strMsg(buf, blen); \
		throw std::logic_error(strMsg); \
	} while (0)
#define THROW_INPUT_ERROR(msg) THROW_INPUT_ERROR2(msg, beg)
	switch (*beg) {
		default: {
			std::string msg = "php_load: invalid type: ";
			msg.push_back(*beg);
			msg += ", input:";
			msg.append(beg, std::min<size_t>(100, end-beg));
			throw std::logic_error(msg);
		}
		case 'i': { // i:val;
			if (++beg >= end)
				THROW_INPUT_ERROR("php_load: Incompleted php integer");
			if (':' != *beg)
				THROW_INPUT_ERROR("php_load: integer, expect ':'");
			char* pp = NULL;
			long long val = strtoll(beg+1, &pp, 10);
			if (';' != *pp)
				THROW_INPUT_ERROR2("php_load: integer, expect ';'", pp);
			beg = pp + 1;
			if (sizeof(long) == sizeof(long long) || (LONG_MIN <= val&&val <= LONG_MAX))
				return new obj_long((long)val);
			else
				return new obj_llong(val);
		}
		case 'b': { // b:val;
			if (++beg >= end)
				THROW_INPUT_ERROR("php_load: Incompleted php boolean");
			if (':' != *beg)
				THROW_INPUT_ERROR("php_load: boolean, expect ':'");
			char* pp = NULL;
			long val = strtol(beg+1, &pp, 10);
			if (';' != *pp)
				THROW_INPUT_ERROR2("php_load: boolean, expect ';'", pp);
			beg = pp + 1;
			return new obj_bool(val ? 1 : 0);
		}
#if 0
		case 'd': { // d:val;
			if (++beg >= end)
				THROW_INPUT_ERROR("php_load: Incompleted php double");
			if (':' != *beg)
				THROW_INPUT_ERROR("php_load: double, expect ':'");
			char* pp = NULL;
			double val = strtod(beg+1, &pp);
			if (';' != *pp)
				THROW_INPUT_ERROR("php_load: double, expect ';'");
			beg = pp + 1;
			return new obj_double(val);
		}
#else
		case 'd': { // d:val;
			if (++beg >= end)
				THROW_INPUT_ERROR("php_load: Incompleted php double");
			if (':' != *beg)
				THROW_INPUT_ERROR("php_load: long double, expect ':'");
			char* pp = NULL;
		#ifdef __CYGWIN__ //_LDBL_EQ_DBL
			double val = strtod(beg+1, &pp);
		#else
			long double val = strtold(beg+1, &pp);
		#endif
			if (';' != *pp)
				THROW_INPUT_ERROR2("php_load: long double, expect ';'", pp);
			beg = pp + 1;
			return new obj_ldouble(val);
		}
#endif
		case 's': { // s:size:"content";
			if (++beg >= end)
				THROW_INPUT_ERROR("php_load: Incompleted php string");
			if (':' != *beg)
				THROW_INPUT_ERROR("php_load: string.size expect ':'");
			char* pp = NULL;
			long len = strtol(beg+1, &pp, 10);
			if (':' != *pp)
				THROW_INPUT_ERROR2("php_load: string.content expect ':'", pp);
			if (len < 0)
				THROW_INPUT_ERROR2("php_load: string.size is negtive", beg+1);
			if ('"' != pp[1])
				THROW_INPUT_ERROR2("php_load: string.content expect '\"'", pp+1);
			if ('"' != pp[len+2])
				THROW_INPUT_ERROR2("php_load: string.content not found right quote", pp+len+2);
			if (';' != pp[len+3])
				THROW_INPUT_ERROR2("php_load: string didn't end with ';'", pp+len+3);
			std::auto_ptr<obj_string> x(new obj_string);
			x->resize(len);
			x->assign(pp+2, len);
			beg = pp + len + 4; // s:size:"content";
			return x.release();
		}
		case 'a': { // A:size:{key;value; ....}
		//	fprintf(stderr, "loading array: ");
			if (++beg >= end)
				THROW_INPUT_ERROR("php_load: Incompleted php array");
			if (':' != *beg)
				THROW_INPUT_ERROR("php_load: array.size expect ':'");
			char* pp = NULL;
			long len = strtol(beg+1, &pp, 10);
		//	fprintf(stderr, "size=%ld\n", len);
			if (':' != pp[0] || '{' != pp[1])
				THROW_INPUT_ERROR2("php_load: array.size should followed by ':{'", pp);
			std::auto_ptr<obj_array> arr(new obj_array);
			std::auto_ptr<php_array> map;
			arr->resize(2*len);
			beg = pp + 2;
			long max_idx = -1;
			for (long i = 0; i < len; ++i) {
			//	fprintf(stderr, "loading array[%ld]:\n", i);
				const char* key_pos = beg;
				std::auto_ptr<obj> key(php_load_impl(base, beg, end));
				if (key.get() == NULL) {
					THROW_INPUT_ERROR2("php_load: array.key must not be NULL", key_pos);
				}
				if (arr.get()) {
					obj_long* l = dynamic_cast<obj_long*>(key.get());
					if (l) {
						long idx = l->t;
						if (idx >= 0 && idx < (long)arr->size()) {
							(*arr)[idx].reset(php_load_impl(base, beg, end));
							max_idx = std::max(idx, max_idx);
							continue;
						}
					}
				}
				if (map.get() == NULL)
					map.reset(new php_array);
				if (arr.get()) {
					for (long j = 0; j <= max_idx; ++j) {
						if ((*arr)[j])
							(*map)[obj_ptr(new obj_long(j))] = (*arr)[j];
					}
					arr.reset(NULL);
				}
				(*map)[obj_ptr(key.get())].reset(php_load_impl(base, beg, end));
				key.release();
			}
			if ('}' != *beg)
				THROW_INPUT_ERROR("php_load: array not correctly closed");
			beg += 1;
			if (arr.get()) {
				arr->resize(max_idx+1);
				arr->shrink_to_fit();
				return arr.release();
			}
			return map.release();
		}
		case 'N': {
			if (++beg >= end)
				THROW_INPUT_ERROR("php_load: Incompleted php NULL");
			if (';' != *beg)
				THROW_INPUT_ERROR("php_load: NULL expect ';'");
			beg += 1;
			return NULL;
		}
		case 'O': {
// O:strlen(class name):"class name":fields_num:{s:strlen(field name):"field name":field definition;(repeated per field)}
			if (++beg >= end)
				THROW_INPUT_ERROR("php_load: Incompleted php Object");
			if (':' != *beg)
				THROW_INPUT_ERROR("php_load: Object.namelen expect ':' 1");
			char* pp = NULL;
			long len = strtol(beg+1, &pp, 10);
			if (':' != pp[0] && '"' != pp[1])
				THROW_INPUT_ERROR2("php_load: Object.namelen expect ':\"' 2", pp);
			if (pp + 4 + len > end)
				THROW_INPUT_ERROR2("php_load: Object 3", pp);
			std::auto_ptr<php_object> tree(new php_object);
			tree->cls_name.assign(pp + 2, len);
			long fields = strtol(pp + 4 + len, &pp, 10);
			if (':' != pp[0] || '{' != pp[1])
				THROW_INPUT_ERROR2("php_load: Object 4", pp);
			beg = pp + 2;
			for (long i = 0; i < fields; ++i) {
				std::auto_ptr<obj> pname(php_load_impl(base, beg, end));
				obj_string* name = dynamic_cast<obj_string*>(pname.get());
				if (NULL == name)
					THROW_INPUT_ERROR("object field name is not a string");
				std::auto_ptr<obj> value(php_load_impl(base, beg, end));
				tree->fields[*name].reset(value.release());
			}
			if ('}' != beg[0])
				THROW_INPUT_ERROR("php_load: Object not correctly closed");
			beg += 1;
			return tree.release();
		}
	}
	assert(0);
	return NULL;
}