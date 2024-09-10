    void Remove_Placeholders::operator()(Ruleset* r) {
        // Create a new selector group without placeholders
        Selector_List* sl = static_cast<Selector_List*>(r->selector());

        if (sl) {
            Selector_List* new_sl = new (ctx.mem) Selector_List(sl->pstate());

            for (size_t i = 0, L = sl->length(); i < L; ++i) {
                if (!(*sl)[i]->contains_placeholder()) {
                    *new_sl << (*sl)[i];
                }
            }

            // Set the new placeholder selector list
            r->selector(new_sl);
        }

        // Iterate into child blocks
        Block* b = r->block();

        for (size_t i = 0, L = b->length(); i < L; ++i) {
            if ((*b)[i]) (*b)[i]->perform(this);
        }
    }