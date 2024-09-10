 TPIDs evalSingles(DescrFamily const & pF, Value * pValues)
 {
     // Evaluate a join of pF.mSingles with pValues (assumed to match the count of conditions in pF).
     TPIDs lResult;
     CmvautoPtr<IStmt> lStmt(mSession->createStmt());
     size_t i;
     unsigned char lVars[255];
     for (i = 0; i < pF.mDescr.size(); i++)
     {       
         SourceSpec lCS;
         lCS.objectID = pF.mSingles[i];
         lCS.params = &pValues[i];
         lCS.nParams = 1;
         lVars[i] = lStmt->addVariable(&lCS, 1);
     }
     lStmt->setOp(lVars, pF.mDescr.size(), QRY_INTERSECT);
     mLogger.out() << "singles query " << std::endl << lStmt->toString() << std::endl;
     ICursor* lC = NULL;
     TVERIFYRC(lStmt->execute(&lC));
     CmvautoPtr<ICursor> lCursor(lC);
     if (!lCursor.IsValid())
         { TVERIFY2(false, "Invalid/NULL cursor!"); return lResult; }
     IPIN * lP;
     while (NULL != (lP = lCursor->next()))
     {
         lResult.insert(lP->getPID());
         //printf("%s%x\n", "evalsingles : pid : ", lP->getPID());
         lP->destroy();
     }
     return lResult;
 }