// returns the output field
Field* ProtoInterpreter::sexp_to_graph(SExpr* s, AM* space, Env *env) {
  V3 << "Interpret: " << ce2s(s) << " in " << ce2s(space) << endl;
  if(s->isSymbol()) {
    // All other symbols are looked up in the environment
    CompilationElement* elt = env->lookup(dynamic_cast<SE_Symbol &>(*s).name);
    if(elt==NULL) { 
      V4 << "Symbolic literal?\n";
      ProtoType* val = symbolic_literal(dynamic_cast<SE_Symbol &>(*s).name);
      if(val) { V4 << "- Yes\n"; return dfg->add_literal(val,space,s); }
      return field_err(s,space,"Couldn't find definition of "+s->to_str());
    } else if(elt->isA("Field")) { 
      V4 << "Found field: " << ce2s(elt) << endl;
      Field* f = &dynamic_cast<Field &>(*elt);
      if(f->domain==space) { return f;
      } if(f->domain->child_of(space)) {
        ierror(s,"Direct reference to child space in parent:"+ce2s(s));
      } else { // implicit restriction
        OI *oi = new OperatorInstance(s,Env::core_op("restrict"),space);
        oi->add_input(f);
        if(space->selector) oi->add_input(space->selector); 
        return oi->output;
      }
    } else if(elt->isA("Operator")) {
      V4 << "Lambda literal: " << ce2s(elt) << endl;
      return dfg->add_literal(new ProtoLambda(&dynamic_cast<Operator &>(*elt)),
          space, s);
    } else if(elt->isA("MacroSymbol")) {
      V4 << "Macro: " << ce2s(elt) << endl;
      return
        sexp_to_graph(dynamic_cast<MacroSymbol &>(*elt).pattern,space,env);
    } else return field_err(s,space,"Can't interpret "+elt->type_of()+" "+
                            s->to_str()+" as field");
  } else if(s->isScalar()) { // Numbers are literals
    V4 << "Numeric literal.\n";
    return
      dfg->add_literal(new ProtoScalar(dynamic_cast<SE_Scalar &>(*s).value),
          space,s);
  } else { // it must be a list
    // Lists are special forms or function applicatios
    SE_List* sl = &dynamic_cast<SE_List &>(*s);
    if(sl->len()==0) return field_err(sl,space,"Expression has no members"); 
    if(sl->op()->isSymbol()) { 
      // check if it's a special form
      string opname = dynamic_cast<SE_Symbol &>(*sl->op()).name;
      if(opname=="let") { return let_to_graph(sl,space,env,false);
      } else if(opname=="let*") { return let_to_graph(sl,space,env,true);
      } else if(opname=="all") { // evaluate children, returning last field
        Field* last=NULL;
        V4 << "Found 'all' construct\n";
        for(int j=1;j<sl->len();j++) last = sexp_to_graph((*sl)[j],space,env);
        return last;
      } else if(opname=="restrict"){ 
        return restrict_to_graph(sl,space,env);
      } else if(opname=="def" && sl->len()==3) { // variable definition
        SExpr *def=(*sl)[1], *exp=(*sl)[2];
        if(!def->isSymbol())
          return field_err(sl,space,"def name not a symbol: "+def->to_str());
        Field* f = sexp_to_graph(exp,space,env);
        env->force_bind(dynamic_cast<SE_Symbol &>(*def).name,f);
        V4 << "Defined variable: " << ce2s(f) << endl;
        return f;
      } else if(opname=="def" || opname=="primitive" || 
                opname=="lambda" || opname=="fun") {
        Operator* op = sexp_to_op(s,env);
        if(!(opname=="lambda" || opname=="fun")) return NULL;
        return dfg->add_literal(new ProtoLambda(op),space,s);
      } else if(opname=="annotate") {
        SE_List_iter li(sl); li.get_next(); // make iterator, discard op
        string name = li.get_token("operator name");
        CE* p = env->lookup(name);
        if(p==NULL) {
          compile_error(sl,"Can't find primitve '"+name+"' to annotate");
        } else if(!p->isA("Primitive")) {
          compile_error(sl,"Can't annotate '"+name+"': not a primitive");
        } else {
          // add in attributes
          parse_primitive_attributes(&li, &dynamic_cast<Primitive &>(*p));
        }
        return NULL; // annotations are like primitives: nothing returned
      } else if(opname=="letfed" || opname=="letfed+") {
        return letfed_to_graph(sl,space,env,opname=="letfed");
      } else if(opname=="macro") {
        V4 << "Defining macro\n";
        sexp_to_macro(sl,env);
        return NULL;
      } else if(opname=="include") {
        for(int j=1;j<sl->len();j++) {
          SExpr *ex = (*sl)[j];
          V4 << "Including file: "<<ce2s(ex)<<endl;
          if(ex->isSymbol())
            interpret_file(dynamic_cast<SE_Symbol &>(*ex).name);
          else compile_error(ex,"File name "+ex->to_str()+" is not a symbol");
        }
        return NULL;
      } else if(opname=="quote") {
        if(sl->len()!=2) 
          return field_err(sl,space,"Quote requires an argument: "+s->to_str());
        V4 << "Creating quote literal\n";
        return dfg->add_literal(quote_to_literal_type((*sl)[1]),space,s);
      } else if(opname=="quasiquote") {
        return field_err(sl,space,"Quasiquote only allowed in macros: "+sl->to_str());
      }
      // check if it's a macro
      CompilationElement* ce = env->lookup(opname);
      if(ce && ce->isA("Macro")) {
        V4 << "Applying macro\n";
        SExpr* new_expr;
        if(ce->isA("MacroOperator")) {
          new_expr = expand_macro(&dynamic_cast<MacroOperator &>(*ce),sl);
          if(new_expr->attributes.count("DUMMY")) // Mark of a failure
            return field_err(s,space,"Macro expansion failed on "+s->to_str());
        } else { // it's a MacroSymbol
          new_expr = sl->copy();
          dynamic_cast<SE_List &>(*new_expr).children[0]
            = dynamic_cast<Macro &>(*ce).pattern;
        }
        return sexp_to_graph(new_expr,space,env);
      }
    }
    // if we didn't return yet, it's an ordinary composite expression
    Operator *op = sexp_to_op(sl->op(),env);
    if(op->marked(":protected"))
      compile_warn(op,"operator '"+op->name+"' not intended for direct use.");
    OperatorInstance *oi = new OperatorInstance(s,op,space);
    for(vector<SExpr*>::iterator it=sl->args(); it!=sl->children.end(); it++) {
      Field* sub = sexp_to_graph(*it,space,env);
      // operator defs, primitives, and macros return null & are ignored
      if(sub) oi->add_input(sub);
    }
    if(!op->signature->legal_length(oi->inputs.size())) {
      compile_error(s,"Called "+ce2s(op)+" with "+i2s(oi->inputs.size())+
                    " arguments; it requires "+op->signature->num_arg_str());
    }
    V4 << "Added operator "<<ce2s(oi)<<endl;
    return oi->output;
  }
  ierror("Fell through sexp_to_graph w/o returning for: "+s->to_str());
}