// virtual
S32 LLSDBinaryFormatter::format(const LLSD& data, std::ostream& ostr, U32 options) const
{
	S32 format_count = 1;
	switch(data.type())
	{
	case LLSD::TypeMap:
	{
		ostr.put('{');
		U32 size_nbo = htonl(data.size());
		ostr.write((const char*)(&size_nbo), sizeof(U32));
		LLSD::map_const_iterator iter = data.beginMap();
		LLSD::map_const_iterator end = data.endMap();
		for(; iter != end; ++iter)
		{
			ostr.put('k');
			formatString((*iter).first, ostr);
			format_count += format((*iter).second, ostr);
		}
		ostr.put('}');
		break;
	}

	case LLSD::TypeArray:
	{
		ostr.put('[');
		U32 size_nbo = htonl(data.size());
		ostr.write((const char*)(&size_nbo), sizeof(U32));
		LLSD::array_const_iterator iter = data.beginArray();
		LLSD::array_const_iterator end = data.endArray();
		for(; iter != end; ++iter)
		{
			format_count += format(*iter, ostr);
		}
		ostr.put(']');
		break;
	}

	case LLSD::TypeUndefined:
		ostr.put('!');
		break;

	case LLSD::TypeBoolean:
		if(data.asBoolean()) ostr.put(BINARY_TRUE_SERIAL);
		else ostr.put(BINARY_FALSE_SERIAL);
		break;

	case LLSD::TypeInteger:
	{
		ostr.put('i');
		U32 value_nbo = htonl(data.asInteger());
		ostr.write((const char*)(&value_nbo), sizeof(U32));
		break;
	}

	case LLSD::TypeReal:
	{
		ostr.put('r');
		F64 value_nbo = ll_htond(data.asReal());
		ostr.write((const char*)(&value_nbo), sizeof(F64));
		break;
	}

	case LLSD::TypeUUID:
	{
		ostr.put('u');
		LLUUID temp = data.asUUID();
		ostr.write((const char*)(&(temp.mData)), UUID_BYTES);
		break;
	}

	case LLSD::TypeString:
		ostr.put('s');
		formatString(data.asStringRef(), ostr);
		break;

	case LLSD::TypeDate:
	{
		ostr.put('d');
		F64 value = data.asReal();
		ostr.write((const char*)(&value), sizeof(F64));
		break;
	}

	case LLSD::TypeURI:
		ostr.put('l');
		formatString(data.asString(), ostr);
		break;

	case LLSD::TypeBinary:
	{
		ostr.put('b');
		const std::vector<U8>& buffer = data.asBinary();
		U32 size_nbo = htonl(buffer.size());
		ostr.write((const char*)(&size_nbo), sizeof(U32));
		if(buffer.size()) ostr.write((const char*)&buffer[0], buffer.size());
		break;
	}

	default:
		// *NOTE: This should never happen.
		ostr.put('!');
		break;
	}
	return format_count;
}