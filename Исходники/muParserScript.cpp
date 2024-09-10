QVariant muParserScript::evaluateImpl() {
  if (!compile(scriptCode())) {
    return QVariant();
  }
  double val = 0.0;
  try {
    current = this;
    for (QStringList::iterator i = muCode.begin(); i != muCode.end(); ++i) {
      parser.SetExpr(i->toAscii().constData());
      val = parser.Eval();
    }
  } catch (EmptySourceError *) {
    return QVariant("");
  } catch (ParserError &e) {
    emit error(e.GetMsg().c_str(), "", 0);
    return QVariant();
  }
  return QVariant(val);
}