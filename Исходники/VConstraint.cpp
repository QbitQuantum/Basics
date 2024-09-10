/*
 * Logs a constraint failure to the validator for the given SBML object.
 * The parameter message is used instead of the constraint's member
 * variable msg.
 */
void
VConstraint::logFailure (const SBase& object, const std::string& message)
{
  if (&object == NULL || &message == NULL) return;

  SBMLError error = SBMLError( mId, object.getLevel(), object.getVersion(),
			       message, object.getLine(), object.getColumn() );

  if (error.getSeverity() != LIBSBML_SEV_NOT_APPLICABLE)
    mValidator.logFailure(error);

/*    ( SBMLError( mId, object.getLevel(), object.getVersion(),
                 message, object.getLine(), object.getColumn(),
                 LIBSBML_SEV_ERROR, LIBSBML_CAT_SBML ));*/

}