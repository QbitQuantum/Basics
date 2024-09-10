    inline bool st_exact_search(StateParser & stparser, const char * s)
    {
        if ( stparser.empty() ) {
            return false;
        }

        StatesValue stval(stparser.states(), stparser.nb_capture());

// #ifdef DISPLAY_TRACE
//         display_states(stval, stparser.root());
// #endif

        st_step_range_list_t l1;
        add_first(l1, l1, stparser.root());
        if (l1.empty()) {
            return false;
        }
        utf8_consumer consumer(s);
        st_step_range_list_t l2;
        bool res = false;
        unsigned count = 1;
        while (consumer.valid() && !(res = st_exact_step(l1, l2, stval, consumer.bumpc(), consumer, ++count))) {
#ifdef DISPLAY_TRACE
            std::cout << "\033[01;31mc: '" << utf8_char(consumer.getc()) << "'\033[0m\n";
#endif
            if (l2.empty()) {
                return false;
            }
            l1.swap(l2);
            l2.clear();
        }

        if (consumer.valid()) {
            return false;
        }
        if (res) {
            return true;
        }
        return false;
    }