void IRPrinter::print(Stmt ir) {
    ir.accept(this);
}