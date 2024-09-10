void test1()
{
    const char* fname = "tests/assets/trace.txt";
    mm_simulator_t* simulator = mm_simulator_parse_file(fname);

    ASSERT(simulator->physical && simulator->virtual,
           "Must have created physical and virtual memories");
    ASSERT(simulator->physical->size == 100, "");
    ASSERT(simulator->virtual->size == 100, "");
    ASSERT(simulator->process_count == 4, "");

    ASSERT(simulator->processes[0]->t0 == 0, "");
    STRNCMP(simulator->processes[0]->pname, "process0");
    ASSERT(simulator->processes[0]->access_count == 2, "");
    ASSERT(simulator->processes[0]->access[0].position == 1, "");
    ASSERT(simulator->processes[0]->access[0].time == 1, "");

    while (simulator->process_count-- > 0)
        mm_process_destroy(simulator->processes[simulator->process_count]);
    mm_simulator_destroy(simulator);
}