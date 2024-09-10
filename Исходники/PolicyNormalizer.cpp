CSenElement* CPolicyNormalizer::ProcessPolicyReferenceL(CSenElement* aPolicy, CPolicyRegistry* aRegistry)
{    //Loop for wsp:PolicyReference element and if found then replace
    // it with wsp:All and copy everything from found policy to here
    if(aRegistry == NULL)
        return NULL;
    //Check if there is a reference if yes then resolve it
    RPointerArray<CSenElement> referenceChildren;
    
    if(aPolicy->ElementsL(referenceChildren, KWsPolicyReference) == KErrNone)
        {
        TInt childCount = referenceChildren.Count();
        TInt i = 0;
        CSenElement* pNextChild;

        while (i < childCount)
            {
            pNextChild = referenceChildren[i];
            TPtrC8 localName = pNextChild->LocalName();
            TPtrC8 uri = GetReferenceUriL(pNextChild);
            _LIT8(KHash, "#");
            
            HBufC8* aRippedUri = NULL;
             
            if(uri.Left(1).Compare(KHash) == 0)
               aRippedUri = uri.Right(uri.Length()-1).AllocL();
            
            if(aRippedUri->Length() > 0)
                {
                CSenElement* referedPolicy = aRegistry->LookupPolicy(aRippedUri->Des());
                if(referedPolicy)
                    {
                    ReplacePolicyReferenceL(pNextChild,referedPolicy);
                    }
                }
                delete aRippedUri;
                
            i++;
            }
        }
        
    //Check in all children recursively PolicyReferences and resolve them
    RPointerArray<CSenElement>& children = aPolicy->ElementsL();
    TInt childCount = children.Count();    

    CSenElement* pNextChild;
    TInt i=0;

    while (i < childCount)
    {
        pNextChild = children[i];
        TPtrC8 localName = pNextChild->LocalName();
        ProcessPolicyReferenceL(pNextChild, aRegistry);
        i++;
    }
    
  return NULL;  
}