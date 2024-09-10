int BinaryNode::getAsString(QoreString &str, int foff, ExceptionSink *xsink) const {
   if (foff == FMT_YAML_SHORT) {
      QoreString bstr(this, -1);
      str.sprintf("!!binary %s", bstr.getBuffer());
   }
   else
      str.sprintf("binary object %p ("QSD" byte%s)", getPtr(), size(), size() == 1 ? "" : "s");
   return 0;
}