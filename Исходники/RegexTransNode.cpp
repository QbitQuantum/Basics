// get string representation (for %n and %N), foff is for multi-line formatting offset, -1 = no line breaks
// the ExceptionSink is only needed for QoreObject where a method may be executed
// use the QoreNodeAsStringHelper class (defined in QoreStringNode.h) instead of using these functions directly
// returns -1 for exception raised, 0 = OK
int RegexTransNode::getAsString(QoreString &str, int foff, ExceptionSink *xsink) const {
   str.sprintf("transliteration expression (%p)", this);
   return 0;
}