bool AlgebraManager::findOperator(const string& name,
                                  const ListExpr argList,
                                  ListExpr& resultList,
                                  int& algId,
                                  int& opId,
                                  int& funId){

   ListExpr typeError = nl->SymbolAtom(Symbol::TYPEERROR());

   NestedList* nl_orig = NList::getNLRef();
   NList::setNLRef(nl);

   int mode = 0;  // normal mode, search for matching arglist
   string algName ="";
   if(nl->HasLength(argList,2)){
     if(nl->IsEqual(nl->First(argList),"algebra")
        && nl->AtomType(nl->Second(argList)==SymbolType)){
        mode = 1; // search within a specific algebra
        algName = nl->SymbolValue(nl->Second(argList));
        stringutils::toLower(algName);
        if(algName=="all"){
           mode = 2; // search all algebras, return first hit
        }
     } 
   }
   for(unsigned int a=0;a<algebra.size();a++){
     Algebra* alg = algebra[a];
     if(alg!=0){
       string an = algebraNames[a];
       stringutils::toLower(an);
       if(mode==0 || mode==2 || an==algName){
         for(int o=0; o< alg->GetNumOps(); o++){
           Operator* op = alg->GetOperator(o);
           if(op->GetName() == name){
             if(mode==0){
               try{
                  ListExpr res = op->CallTypeMapping(argList);
                  if(!nl->Equal(res,typeError)){ //  appropriate operator found
                     algId = a;
                     opId = o;
                     funId = op->Select(argList);
                     resultList = res;
                     NList::setNLRef(nl_orig);
                     return true;
                  }
               } catch (...){
                  cerr << "Problem in Typemapping of operator " << op->GetName()
                       << " in Algebra" << GetAlgebraName(a) << endl;
                  cerr << "Throws an exception when called with "
                       << nl->ToString(argList) << endl;
               }
            } else { // mode <>0
                algId = a;
                opId = o;
                funId = 0;
                resultList = nl->TheEmptyList();
                NList::setNLRef(nl_orig);
                return true;
            }
          }
        }
      } // fitting algebra name
    }
  }
  algId = 0;
  opId = 0;
  resultList = nl->TheEmptyList();
  NList::setNLRef(nl_orig);
  return false;
}