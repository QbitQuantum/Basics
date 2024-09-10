bool BlackList::isInInit(const GlobalVariable &G) {
  return (isIn(*G.getParent()) ||
          inSection("global-init", G.getName()) ||
          inSection("global-init-type", GetGVTypeString(G)));
}