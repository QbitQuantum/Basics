static inline void atomic_add_f64(volatile double* global_value, double addend)
{
#ifdef __INTEL_COMPILER
   uint64_t expected_value, new_value;
    do {
        double old_value = *global_value;
        expected_value = _castf64_u64(old_value);
        new_value = _castf64_u64(old_value + addend);
    } while (!__sync_bool_compare_and_swap((volatile uint64_t*)global_value,
                                           expected_value, new_value));
#else
   #pragma omp atomic
   *global_value+=addend;
#endif
}