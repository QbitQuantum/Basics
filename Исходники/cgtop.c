static int process(const char *controller, const char *path, Hashmap *a, Hashmap *b, unsigned iteration) {
        Group *g;
        int r;
        FILE *f;
        pid_t pid;
        unsigned n;

        assert(controller);
        assert(path);
        assert(a);

        g = hashmap_get(a, path);
        if (!g) {
                g = hashmap_get(b, path);
                if (!g) {
                        g = new0(Group, 1);
                        if (!g)
                                return -ENOMEM;

                        g->path = strdup(path);
                        if (!g->path) {
                                group_free(g);
                                return -ENOMEM;
                        }

                        r = hashmap_put(a, g->path, g);
                        if (r < 0) {
                                group_free(g);
                                return r;
                        }
                } else {
                        assert_se(hashmap_move_one(a, b, path) == 0);
                        g->cpu_valid = g->memory_valid = g->io_valid = g->n_tasks_valid = false;
                }
        }

        /* Regardless which controller, let's find the maximum number
         * of processes in any of it */

        r = cg_enumerate_tasks(controller, path, &f);
        if (r < 0)
                return r;

        n = 0;
        while (cg_read_pid(f, &pid) > 0)
                n++;
        fclose(f);

        if (n > 0) {
                if (g->n_tasks_valid)
                        g->n_tasks = MAX(g->n_tasks, n);
                else
                        g->n_tasks = n;

                g->n_tasks_valid = true;
        }

        if (streq(controller, "cpuacct")) {
                uint64_t new_usage;
                char *p, *v;
                struct timespec ts;

                r = cg_get_path(controller, path, "cpuacct.usage", &p);
                if (r < 0)
                        return r;

                r = read_one_line_file(p, &v);
                free(p);
                if (r < 0)
                        return r;

                r = safe_atou64(v, &new_usage);
                free(v);
                if (r < 0)
                        return r;

                assert_se(clock_gettime(CLOCK_MONOTONIC, &ts) == 0);

                if (g->cpu_iteration == iteration - 1) {
                        uint64_t x, y;

                        x = ((uint64_t) ts.tv_sec * 1000000000ULL + (uint64_t) ts.tv_nsec) -
                                ((uint64_t) g->cpu_timestamp.tv_sec * 1000000000ULL + (uint64_t) g->cpu_timestamp.tv_nsec);

                        y = new_usage - g->cpu_usage;

                        if (y > 0) {
                                g->cpu_fraction = (double) y / (double) x;
                                g->cpu_valid = true;
                        }
                }

                g->cpu_usage = new_usage;
                g->cpu_timestamp = ts;
                g->cpu_iteration = iteration;

        } else if (streq(controller, "memory")) {
                char *p, *v;

                r = cg_get_path(controller, path, "memory.usage_in_bytes", &p);
                if (r < 0)
                        return r;

                r = read_one_line_file(p, &v);
                free(p);
                if (r < 0)
                        return r;

                r = safe_atou64(v, &g->memory);
                free(v);
                if (r < 0)
                        return r;

                if (g->memory > 0)
                        g->memory_valid = true;

        } else if (streq(controller, "blkio")) {
                char *p;
                uint64_t wr = 0, rd = 0;
                struct timespec ts;

                r = cg_get_path(controller, path, "blkio.io_service_bytes", &p);
                if (r < 0)
                        return r;

                f = fopen(p, "re");
                free(p);

                if (!f)
                        return -errno;

                for (;;) {
                        char line[LINE_MAX], *l;
                        uint64_t k, *q;

                        if (!fgets(line, sizeof(line), f))
                                break;

                        l = strstrip(line);
                        l += strcspn(l, WHITESPACE);
                        l += strspn(l, WHITESPACE);

                        if (first_word(l, "Read")) {
                                l += 4;
                                q = &rd;
                        } else if (first_word(l, "Write")) {
                                l += 5;
                                q = &wr;
                        } else
                                continue;

                        l += strspn(l, WHITESPACE);
                        r = safe_atou64(l, &k);
                        if (r < 0)
                                continue;

                        *q += k;
                }

                fclose(f);

                assert_se(clock_gettime(CLOCK_MONOTONIC, &ts) == 0);

                if (g->io_iteration == iteration - 1) {
                        uint64_t x, yr, yw;

                        x = ((uint64_t) ts.tv_sec * 1000000000ULL + (uint64_t) ts.tv_nsec) -
                                ((uint64_t) g->io_timestamp.tv_sec * 1000000000ULL + (uint64_t) g->io_timestamp.tv_nsec);

                        yr = rd - g->io_input;
                        yw = wr - g->io_output;

                        if (yr > 0 || yw > 0) {
                                g->io_input_bps = (yr * 1000000000ULL) / x;
                                g->io_output_bps = (yw * 1000000000ULL) / x;
                                g->io_valid = true;

                        }
                }

                g->io_input = rd;
                g->io_output = wr;
                g->io_timestamp = ts;
                g->io_iteration = iteration;
        }

        return 0;
}