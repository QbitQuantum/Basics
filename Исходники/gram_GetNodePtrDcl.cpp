 void getNodePtrDcl (basl::Nonterm & nonterm, smtc::CvType & cv_type)
 {
   nonterm.accept (GetNodePtrDcl (cv_type));
 }