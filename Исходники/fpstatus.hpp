inline bool is_overflow_fp_status() {
    return (_statusfp() & _EM_OVERFLOW) != 0;
}