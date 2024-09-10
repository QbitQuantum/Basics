void shared_occs::operator()(expr * t) {
    SASSERT(m_stack.empty());
    shared_occs_mark visited;
    reset();
    operator()(t, visited);
}