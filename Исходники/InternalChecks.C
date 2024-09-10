void checkLanguageRestrictor(int argc, char *argv[]) {
  // Build the AST used by ROSE
  SgProject* sageProject = frontend(argc,argv);
  LanguageRestrictor lr;
  LanguageRestrictor::VariantSet vs= lr.computeVariantSetOfProvidedAst(sageProject);
  for(LanguageRestrictor::VariantSet::iterator i=vs.begin();i!=vs.end();++i) {
    cout << "VARIANT: "<<lr.variantToString(*i)<<endl;
  }
  cout <<endl;
  lr.allowAstNodesRequiredForEmptyProgram();
  vs=lr.getAllowedAstNodeVariantSet();
  for(LanguageRestrictor::VariantSet::iterator i=vs.begin();i!=vs.end();++i) {
    cout << "VARIANT: "<<lr.variantToString(*i)<<endl;
  }
}