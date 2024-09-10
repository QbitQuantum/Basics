template <typename Visitor> void enumerateFields_gen(InstMem obj,  Visitor & vis) {
  enumerateFields_gen(Inst(obj), vis);
  vis(obj.segment(),"segment");
  vis(obj.align(),"align");
  vis(obj.equivClass(),"equivClass");
  vis(obj.width(),"width");
  enumerateFields(obj.modifier(), vis);
}