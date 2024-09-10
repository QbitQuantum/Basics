int
i_parseSequence(DCM_OBJECT ** object)
{

    DCM_ELEMENT e;
    LST_HEAD *l;
    CONDITION cond;
    int index;
    SQ_TYPE type;
    SQ_REFRESULTSSOPINSTANCEUID *results;
    SQ_REQINTERPRETATIONAPPROVER *approver;
    SQ_REQPROCEDURECODE *diagnosis;
    void *pointer;

    static DCM_MAP_SQ sequences[] = {
	{DCM_IDREFERENCEDRESULTSSEQ, SQ_K_REFRESULTSSOPINSTANCEUID,
	HIS_K_INTRRSEQUENCE},
	{DCM_RESINTERPAPPROVERSEQUENCE, SQ_K_REQINTERPRETATIONAPPROVER,
	HIS_K_INTIAPPSEQUENCE},
	{DCM_RESDIAGNOSISCODESEQ, SQ_K_REQDIAGNOSISCODE,
	HIS_K_INTIDCSEQUENCE},
    };

    for (index = 0; index < (int) DIM_OF(sequences); index++) {
	e.tag = sequences[index].tag;
	cond = DCM_GetSequenceList(object, e.tag, &e.d.sq);
	if (cond != DCM_NORMAL) {
	    if (cond != DCM_ELEMENTNOTFOUND)
		return -1;
	} else {
	    cond = SQ_ParseSequence(&e, &type, &l);
	    if (cond != SQ_NORMAL || type != sequences[index].type)
		return -2;
	    p.Update_Flag |= sequences[index].his_field;
	    pointer = LST_Head(&l);
	    if (pointer != NULL)
		LST_Position(&l, pointer);
	    while (pointer != NULL) {
		switch (sequences[index].tag) {
		case DCM_IDREFERENCEDRESULTSSEQ:
		    strcpy(p.RRSequence[p.RRSequenceCount],
			   ((SQ_REFRESULTSSOPINSTANCEUID *)
			    pointer)->referencedSOPInstanceUID);
		    p.RRSequenceCount++;
		    break;
		case DCM_RESINTERPAPPROVERSEQUENCE:
		    strcpy(p.IApprover[p.IApprovalSequenceCount],
			   ((SQ_REQINTERPRETATIONAPPROVER *)
			    pointer)->physiciansApproving);
		    strcpy(p.IADates[p.IApprovalSequenceCount],
			   ((SQ_REQINTERPRETATIONAPPROVER *)
			    pointer)->approvalDates);
		    strcpy(p.IATimes[p.IApprovalSequenceCount],
			   ((SQ_REQINTERPRETATIONAPPROVER *)
			    pointer)->approvalTimes);
		    p.IApprovalSequenceCount++;
		    break;
		case DCM_RESDIAGNOSISCODESEQ:
		    strcpy(p.IDCSequence[p.IDCSequenceCount].
			   CodeValue,
			   ((SQ_REQPROCEDURECODE *) pointer)->codeValue);
		    strcpy(p.IDCSequence[p.IDCSequenceCount].
			   CodingSchemeDesignator,
			   ((SQ_REQPROCEDURECODE *) pointer)->codingSchemeDesignator);
		    strcpy(p.IDCSequence[p.IDCSequenceCount].
			   CodeMeaning,
			   ((SQ_REQPROCEDURECODE *) pointer)->codeMeaning);
		    p.IDCSequenceCount++;
		    break;
		}
		pointer = LST_Next(&l);
	    }
	}
    }
    return 0;
/*
    e.tag = DCM_IDREFERENCEDRESULTSSEQ;

    cond = DCM_GetSequenceList(object, e.tag, &e.d.sq);
    if (cond == DCM_ELEMENTNOTFOUND)
	return 0;
    else if (cond != DCM_NORMAL)
	return -1;

    cond = SQ_ParseSequence(&e, &type, &l);
    if (cond != SQ_NORMAL)
	return -2;
    if (type == SQ_K_REFRESULTSSOPINSTANCEUID) {
	p.Update_Flag |= HIS_K_INTRRSEQUENCE;
	results = LST_Head(&l);
	if (results != NULL)
	    LST_Position(&l, results);
	while (results != NULL) {
	    strcpy(p.RRSequence[p.RRSequenceCount],
		   results->referencedSOPInstanceUID);
	    ++p.RRSequenceCount;
	    results = LST_Next(&l);
	}
    }
*/
}