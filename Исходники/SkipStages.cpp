Stmt skip_stages(Stmt stmt, const vector<string> &order) {
    // Don't consider the last stage, because it's the output, so it's
    // never skippable.
    for (size_t i = order.size()-1; i > 0; i--) {
        debug(2) << "skip_stages checking " << order[i-1] << "\n";
        MightBeSkippable check(order[i-1]);
        stmt.accept(&check);
        if (check.result) {
            debug(2) << "skip_stages can skip " << order[i-1] << "\n";
            StageSkipper skipper(order[i-1]);
            stmt = skipper.mutate(stmt);
        }
    }
    return stmt;
}