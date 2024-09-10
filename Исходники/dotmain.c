static void DOT_RunRequest(WindoW w, BioseqPtr qbsp, BioseqPtr sbsp, DOTStartDataPtr sdata){
  Char            str1[100]={""}, str2[100]={""};
  SeqLocPtr       slp1=NULL, slp2=NULL;
  SeqAlignPtr     sap = NULL;
  DOTMainDataPtr  mip;
  DOTAlignInfoPtr alp=NULL;
  SCP_ResultPtr    scp=NULL;


  MemSet((Pointer)str1, '\0', sizeof(str1));
  GetTitle (sdata->querystart,  str1,  sizeof(str1));
  if (StringCmp(str1, "All")==0)
     q_start=0; 
  else
    q_start=DOT_GetValue(sdata->querystart);
  MemSet((Pointer)str1, '\0', sizeof(str1));
  GetTitle(sdata->querystop, str1, sizeof(str1));
  if (StringCmp(str1, "All")==0)
    q_stop=qbsp->length-1;
  else
      q_stop=DOT_GetValue(sdata->querystop);
  MemSet((Pointer)str1, '\0', sizeof(str1));
  GetTitle(sdata->subjectstart, str1, sizeof(str1));
  if (StringCmp(str1, "All")==0)
    s_start=0;
  else
    s_start=DOT_GetValue(sdata->subjectstart);
  MemSet((Pointer)str1, '\0', sizeof(str1));
  GetTitle(sdata->subjectstop, str1, sizeof(str1));
  if (StringCmp(str1, "All")==0)
    s_stop=sbsp->length-1;
  else
    s_stop=DOT_GetValue(sdata->subjectstop);
  if (qbsp->length<q_start || sbsp->length<s_start || q_start>q_stop|| s_start>s_stop || s_start<0 || q_start<0)
    {
      ErrPostEx(SEV_FATAL, 1, 0, "Bad sequence offset values");
      return;
    }
  
  if (GetStatus(sdata->reg_blast)){
    if (GetValue(sdata->plusorminus) == 1){
      slp1 = NULL;
      slp2 = NULL;
    }
    else {
      slp1= SeqLocIntNew(q_start, q_stop, 1, qbsp->id);
      if (GetValue(sdata->plusorminus) == 2)
        slp2 = SeqLocIntNew(s_start, s_stop, 1, sbsp->id);
      else
        slp2 = SeqLocIntNew(s_start, s_stop,2, sbsp->id);
    }
  }
  else if (GetStatus(sdata->auto_blast)){
    slp1 = SeqLocIntNew(q_start, q_stop, 1, qbsp->id);
    slp2 = SeqLocIntNew(s_start, s_stop,1, sbsp->id);
  }
  else if (GetStatus(sdata->dot)){
    slp1= SeqLocIntNew(q_start, q_stop, 1, qbsp->id);
    if (GetValue(sdata->plusorminus) == 1)
      slp2 = SeqLocIntNew(s_start, s_stop,1, sbsp->id);
    else
      slp2 = SeqLocIntNew(s_start, s_stop, 2, sbsp->id);
  }
  
  if (GetStatus(sdata->reg_blast)){
    sap = DOT_RunBlast2Seqs(qbsp, sbsp, slp1, slp2, sdata);
    if (sap == NULL){
      Message (MSG_OK, "Blast 2 Seqs -  returned NULL");
      DOT_quitProgram(NULL);
      return;
    }
    DOT_AlignPlotGivenSeqAlign(sap);
  }
  else if (GetStatus(sdata->dot) || GetStatus(sdata->auto_blast)){
    
    word_size=DOT_GetValue(sdata->wordsize);
    tree_limit=DOT_GetValue(sdata->hitsize);
    
    if (GetStatus(sdata->dot)){
      mip=DOT_CreateAndStorebyLoc(slp1, slp2, word_size, tree_limit);
      if (mip == NULL){
        Message (MSG_OK, "Dot Plot analysis returned NULL");
        DOT_quitProgram(NULL);
        return;
      }
      Remove(sdata->hStart);
      Remove(w);
      DOT_MakeMainViewer(mip, alp);
    }
    else if (GetStatus(sdata->auto_blast)){
      scp=SCP_CompareOrderOrganizeBioseqs(qbsp, sbsp, slp1, slp2, "blastn", word_size, tree_limit);
      if (scp == NULL){
        Message (MSG_OK, "Blast 2 Seqs - return NULL");
        DOT_quitProgram(NULL);
        return;
      }
      DOT_AlignPlotGivenScp(scp);
    } 
  } 
}