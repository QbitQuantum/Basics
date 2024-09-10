TInt CSenLayeredXmlProperties::PropertiesByTypeL(const TDesC8& aType,
                                                 RPointerArray<MSenProperty>& aArray)
    {
    TInt retVal(KErrNotFound);

    retVal = AllPropertiesByTypeL(aType, aArray);

    // Remove omitted values from the array.
    TInt propsCount = aArray.Count()-1;
    for (TInt i=propsCount; i>=0; i--)
        {
        CSenPropertiesElement* pElement = (CSenPropertiesElement*)aArray[i];
		const TDesC8* pAttrValue = pElement->AttrValue(KSenOmittedAttributeName);
		if ( pAttrValue )
            {
            if ( *pAttrValue == KSenOmittedTrueNoValue)
		        {
		        aArray.Remove(i);
                }
            else if ( *pAttrValue == KSenPropertyTrue)
                {
		        aArray.Remove(i);
                }
            }
        }
    
    if ( aArray.Count() > 0 )
        {
        retVal=KErrNone;
        }
    
    return retVal;
    }