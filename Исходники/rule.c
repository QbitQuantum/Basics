/* This functions looks at the given message and checks if it matches the
 * provided filter condition.
 */
static rsRetVal
shouldProcessThisMessage(rule_t *pRule, msg_t *pMsg, int *bProcessMsg)
{
	DEFiRet;
	unsigned short pbMustBeFreed;
	uchar *pszPropVal;
	int bRet = 0;
	size_t propLen;
	vm_t *pVM = NULL;
	var_t *pResult = NULL;

	ISOBJ_TYPE_assert(pRule, rule);
	assert(pMsg != NULL);

	/* we first have a look at the global, BSD-style block filters (for tag
	 * and host). Only if they match, we evaluate the actual filter.
	 * rgerhards, 2005-10-18
	 */
	if(pRule->eHostnameCmpMode == HN_NO_COMP) {
		/* EMPTY BY INTENSION - we check this value first, because
		 * it is the one most often used, so this saves us time!
		 */
	} else if(pRule->eHostnameCmpMode == HN_COMP_MATCH) {
		if(rsCStrSzStrCmp(pRule->pCSHostnameComp, (uchar*) getHOSTNAME(pMsg), getHOSTNAMELen(pMsg))) {
			/* not equal, so we are already done... */
			dbgprintf("hostname filter '+%s' does not match '%s'\n", 
				rsCStrGetSzStrNoNULL(pRule->pCSHostnameComp), getHOSTNAME(pMsg));
			FINALIZE;
		}
	} else { /* must be -hostname */
		if(!rsCStrSzStrCmp(pRule->pCSHostnameComp, (uchar*) getHOSTNAME(pMsg), getHOSTNAMELen(pMsg))) {
			/* not equal, so we are already done... */
			dbgprintf("hostname filter '-%s' does not match '%s'\n", 
				rsCStrGetSzStrNoNULL(pRule->pCSHostnameComp), getHOSTNAME(pMsg));
			FINALIZE;
		}
	}
	
	if(pRule->pCSProgNameComp != NULL) {
		int bInv = 0, bEqv = 0, offset = 0;
		if(*(rsCStrGetSzStrNoNULL(pRule->pCSProgNameComp)) == '-') {
			if(*(rsCStrGetSzStrNoNULL(pRule->pCSProgNameComp) + 1) == '-')
				offset = 1;
			else {
				bInv = 1;
				offset = 1;
			}
		}
		if(!rsCStrOffsetSzStrCmp(pRule->pCSProgNameComp, offset,
			(uchar*) getProgramName(pMsg, LOCK_MUTEX), getProgramNameLen(pMsg, LOCK_MUTEX)))
			bEqv = 1;

		if((!bEqv && !bInv) || (bEqv && bInv)) {
			/* not equal or inverted selection, so we are already done... */
			DBGPRINTF("programname filter '%s' does not match '%s'\n", 
				rsCStrGetSzStrNoNULL(pRule->pCSProgNameComp), getProgramName(pMsg, LOCK_MUTEX));
			FINALIZE;
		}
	}
	
	/* done with the BSD-style block filters */

	if(pRule->f_filter_type == FILTER_PRI) {
		/* skip messages that are incorrect priority */
dbgprintf("testing filter, f_pmask %d\n", pRule->f_filterData.f_pmask[pMsg->iFacility]);
		if ( (pRule->f_filterData.f_pmask[pMsg->iFacility] == TABLE_NOPRI) || \
		    ((pRule->f_filterData.f_pmask[pMsg->iFacility] & (1<<pMsg->iSeverity)) == 0) )
			bRet = 0;
		else
			bRet = 1;
	} else if(pRule->f_filter_type == FILTER_EXPR) {
		CHKiRet(vm.Construct(&pVM));
		CHKiRet(vm.ConstructFinalize(pVM));
		CHKiRet(vm.SetMsg(pVM, pMsg));
		CHKiRet(vm.ExecProg(pVM, pRule->f_filterData.f_expr->pVmprg));
		CHKiRet(vm.PopBoolFromStack(pVM, &pResult));
		dbgprintf("result of expression evaluation: %lld\n", pResult->val.num);
		/* VM is destructed on function exit */
		bRet = (pResult->val.num) ? 1 : 0;
	} else {
		assert(pRule->f_filter_type == FILTER_PROP); /* assert() just in case... */
		pszPropVal = MsgGetProp(pMsg, NULL, pRule->f_filterData.prop.propID, &propLen, &pbMustBeFreed);

		/* Now do the compares (short list currently ;)) */
		switch(pRule->f_filterData.prop.operation ) {
		case FIOP_CONTAINS:
			if(rsCStrLocateInSzStr(pRule->f_filterData.prop.pCSCompValue, (uchar*) pszPropVal) != -1)
				bRet = 1;
			break;
		case FIOP_ISEQUAL:
			if(rsCStrSzStrCmp(pRule->f_filterData.prop.pCSCompValue,
					  pszPropVal, ustrlen(pszPropVal)) == 0)
				bRet = 1; /* process message! */
			break;
		case FIOP_STARTSWITH:
			if(rsCStrSzStrStartsWithCStr(pRule->f_filterData.prop.pCSCompValue,
					  pszPropVal, ustrlen(pszPropVal)) == 0)
				bRet = 1; /* process message! */
			break;
		case FIOP_REGEX:
			if(rsCStrSzStrMatchRegex(pRule->f_filterData.prop.pCSCompValue,
					(unsigned char*) pszPropVal, 0, &pRule->f_filterData.prop.regex_cache) == RS_RET_OK)
				bRet = 1;
			break;
		case FIOP_EREREGEX:
			if(rsCStrSzStrMatchRegex(pRule->f_filterData.prop.pCSCompValue,
					  (unsigned char*) pszPropVal, 1, &pRule->f_filterData.prop.regex_cache) == RS_RET_OK)
				bRet = 1;
			break;
		default:
			/* here, it handles NOP (for performance reasons) */
			assert(pRule->f_filterData.prop.operation == FIOP_NOP);
			bRet = 1; /* as good as any other default ;) */
			break;
		}

		/* now check if the value must be negated */
		if(pRule->f_filterData.prop.isNegated)
			bRet = (bRet == 1) ?  0 : 1;

		if(Debug) {
			dbgprintf("Filter: check for property '%s' (value '%s') ",
			        propIDToName(pRule->f_filterData.prop.propID), pszPropVal);
			if(pRule->f_filterData.prop.isNegated)
				dbgprintf("NOT ");
			dbgprintf("%s '%s': %s\n",
			       getFIOPName(pRule->f_filterData.prop.operation),
			       rsCStrGetSzStrNoNULL(pRule->f_filterData.prop.pCSCompValue),
			       bRet ? "TRUE" : "FALSE");
		}

		/* cleanup */
		if(pbMustBeFreed)
			free(pszPropVal);
	}

finalize_it:
	/* destruct in any case, not just on error, but it makes error handling much easier */
	if(pVM != NULL)
		vm.Destruct(&pVM);

	if(pResult != NULL)
		var.Destruct(&pResult);

	*bProcessMsg = bRet;
	RETiRet;
}