void ModelPrinter::accept_idented(shared_ptr<ModelAST> node) {
    ident++;
    node->accept(*this);
    ident--;
}