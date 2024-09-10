pair<int, int> ModulusRemainder::analyze(Expr e) {
    e.accept(this);
    return make_pair(modulus, remainder);
}