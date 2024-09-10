void IdealGraphPrinter::print_method(ciMethod *method, int bci, InlineTree *tree) {
  begin_head(METHOD_ELEMENT);

  stringStream str;
  method->print_name(&str);

  stringStream shortStr;
  method->print_short_name(&shortStr);

  print_attr(METHOD_NAME_PROPERTY, str.as_string());
  print_attr(METHOD_SHORT_NAME_PROPERTY, shortStr.as_string());
  print_attr(METHOD_BCI_PROPERTY, bci);

  end_head();

  head(BYTECODES_ELEMENT);
  _xml->print_cr("<![CDATA[");
  method->print_codes_on(_xml);
  _xml->print_cr("]]>");
  tail(BYTECODES_ELEMENT);

  if (tree != NULL && tree->subtrees().length() > 0) {
    head(INLINE_ELEMENT);
    GrowableArray<InlineTree *> subtrees = tree->subtrees();
    for (int i = 0; i < subtrees.length(); i++) {
      print_inline_tree(subtrees.at(i));
    }
    tail(INLINE_ELEMENT);
  }

  tail(METHOD_ELEMENT);
  _xml->flush();
}