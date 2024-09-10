int count_host_alignment_asserts(Func f, std::map<string, int> m) {
    Target t = get_jit_target_from_environment();
    t.set_feature(Target::NoBoundsQuery);
    f.compute_root();
    Stmt s = Internal::lower({f.function()}, f.name(), t);
    CountHostAlignmentAsserts c(m);
    s.accept(&c);
    return c.count;
}