 void getNodeParamDcl (basl::Nonterm & nonterm, SpecSel & dcl_spec_sel, smtc::CvType & dcl_cv_type, smtc::NamePtr & name)
 {
   SpecSel decl_spec_sel;
   smtc::CvType cv_type;
   nonterm.accept (GetNodeDcl (decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name));
 }