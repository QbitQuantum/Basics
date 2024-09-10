Tuple argmin(Expr e, const std::string &name) {
    Internal::FindFreeVars v;
    e.accept(&v);
    Func f(name);

    assert(v.rdom.defined() && "Expression passed to argmin must reference a reduction domain");

    Tuple initial_tup(vector<Expr>(v.rdom.dimensions()+1));
    Tuple update_tup(vector<Expr>(v.rdom.dimensions()+1));
    for (int i = 0; i < v.rdom.dimensions(); i++) {
        initial_tup[i] = 0;
        update_tup[i] = v.rdom[i];
    }
    int value_index = (int)initial_tup.size()-1;
    initial_tup[value_index] = e.type().max();
    update_tup[value_index] = e;

    f(v.free_vars) = initial_tup;
    Expr better = e < f(v.free_vars)[value_index];
    f(v.free_vars) = tuple_select(better, update_tup, f(v.free_vars));
    return f(v.free_vars);
}