bool FieldParser::ParseXCLCField(ESMStream& stream, uint16_t length, XCLCField& outField) {
    //FIXME: According to the documents this is a 12 byte field, however I'm encountering only 8 bytes.
    if (length != sizeof(outField))
    {
        if (length == sizeof(uint32_t) * 2) {
            stream.Read32((uint32_t &)outField.X);
            stream.Read32((uint32_t &)outField.Y);
            
            outField.LandHideFlags = LandHideFlag::None;
            return true;
        }
        
        return false;
    }
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}