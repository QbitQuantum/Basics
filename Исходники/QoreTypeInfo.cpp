void QoreTypeInfo::doNonBooleanWarning(const char* preface) const {
   QoreStringNode* desc = new QoreStringNode(preface);
   getThisType(*desc);
   desc->sprintf(", which does not evaluate to a numeric or boolean type, therefore will always evaluate to False at runtime");
   qore_program_private::makeParseWarning(getProgram(), QP_WARN_INVALID_OPERATION, "INVALID-OPERATION", desc);
}