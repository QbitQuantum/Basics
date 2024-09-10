char *OpenDDLParser::parseDataList( char *in, char *end, Value::ValueType type, Value **data, 
                                    size_t &numValues, Reference **refs, size_t &numRefs ) {
    *data = ddl_nullptr;
    numValues = numRefs = 0;
    if( ddl_nullptr == in || in == end ) {
        return in;
    }

    in = lookForNextToken( in, end );
    if( *in == '{' ) {
        ++in;
        Value *current( ddl_nullptr ), *prev( ddl_nullptr );
        while( '}' != *in ) {
            current = ddl_nullptr;
            in = lookForNextToken( in, end );
            if ( Value::ddl_ref == type ) {
                std::vector<Name*> names;
                in = parseReference( in, end, names );
                if ( !names.empty() ) {
                    Reference *ref = new Reference( names.size(), &names[ 0 ] );
                    *refs = ref;
                    numRefs = names.size();
                }
            } else  if ( Value::ddl_none == type ) {
                if (isInteger( in, end )) {
                    in = parseIntegerLiteral( in, end, &current );
                } else if (isFloat( in, end )) {
                    in = parseFloatingLiteral( in, end, &current );
                } else if (isStringLiteral( *in )) {
                    in = parseStringLiteral( in, end, &current );
                } else if (isHexLiteral( in, end )) {
                    in = parseHexaLiteral( in, end, &current );
                }
            } else {
                switch(type){
                    case Value::ddl_int8:
                    case Value::ddl_int16:
                    case Value::ddl_int32:
                    case Value::ddl_int64:
                    case Value::ddl_unsigned_int8:
                    case Value::ddl_unsigned_int16:
                    case Value::ddl_unsigned_int32:
                    case Value::ddl_unsigned_int64:
                        in = parseIntegerLiteral( in, end, &current, type);
                        break;
                    case Value::ddl_half:
                    case Value::ddl_float:
                    case Value::ddl_double:
                        in = parseFloatingLiteral( in, end, &current, type);
                        break;
                    case Value::ddl_string:
                        in = parseStringLiteral( in, end, &current );
                        break;
                    default:
                        break;
                }
            }

            if( ddl_nullptr != current ) {
                if( ddl_nullptr == *data ) {
                    *data = current;
                    prev = current;
                } else {
                    prev->setNext( current );
                    prev = current;
                }
                ++numValues;
            }

            in = getNextSeparator( in, end );
            if( ',' != *in && Grammar::CloseBracketToken[ 0 ] != *in && !isSpace( *in ) ) {
                break;
            }
        }
        ++in;
    }

    return in;
}