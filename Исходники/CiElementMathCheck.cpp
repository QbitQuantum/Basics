/**
 * @return the error message to use when logging constraint violations.
 * This method is called by logFailure.
 *
 * Returns a message that the given id and its corresponding object are
 * in  conflict with an object previously defined.
 */
const string
CiElementMathCheck::getMessage (const ASTNode& node, const SBase& object)
{

  ostringstream msg;

  //msg << getPreamble();
  char * formula = SBML_formulaToString(&node);
  msg << "\nThe formula '" << formula;
  msg << "' in the " << getFieldname() << " element of the " << getTypename(object);
  if (object.getLevel() == 2 && object.getVersion() == 1)
    msg << " uses '" << node.getName() << "' that is not the id of a species/compartment/parameter.";
  else
    msg << " uses '" << node.getName() << "' that is not the id of a species/compartment/parameter/reaction.";
  safe_free(formula);

  return msg.str();
}