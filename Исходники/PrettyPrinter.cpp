void PrettyPrinter::PrintOut(AstNode* node) {
    PrettyPrinter printer;
    PrintF("%s", printer.Print(node));
}