/**
  * Checks that the functionDefinition referred to by a <ci> element 
  * has the appropriate number of arguments.
  *
  * If not, an error message is logged.
  */
void 
FunctionNoArgsMathCheck::checkNumArgs (const Model& m, const ASTNode& node, 
                                                const SBase & sb)
{
  /* this rule was only introduced level 2 version 4 */
  if (m.getLevel() > 2 || (m.getLevel() == 2 && m.getVersion() > 3))
  {
    if (m.getFunctionDefinition(node.getName()) != NULL)
    {
      /* functiondefinition math */
      const ASTNode * fdMath = m.getFunctionDefinition(node.getName())->getMath();
      if (fdMath != NULL)
      {
      /* We have a definition for this function.  Does the defined number
	        of arguments equal the number used here? */

        if (node.getNumChildren() != m.getFunctionDefinition(node.getName())->getNumArguments())
	      {
          logMathConflict(node, sb);
	      }
      }

    }
  }
}