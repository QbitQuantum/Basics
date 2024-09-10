void LogStatistics::format(char **buf,
                           uid_t uid, unsigned int logMask, log_time oldest) {
    static const unsigned short spaces_current = 13;
    static const unsigned short spaces_total = 19;

    if (*buf) {
        free(*buf);
        *buf = NULL;
    }

    android::String8 string("        span -> size/num");
    size_t oldLength;
    short spaces = 2;

    log_id_for_each(i) {
        if (!(logMask & (1 << i))) {
            continue;
        }
        oldLength = string.length();
        if (spaces < 0) {
            spaces = 0;
        }
        string.appendFormat("%*s%s", spaces, "", android_log_id_to_name(i));
        spaces += spaces_total + oldLength - string.length();

        LidStatistics &l = id(i);
        l.sort();

        UidStatisticsCollection::iterator iu;
        for (iu = l.begin(); iu != l.end(); ++iu) {
            (*iu)->sort();
        }
    }

    spaces = 1;
    log_time t(CLOCK_MONOTONIC);
    unsigned long long d;
    if (mStatistics) {
        d = t.nsec() - start.nsec();
        string.appendFormat("\nTotal%4llu:%02llu:%02llu.%09llu",
                  d / NS_PER_SEC / 60 / 60, (d / NS_PER_SEC / 60) % 60,
                  (d / NS_PER_SEC) % 60, d % NS_PER_SEC);

        log_id_for_each(i) {
            if (!(logMask & (1 << i))) {
                continue;
            }
            oldLength = string.length();
            if (spaces < 0) {
                spaces = 0;
            }
            string.appendFormat("%*s%zu/%zu", spaces, "",
                                sizesTotal(i), elementsTotal(i));
            spaces += spaces_total + oldLength - string.length();
        }
        spaces = 1;
    }

    d = t.nsec() - oldest.nsec();
    string.appendFormat("\nNow%6llu:%02llu:%02llu.%09llu",
                  d / NS_PER_SEC / 60 / 60, (d / NS_PER_SEC / 60) % 60,
                  (d / NS_PER_SEC) % 60, d % NS_PER_SEC);

    log_id_for_each(i) {
        if (!(logMask & (1 << i))) {
            continue;
        }

        size_t els = elements(i);
        if (els) {
            oldLength = string.length();
            if (spaces < 0) {
                spaces = 0;
            }
            string.appendFormat("%*s%zu/%zu", spaces, "", sizes(i), els);
            spaces -= string.length() - oldLength;
        }
        spaces += spaces_total;
    }

    // Construct list of worst spammers by Pid
    static const unsigned char num_spammers = 10;
    bool header = false;

    log_id_for_each(i) {
        if (!(logMask & (1 << i))) {
            continue;
        }

        PidStatisticsCollection pids;
        pids.clear();

        LidStatistics &l = id(i);
        UidStatisticsCollection::iterator iu;
        for (iu = l.begin(); iu != l.end(); ++iu) {
            UidStatistics &u = *(*iu);
            PidStatisticsCollection::iterator ip;
            for (ip = u.begin(); ip != u.end(); ++ip) {
                PidStatistics *p = (*ip);
                if (p->getPid() == p->gone) {
                    break;
                }

                size_t mySizes = p->sizes();

                PidStatisticsCollection::iterator q;
                unsigned char num = 0;
                for (q = pids.begin(); q != pids.end(); ++q) {
                    if (mySizes > (*q)->sizes()) {
                        pids.insert(q, p);
                        break;
                    }
                    // do we need to traverse deeper in the list?
                    if (++num > num_spammers) {
                        break;
                    }
                }
                if (q == pids.end()) {
                   pids.push_back(p);
                }
            }
        }

        size_t threshold = sizes(i);
        if (threshold < 65536) {
            threshold = 65536;
        }
        threshold /= 100;

        PidStatisticsCollection::iterator pt = pids.begin();

        for(int line = 0;
                (pt != pids.end()) && (line < num_spammers);
                ++line, pt = pids.erase(pt)) {
            PidStatistics *p = *pt;

            size_t sizes = p->sizes();
            if (sizes < threshold) {
                break;
            }

            char *name = p->getName();
            pid_t pid = p->getPid();
            if (!name || !*name) {
                name = pidToName(pid);
                if (name) {
                    if (*name) {
                        p->setName(name);
                    } else {
                        free(name);
                        name = NULL;
                    }
                }
            }

            if (!header) {
                string.appendFormat("\n\nChattiest clients:\n"
                                    "log id %-*s PID[?] name",
                                    spaces_total, "size/total");
                header = true;
            }

            size_t sizesTotal = p->sizesTotal();

            android::String8 sz("");
            sz.appendFormat((sizes != sizesTotal) ? "%zu/%zu" : "%zu",
                            sizes, sizesTotal);

            android::String8 pd("");
            pd.appendFormat("%u%c", pid, p->pidGone() ? '?' : ' ');

            string.appendFormat("\n%-7s%-*s %-7s%s",
                                line ? "" : android_log_id_to_name(i),
                                spaces_total, sz.string(), pd.string(),
                                name ? name : "");
        }

        pids.clear();
    }

    if (dgramQlenStatistics) {
        const unsigned short spaces_time = 6;
        const unsigned long long max_seconds = 100000;
        spaces = 0;
        string.append("\n\nMinimum time between log events per max_dgram_qlen:\n");
        for(unsigned short i = 0; dgramQlen(i); ++i) {
            oldLength = string.length();
            if (spaces < 0) {
                spaces = 0;
            }
            string.appendFormat("%*s%u", spaces, "", dgramQlen(i));
            spaces += spaces_time + oldLength - string.length();
        }
        string.append("\n");
        spaces = 0;
        unsigned short n;
        for(unsigned short i = 0; (n = dgramQlen(i)); ++i) {
            unsigned long long duration = minimum(i);
            if (duration) {
                duration /= n;
                if (duration >= (NS_PER_SEC * max_seconds)) {
                    duration = NS_PER_SEC * (max_seconds - 1);
                }
                oldLength = string.length();
                if (spaces < 0) {
                    spaces = 0;
                }
                string.appendFormat("%*s", spaces, "");
                if (duration >= (NS_PER_SEC * 10)) {
                    string.appendFormat("%llu",
                        (duration + (NS_PER_SEC / 2))
                            / NS_PER_SEC);
                } else if (duration >= (NS_PER_SEC / (1000 / 10))) {
                    string.appendFormat("%llum",
                        (duration + (NS_PER_SEC / 2 / 1000))
                            / (NS_PER_SEC / 1000));
                } else if (duration >= (NS_PER_SEC / (1000000 / 10))) {
                    string.appendFormat("%lluu",
                        (duration + (NS_PER_SEC / 2 / 1000000))
                            / (NS_PER_SEC / 1000000));
                } else {
                    string.appendFormat("%llun", duration);
                }
                spaces -= string.length() - oldLength;
            }
            spaces += spaces_time;
        }
    }

    log_id_for_each(i) {
        if (!(logMask & (1 << i))) {
            continue;
        }

        header = false;
        bool first = true;

        UidStatisticsCollection::iterator ut;
        for(ut = id(i).begin(); ut != id(i).end(); ++ut) {
            UidStatistics *up = *ut;
            if ((uid != AID_ROOT) && (uid != up->getUid())) {
                continue;
            }

            PidStatisticsCollection::iterator pt = up->begin();
            if (pt == up->end()) {
                continue;
            }

            android::String8 intermediate;

            if (!header) {
                // header below tuned to match spaces_total and spaces_current
                spaces = 0;
                intermediate = string.format("%s: UID/PID Total size/num",
                                             android_log_id_to_name(i));
                string.appendFormat("\n\n%-31sNow          "
                                         "UID/PID[?]  Total              Now",
                                    intermediate.string());
                intermediate.clear();
                header = true;
            }

            bool oneline = ++pt == up->end();
            --pt;

            if (!oneline) {
                first = true;
            } else if (!first && (spaces > 0)) {
                string.appendFormat("%*s", spaces, "");
            }
            spaces = 0;

            uid_t u = up->getUid();
            PidStatistics *pp = *pt;
            pid_t p = pp->getPid();

            intermediate = string.format(oneline
                                             ? ((p == PidStatistics::gone)
                                                 ? "%d/?"
                                                 : "%d/%d%c")
                                             : "%d",
                                         u, p, pp->pidGone() ? '?' : '\0');
            string.appendFormat(first ? "\n%-12s" : "%-12s",
                                intermediate.string());
            intermediate.clear();

            size_t elsTotal = up->elementsTotal();
            oldLength = string.length();
            string.appendFormat("%zu/%zu", up->sizesTotal(), elsTotal);
            spaces += spaces_total + oldLength - string.length();

            size_t els = up->elements();
            if (els == elsTotal) {
                if (spaces < 0) {
                    spaces = 0;
                }
                string.appendFormat("%*s=", spaces, "");
                spaces = -1;
            } else if (els) {
                oldLength = string.length();
                if (spaces < 0) {
                    spaces = 0;
                }
                string.appendFormat("%*s%zu/%zu", spaces, "", up->sizes(), els);
                spaces -= string.length() - oldLength;
            }
            spaces += spaces_current;

            first = !first;

            if (oneline) {
                continue;
            }

            size_t gone_szs = 0;
            size_t gone_els = 0;

            for(; pt != up->end(); ++pt) {
                pp = *pt;
                p = pp->getPid();

                // If a PID no longer has any current logs, and is not
                // active anymore, skip & report totals for gone.
                elsTotal = pp->elementsTotal();
                size_t szsTotal = pp->sizesTotal();
                if (p == pp->gone) {
                    gone_szs += szsTotal;
                    gone_els += elsTotal;
                    continue;
                }
                els = pp->elements();
                bool gone = pp->pidGone();
                if (gone && (els == 0)) {
                    // ToDo: garbage collection: move this statistical bucket
                    //       from its current UID/PID to UID/? (races and
                    //       wrap around are our achilles heel). Below is
                    //       merely lipservice to catch PIDs that were still
                    //       around when the stats were pruned to zero.
                    gone_szs += szsTotal;
                    gone_els += elsTotal;
                    continue;
                }

                if (!first && (spaces > 0)) {
                    string.appendFormat("%*s", spaces, "");
                }
                spaces = 0;

                intermediate = string.format(gone ? "%d/%d?" : "%d/%d", u, p);
                string.appendFormat(first ? "\n%-12s" : "%-12s",
                                    intermediate.string());
                intermediate.clear();

                oldLength = string.length();
                string.appendFormat("%zu/%zu", szsTotal, elsTotal);
                spaces += spaces_total + oldLength - string.length();

                if (els == elsTotal) {
                    if (spaces < 0) {
                        spaces = 0;
                    }
                    string.appendFormat("%*s=", spaces, "");
                    spaces = -1;
                } else if (els) {
                    oldLength = string.length();
                    if (spaces < 0) {
                        spaces = 0;
                    }
                    string.appendFormat("%*s%zu/%zu", spaces, "",
                                        pp->sizes(), els);
                    spaces -= string.length() - oldLength;
                }
                spaces += spaces_current;

                first = !first;
            }

            if (gone_els) {
                if (!first && (spaces > 0)) {
                    string.appendFormat("%*s", spaces, "");
                }

                intermediate = string.format("%d/?", u);
                string.appendFormat(first ? "\n%-12s" : "%-12s",
                                    intermediate.string());
                intermediate.clear();

                spaces = spaces_total + spaces_current;

                oldLength = string.length();
                string.appendFormat("%zu/%zu", gone_szs, gone_els);
                spaces -= string.length() - oldLength;

                first = !first;
            }
        }
    }

    *buf = strdup(string.string());
}