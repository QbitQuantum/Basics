void CActionSet::Hex(HBufC8& aString)
{
    TPtr8 ptr=aString.Des();
    if (aString.Length()%2)
    {
        ptr.SetLength(0);
        return;
    }
    TInt i;
    for (i=0; i<aString.Length(); i+=2)
    {
        TUint8 tmp;
        tmp=(TUint8)(aString[i]-(aString[i]>'9'?('A'-10):'0'));
        tmp*=16;
        tmp|=(TUint8)(aString[i+1]-(aString[i+1]>'9'?('A'-10):'0'));
        ptr[i/2]=tmp;
    }
    ptr.SetLength(aString.Length()/2);
}