bool uses_branches(Func f) {
    Target t = get_jit_target_from_environment();
    t.set_feature(Target::NoBoundsQuery);
    t.set_feature(Target::NoAsserts);
    Stmt s = Internal::lower(f.function(), t);
    ContainsBranches b;
    s.accept(&b);
    return b.result;
}