int volk_gnsssdr_rank_archs(
    const char *kern_name,     //name of the kernel to rank
    const char *impl_names[],  //list of implementations by name
    const int *impl_deps,      //requirement mask per implementation
    const bool *alignment,     //alignment status of each implementation
    size_t n_impls,            //number of implementations available
    const bool align           //if false, filter aligned implementations
)
{
    size_t i;
    static volk_gnsssdr_arch_pref_t *volk_gnsssdr_arch_prefs;
    static size_t n_arch_prefs = 0;
    static int prefs_loaded = 0;
    if (!prefs_loaded)
        {
            n_arch_prefs = volk_gnsssdr_load_preferences(&volk_gnsssdr_arch_prefs);
            prefs_loaded = 1;
        }

    // If we've defined VOLK_GENERIC to be anything, always return the
    // 'generic' kernel. Used in GR's QA code.
    char *gen_env = getenv("VOLK_GENERIC");
    if (gen_env)
        {
            return volk_gnsssdr_get_index(impl_names, n_impls, "generic");
        }

    //now look for the function name in the prefs list
    for (i = 0; i < n_arch_prefs; i++)
        {
            if (!strncmp(kern_name, volk_gnsssdr_arch_prefs[i].name, sizeof(volk_gnsssdr_arch_prefs[i].name)))  //found it
                {
                    const char *impl_name = align ? volk_gnsssdr_arch_prefs[i].impl_a : volk_gnsssdr_arch_prefs[i].impl_u;
                    return volk_gnsssdr_get_index(impl_names, n_impls, impl_name);
                }
        }

    //return the best index with the largest deps
    size_t best_index_a = 0;
    size_t best_index_u = 0;
    int best_value_a = -1;
    int best_value_u = -1;
    for (i = 0; i < n_impls; i++)
        {
            const signed val = __popcnt(impl_deps[i]);
            if (alignment[i] && val > best_value_a)
                {
                    best_index_a = i;
                    best_value_a = val;
                }
            if (!alignment[i] && val > best_value_u)
                {
                    best_index_u = i;
                    best_value_u = val;
                }
        }

    //when align and we found a best aligned, use it
    if (align && best_value_a != -1) return best_index_a;

    //otherwise return the best unaligned
    return best_index_u;
}