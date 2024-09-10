void RemoveFound::visit(Element &e) {
  if (e.hasParam("flags") && e.getFlags().has("found")) e.remove();
}