static void _group_list_init(struct mxq_group_list *glist)
{
    struct mxq_server *server;
    struct mxq_group *group;

    long double memory_per_job_thread;
    long double memory_available_for_group;

    unsigned long slots_per_job;
    unsigned long slots_per_job_memory;
    unsigned long slots_per_job_cpu;
    unsigned long jobs_max;
    unsigned long slots_max;
    unsigned long memory_max;

    assert(glist);
    assert(glist->user);
    assert(glist->user->server);

    server = glist->user->server;
    group  = &glist->group;

    memory_per_job_thread = (long double)group->job_memory / (long double)group->job_threads;

    /* max_memory_per_server_slot_soft < memory_per_job_thread => limit total memory for group default: avg_memory_per_server_slot*/
    /* max_memory_per_server_slot_hard < memory_per_job_thread => do not start jobs for group  default: memory_total */

    /* memory_available_for_group = memory_total * max_memory_per_server_slot_soft / memory_per_job_thread */
    memory_available_for_group = (long double)server->memory_total * (long double)server->memory_limit_slot_soft / memory_per_job_thread;

    if (memory_available_for_group > (long double)server->memory_total)
        memory_available_for_group = (long double)server->memory_total;

    /* memory_slots_per_job = memory_per_job / memory_per_server_slot */
    /* cpu_slots_per_job    = job_threads */
    /* slots_per_job        = max(memory_slots_per_job, cpu_slots_per_job) */

    slots_per_job_memory = (unsigned long)ceill((long double)group->job_memory / server->memory_avg_per_slot);
    slots_per_job_cpu    = group->job_threads;

    if (slots_per_job_memory < slots_per_job_cpu)
        slots_per_job = slots_per_job_cpu;
    else
        slots_per_job = slots_per_job_memory;

    if (memory_per_job_thread > server->memory_limit_slot_hard) {
        jobs_max = 0;
    } else if (memory_per_job_thread > server->memory_avg_per_slot) {
        jobs_max = (unsigned long)ceill(memory_available_for_group / (long double)group->job_memory);
    } else {
        jobs_max = server->slots / group->job_threads;
    }

    if (jobs_max > server->slots / slots_per_job)
        jobs_max = server->slots / slots_per_job;

    /* limit maximum number of jobs on user/group request */
    if (group->job_max_per_node && jobs_max > group->job_max_per_node)
        jobs_max = group->job_max_per_node;

    slots_max  = jobs_max * slots_per_job;
    memory_max = jobs_max * group->job_memory;

    if (glist->memory_per_job_thread != memory_per_job_thread
       || glist->memory_available_for_group != memory_available_for_group
       || glist->slots_per_job != slots_per_job
       || glist->jobs_max != jobs_max
       || glist->slots_max != slots_max
       || glist->memory_max != memory_max) {
        mx_log_info("  group=%s(%u):%lu jobs_max=%lu slots_max=%lu memory_max=%lu slots_per_job=%lu memory_per_job_thread=%Lf :: group %sinitialized.",
                    group->user_name,
                    group->user_uid,
                    group->group_id,
                    jobs_max,
                    slots_max,
                    memory_max,
                    slots_per_job,
                    memory_per_job_thread,
                    glist->orphaned ? "re" : "");
    }

    glist->memory_per_job_thread      = memory_per_job_thread;
    glist->memory_available_for_group = memory_available_for_group;

    glist->slots_per_job = slots_per_job;

    glist->jobs_max   = jobs_max;
    glist->slots_max  = slots_max;
    glist->memory_max = memory_max;

    glist->orphaned = 0;
}