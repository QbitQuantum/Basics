void IRGraphVisitor::include(const Stmt &s) {
    if (visited.count(s.ptr)) {
        return;
    } else {
        visited.insert(s.ptr);
        s.accept(this);
        return;
    }
}