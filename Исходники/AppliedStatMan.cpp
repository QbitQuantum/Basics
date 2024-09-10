// Get the scan expression for given jbbc
// if jbbc is not a scan or predIdSet is NULL
// then the original JBBC expression is returned
RelExpr * AppliedStatMan::getExprForCANodeId(
          CANodeId jbbc,
          const EstLogPropSharedPtr &inLP,
          const ValueIdSet * predIdSet)
{
  RelExpr * jbbcExpr = NULL;
  
  // should not happen but a check just in case
  CCMPASSERT(jbbc.getNodeAnalysis());
  
  //if specified by the user apply those predicates,
  // else apply predicates in the original expr
  NodeAnalysis * jbbcNode = jbbc.getNodeAnalysis();

  TableAnalysis * tableAnalysis = jbbcNode->getTableAnalysis();

  if (tableAnalysis && predIdSet)
  {
    TableDesc * tableDesc = tableAnalysis->getTableDesc();
    const CorrName& name = tableDesc->getNATable()->getTableName();

    Scan *scanExpr = new STMTHEAP Scan(name, tableDesc, REL_SCAN, STMTHEAP);
    scanExpr->setBaseCardinality(MIN_ONE (tableDesc->getNATable()->getEstRowCount())) ;

    GroupAttributes * gaExpr = new STMTHEAP GroupAttributes();

    scanExpr->setSelectionPredicates(*predIdSet);

    ValueIdSet requiredOutputs = jbbc.getNodeAnalysis()->\
  getOriginalExpr()->getGroupAttr()->getCharacteristicOutputs();

    gaExpr->setCharacteristicOutputs(requiredOutputs);

    ValueIdSet requiredInputs = jbbc.getNodeAnalysis()->\
  getOriginalExpr()->getGroupAttr()->getCharacteristicInputs();

    gaExpr->setCharacteristicInputs(requiredInputs);
    
    scanExpr->setGroupAttr(gaExpr);
    gaExpr->setLogExprForSynthesis(scanExpr);
    scanExpr->synthLogProp();
    jbbcExpr = scanExpr;
  }
  else
  {
    NodeAnalysis * nodeAnalysis = jbbc.getNodeAnalysis();

    RelExpr * relExpr = nodeAnalysis->getModifiedExpr();

    if (relExpr == NULL)
      relExpr = nodeAnalysis->getOriginalExpr();

    jbbcExpr = relExpr;
  }

  return jbbcExpr;
} // getExprForCANodeId