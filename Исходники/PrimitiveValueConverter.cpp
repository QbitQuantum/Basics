char PrimitiveValueConverter::convert(const PrimitiveValueNode& value) const {

    switch( value.getType() ) {
        case PrimitiveValueNode::CHAR_TYPE:
            return value.getChar();
        case PrimitiveValueNode::STRING_TYPE:
        case PrimitiveValueNode::BIG_STRING_TYPE:
        {
            try{
                return (char)decaf::lang::Byte::parseByte( value.getString() );
            } catch( decaf::lang::Exception& ex ) {}
        }
        default:
            throw decaf::lang::exceptions::UnsupportedOperationException(
                 __FILE__, __LINE__, "Unsupported Type Conversion" );
    }
}