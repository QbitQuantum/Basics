 // Calls appropriate visitor for given element
 void visitElement(const Element& element)
 {
     Style style = context_.styleProvider.forElement(element, context_.quadKey.levelOfDetail);
     std::stringstream ss(*style.get(builderKeyId_)->value());
     while (ss.good()) {
         std::string name;
         getline(ss, name, ',');
         element.accept(getBuilder(name));
     }
 }