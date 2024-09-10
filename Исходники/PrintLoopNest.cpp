string print_loop_nest(const vector<Function> &outputs) {
    // Do the first part of lowering:

    // Compute an environment
    map<string, Function> env;
    for (Function f : outputs) {
        map<string, Function> more_funcs = find_transitive_calls(f);
        env.insert(more_funcs.begin(), more_funcs.end());
    }

    // Compute a realization order
    vector<string> order = realization_order(outputs, env);

    // Schedule the functions.
    Stmt s = schedule_functions(outputs, order, env, false);

    // Now convert that to pseudocode
    std::ostringstream sstr;
    PrintLoopNest pln(sstr, env);
    s.accept(&pln);
    return sstr.str();
}