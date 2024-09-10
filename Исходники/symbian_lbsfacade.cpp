QTM_BEGIN_NAMESPACE

CSelfManagingPsy::CSelfManagingPsy(TPositionModuleInfo* aPsy, CPsyContainer *aContainer,
                                   MPsyRequestCallback* aRequestCallback, TPositionInfoBase &aPos)
        : CActive(EPriorityNormal), iContainer(aContainer), iPositioner(NULL),
        iPsyModInfo(aPsy), iRequestCallback(aRequestCallback), iPosInfo(aPos),
        iClientRequestActive(EFalse), iPsyAvailabilityStatus(EFalse)
{
    TBuf<20> psyName;
    iPsyModInfo->GetModuleName(psyName);
    QString qPsyName((QChar*)psyName.Ptr(), psyName.Length());
    iPsyName = qPsyName;
}