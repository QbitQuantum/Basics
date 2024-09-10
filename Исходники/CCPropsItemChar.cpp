void CCPropsItemChar::SetPropertyNum(int iPropIndex, PropertyValNum_t iVal, CObjBase* pLinkedObj, RESDISPLAY_VERSION iLimitToExpansion, bool fDeleteZero)
{
    ADDTOCALLSTACK("CCPropsItemChar::SetPropertyNum");
    ASSERT(!IsPropertyStr(iPropIndex));
    ASSERT((iLimitToExpansion >= RDS_PRET2A) && (iLimitToExpansion < RDS_QTY));

    if ((fDeleteZero && (iVal == 0)) || (_iPropertyExpansion[iPropIndex] > iLimitToExpansion))
    {
        if (0 == _mPropsNum.erase(iPropIndex))
            return; // I didn't have this property, so avoid further processing.
    }
    else
        _mPropsNum[iPropIndex] = iVal;

    if (!pLinkedObj)
        return;

    // Do stuff to the pLinkedObj
    switch (iPropIndex)
    {
        case PROPITCH_WEIGHTREDUCTION:
        {
            CItem *pItemLink = static_cast<CItem*>(pLinkedObj);
            int oldweight = pItemLink->GetWeight();
            CContainer * pCont = dynamic_cast <CContainer*> (pItemLink->GetParent());
            if (pCont)
            {
                ASSERT(pItemLink->IsItemEquipped() || pItemLink->IsItemInContainer());
                pCont->OnWeightChange(pItemLink->GetWeight() - oldweight);
                pLinkedObj->UpdatePropertyFlag();
            }
            break;
        }

        //default:
        //    pLinkedObj->UpdatePropertyFlag();
        //    break;
    }
}