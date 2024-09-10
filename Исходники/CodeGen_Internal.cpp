Closure::Closure(Stmt s, const string &loop_variable, llvm::StructType *buffer_t) : buffer_t(buffer_t) {
    ignore.push(loop_variable, 0);
    s.accept(this);
}