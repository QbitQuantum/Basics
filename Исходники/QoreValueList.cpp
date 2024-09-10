int QoreValueList::getAsString(QoreString &str, int foff, ExceptionSink* xsink) const {
   QoreContainerHelper cch(this);
   if (!cch) {
      str.sprintf("[ERROR: recursive reference to list %p]", this);
      return 0;
   }

   if (foff == FMT_YAML_SHORT) {
      str.concat('[');
      ConstValueListIterator li(this);
      while (li.next()) {
	 QoreValue n = li.getValue();
	 if (n.getAsString(str, foff, xsink))
	    return -1;
	 if (!li.last())
	    str.concat(", ");
      }
      str.concat(']');
      return 0;
   }

   if (!size()) {
      str.concat(&EmptyListString);
      return 0;
   }
   str.concat("list: (");

   if (foff != FMT_NONE)
      str.sprintf("%d element%s)\n", priv->length, priv->length == 1 ? "" : "s");

   for (size_t i = 0; i < priv->length; ++i) {
      if (foff != FMT_NONE) {
	 str.addch(' ', foff + 2);
	 str.sprintf("[%d]=", i);
      }

      QoreValue n = priv->entry[i];
      if (n.getAsString(str, foff != FMT_NONE ? foff + 2 : foff, xsink))
	 return -1;

      if (i != (priv->length - 1)) {
	 if (foff != FMT_NONE)
	    str.concat('\n');
	 else
	    str.concat(", ");
      }
   }
   if (foff == FMT_NONE)
      str.concat(')');

   return 0;
}