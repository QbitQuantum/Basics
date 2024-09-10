static void expand_viterbi_egraphs(int req_viterbi_egraph_size)
{
    int old_size,i;

    if (req_viterbi_egraph_size > max_viterbi_egraph_size) {
        old_size = max_viterbi_egraph_size;

        while (req_viterbi_egraph_size > max_viterbi_egraph_size) {
            max_viterbi_egraph_size *= 2;
        }

        viterbi_egraphs =
            (EG_NODE_PTR *)
            REALLOC(viterbi_egraphs,
                    max_viterbi_egraph_size * sizeof(EG_NODE_PTR));

        for (i = old_size; i < max_viterbi_egraph_size; i++) {
            viterbi_egraphs[i] = NULL;
        }
    }
}