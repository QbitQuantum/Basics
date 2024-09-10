int run_test(struct test *test)
{
    fprintf(stderr, "\nRunning test '%s':\n%s\n", test->name, test->description);

    rrd_memory_mode = RRD_MEMORY_MODE_RAM;
    rrd_update_every = test->update_every;

    char name[101];
    snprintfz(name, 100, "unittest-%s", test->name);

    // create the chart
    RRDSET *st = rrdset_create("netdata", name, name, "netdata", NULL, "Unit Testing", "a value", 1, test->update_every, RRDSET_TYPE_LINE);
    RRDDIM *rd = rrddim_add(st, "dim1", NULL, test->multiplier, test->divisor, test->algorithm);
    
    RRDDIM *rd2 = NULL;
    if(test->feed2)
        rd2 = rrddim_add(st, "dim2", NULL, test->multiplier, test->divisor, test->algorithm);

    st->debug = 1;

    // feed it with the test data
    time_t time_now = 0, time_start = now_realtime_sec();
    unsigned long c;
    collected_number last = 0;
    for(c = 0; c < test->feed_entries; c++) {
        if(debug_flags) fprintf(stderr, "\n\n");

        if(c) {
            time_now += test->feed[c].microseconds;
            fprintf(stderr, "    > %s: feeding position %lu, after %0.3f seconds (%0.3f seconds from start), delta " CALCULATED_NUMBER_FORMAT ", rate " CALCULATED_NUMBER_FORMAT "\n", 
                test->name, c+1,
                (float)test->feed[c].microseconds / 1000000.0,
                (float)time_now / 1000000.0,
                ((calculated_number)test->feed[c].value - (calculated_number)last) * (calculated_number)test->multiplier / (calculated_number)test->divisor,
                (((calculated_number)test->feed[c].value - (calculated_number)last) * (calculated_number)test->multiplier / (calculated_number)test->divisor) / (calculated_number)test->feed[c].microseconds * (calculated_number)1000000);
            rrdset_next_usec_unfiltered(st, test->feed[c].microseconds);
        }
        else {
            fprintf(stderr, "    > %s: feeding position %lu\n", test->name, c+1);
        }

        fprintf(stderr, "       >> %s with value " COLLECTED_NUMBER_FORMAT "\n", rd->name, test->feed[c].value);
        rrddim_set(st, "dim1", test->feed[c].value);
        last = test->feed[c].value;

        if(rd2) {
            fprintf(stderr, "       >> %s with value " COLLECTED_NUMBER_FORMAT "\n", rd2->name, test->feed2[c]);
            rrddim_set(st, "dim2", test->feed2[c]);
        }

        rrdset_done(st);

        // align the first entry to second boundary
        if(!c) {
            fprintf(stderr, "    > %s: fixing first collection time to be %llu microseconds to second boundary\n", test->name, test->feed[c].microseconds);
            rd->last_collected_time.tv_usec = st->last_collected_time.tv_usec = st->last_updated.tv_usec = test->feed[c].microseconds;
            // time_start = st->last_collected_time.tv_sec;
        }
    }

    // check the result
    int errors = 0;

    if(st->counter != test->result_entries) {
        fprintf(stderr, "    %s stored %lu entries, but we were expecting %lu, ### E R R O R ###\n", test->name, st->counter, test->result_entries);
        errors++;
    }

    unsigned long max = (st->counter < test->result_entries)?st->counter:test->result_entries;
    for(c = 0 ; c < max ; c++) {
        calculated_number v = unpack_storage_number(rd->values[c]);
        calculated_number n = test->results[c];
        int same = (roundl(v * 10000000.0) == roundl(n * 10000000.0))?1:0;
        fprintf(stderr, "    %s/%s: checking position %lu (at %lu secs), expecting value " CALCULATED_NUMBER_FORMAT ", found " CALCULATED_NUMBER_FORMAT ", %s\n",
            test->name, rd->name, c+1,
            (rrdset_first_entry_t(st) + c * st->update_every) - time_start,
            n, v, (same)?"OK":"### E R R O R ###");

        if(!same) errors++;

        if(rd2) {
            v = unpack_storage_number(rd2->values[c]);
            n = test->results2[c];
            same = (roundl(v * 10000000.0) == roundl(n * 10000000.0))?1:0;
            fprintf(stderr, "    %s/%s: checking position %lu (at %lu secs), expecting value " CALCULATED_NUMBER_FORMAT ", found " CALCULATED_NUMBER_FORMAT ", %s\n",
                test->name, rd2->name, c+1,
                (rrdset_first_entry_t(st) + c * st->update_every) - time_start,
                n, v, (same)?"OK":"### E R R O R ###");
            if(!same) errors++;
        }
    }

    return errors;
}