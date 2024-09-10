/*
 * Checks that all variables referenced in FunctionDefinition bodies are
 * bound variables (function arguments).
 */
void
FunctionDefinitionVars::check_ (const Model& m, const FunctionDefinition& fd)
{
  if ( fd.getLevel() == 1         ) return;
  if ( !fd.isSetMath()            ) return;
  if ( fd.getBody()  == NULL      ) return;
  //if (  fd.getNumArguments() == 0 ) return;


  List* variables = fd.getBody()->getListOfNodes( ASTNode_isName );


  for (unsigned int n = 0; n < variables->getSize(); ++n)
  {
    ASTNode* node = static_cast<ASTNode*>( variables->get(n) );
    string   name = node->getName() ? node->getName() : "";

    if ( fd.getArgument(name) == NULL ) 
    {
      /* if this is the csymbol time - technically it is allowed 
       * in L2v1 and L2v2
       */
      if (node->getType() == AST_NAME_TIME)
      {
        if (fd.getLevel() > 2
          || (fd.getLevel() == 2 && fd.getVersion() > 2))
        {
          logUndefined(fd, name);
        }
      }
      else
      {
        logUndefined(fd, name);
      }
    }
  }

  if ((m.getLevel() == 2 && m.getVersion() == 5)
    || (m.getLevel() == 3 && m.getVersion() > 1))
  { // check we dont use delay csymbol
    delete variables;
    variables = fd.getBody()->getListOfNodes( ASTNode_isFunction );
    
    for (unsigned int n = 0; n < variables->getSize(); ++n)
    {
      ASTNode* node = static_cast<ASTNode*>( variables->get(n) );

      if (node->getType() == AST_FUNCTION_DELAY)
      {
        logUndefined(fd, node->getName());
      }
    }
  }


  //Check we don't use a function defined in a plugin (like rateOf)
  delete variables;
  variables = fd.getBody()->getListOfNodes(ASTNode_isFunction);

  for (unsigned int n = 0; n < variables->getSize(); ++n)
  {
    ASTNode* node = static_cast<ASTNode*>(variables->get(n));

    const ASTBasePlugin* plugin = node->getASTPlugin(node->getType());
    if (plugin != NULL)
    {
      if (plugin->allowedInFunctionDefinition(node->getType()) == 0)
      {
        logUndefined(fd, node->getName());
      }
    }
  }
  delete variables;
}