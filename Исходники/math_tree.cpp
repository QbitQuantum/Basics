tree
tan (tree t) {
  if (is_double (t)) return as_tree (tan (as_double (t)));
  return tree (TAN, t);
}