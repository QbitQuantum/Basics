struct syntax_node * rel_exp(){
  struct syntax_node * t;
  t = (struct syntax_node*)malloc(sizeof(struct syntax_node));

  chushihua_t(t);
  t->child[0] = Exp();
  t->child[1] = other_rel_e();
  strcpy(t->kind_name, "RelExp");
  return t;
}