void appendQoreString(java::lang::String *jstr, QoreString &qstr) {
   int size = JvGetStringUTFLength(jstr);
   qstr.allocate(qstr.strlen() + size + 1);
   JvGetStringUTFRegion(jstr, 0, jstr->length(), (char *)qstr.getBuffer() + qstr.strlen());
   qstr.terminate(qstr.strlen() + size);
}