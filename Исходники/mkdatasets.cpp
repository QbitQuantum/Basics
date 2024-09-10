void MakeLJNets(TStr InFNm, TStr OutFNm, TStr Desc){
  TStrHash<TInt> StrSet(Mega(1), true);
  for (int i = 1; i < 13; i++){
    TStr tmp = "";  
      
    if (i < 10)
      tmp = InFNm + "ljgraph.0" + TInt::GetStr(i);  
    else
      tmp = InFNm + "ljgraph." + TInt::GetStr(i);  
  
    printf("%s\n",tmp());

    TSsParser Ss(tmp, ssfTabSep);
    PNGraph Graph = TNGraph::New();
      
    while (Ss.Next()) {
      const int SrcNId = StrSet.AddKey(Ss[0]);
      if (! Graph->IsNode(SrcNId)) { Graph->AddNode(SrcNId); }
      for (int dst = 2; dst < Ss.Len(); dst++) {
        TStr ls,rs;
          ((TStr)Ss[dst]).SplitOnCh(ls,' ',rs);
        if (ls == ">"){
          const int DstNId = StrSet.AddKey(rs);
          if (! Graph->IsNode(DstNId)) { Graph->AddNode(DstNId); }
          Graph->AddEdge(SrcNId, DstNId);
        }
      }
    }
    if (i < 10)
      OutFNm = "soc-lj-friends.0"+TInt::GetStr(i);
    else
      OutFNm = "soc-lj-friends."+TInt::GetStr(i);
  
    PrintGraphStatTable(Graph, OutFNm, Desc);
  }
}