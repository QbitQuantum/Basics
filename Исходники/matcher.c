static double process_item(MatchInfo *m, Stack *stack, int32_t *final_positions, UStringSearch **searches) {
    UChar32 hc, lc;
    double final_score = 0.0, score = 0.0, score_for_char = 0.0;
    int32_t pos, i, j, hidx, nidx, last_idx, distance, *positions = final_positions + m->needle_len;
    MemoryItem mem = {0};
    UStringSearch *search = NULL;
    UErrorCode status = U_ZERO_ERROR;

    stack_push(stack, 0, 0, 0, 0.0, final_positions);

    while (stack->pos >= 0) {
        stack_pop(stack, &hidx, &nidx, &last_idx, &score, positions);
        mem = m->memo[hidx][nidx][last_idx];
        if (mem.score == DBL_MAX) {
            // No memoized result, calculate the score
            for (i = nidx; i < m->needle_len;) {
                nidx = i;
                U16_FWD_1(m->needle, i, m->needle_len);// i now points to next char in needle 
                search = searches[nidx];
                if (search == NULL || m->haystack_len - hidx < m->needle_len - nidx) { score = 0.0; break; }
                status = U_ZERO_ERROR; // We ignore any errors as we already know that hidx is correct
                usearch_setOffset(search, hidx, &status);
                status = U_ZERO_ERROR;
                pos = usearch_next(search, &status);
                if (pos == USEARCH_DONE) { score = 0.0; break; } // No matches found
                distance = u_countChar32(m->haystack + last_idx, pos - last_idx);  
                if (distance <= 1) score_for_char = m->max_score_per_char;
                else {
                    U16_GET(m->haystack, 0, pos, m->haystack_len, hc); 
                    j = pos;
                    U16_PREV(m->haystack, 0, j, lc); // lc is the prev character
                    score_for_char = calc_score_for_char(m, lc, hc, distance);
                }
                j = pos;
                U16_NEXT(m->haystack, j, m->haystack_len, hc); 
                hidx = j;
                if (m->haystack_len - hidx >= m->needle_len - nidx) stack_push(stack, hidx, nidx, last_idx, score, positions);
                last_idx = pos; 
                positions[nidx] = pos; 
                score += score_for_char;
            } // for(i) iterate over needle
            mem.score = score; memcpy(mem.positions, positions, sizeof(*positions) * m->needle_len);

        } else {
            score = mem.score; memcpy(positions, mem.positions, sizeof(*positions) * m->needle_len);
        }
        // We have calculated the score for this hidx, nidx, last_idx combination, update final_score and final_positions, if needed
        if (score > final_score) {
            final_score = score;
            memcpy(final_positions, positions, sizeof(*positions) * m->needle_len);
        }
    }
    return final_score;
}