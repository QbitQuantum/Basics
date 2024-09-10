int QoreValue::getAsString(QoreString& str, int format_offset, ExceptionSink *xsink) const {
   if (isNothing()) {
      str.concat(format_offset == FMT_YAML_SHORT ? &YamlNullString : &NothingTypeString);
      return 0;
   }
   switch (type) {
      case QV_Int: str.sprintf(QLLD, v.i); break;
      case QV_Bool: str.concat(v.b ? &TrueString : &FalseString); break;
      case QV_Float: str.sprintf("%.9g", v.f); break;
      case QV_Node: return v.n->getAsString(str, format_offset, xsink);
      default:
	 assert(false);
	 // no break;
   }
   return 0;
}