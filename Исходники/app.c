int ACTIVE_TASK::parse(MIOFILE& fin) {
    char buf[256], result_name[256], project_master_url[256];
    int n, dummy;
    unsigned int i;
    PROJECT* project;

    strcpy(result_name, "");
    strcpy(project_master_url, "");

    while (fin.fgets(buf, 256)) {
        if (match_tag(buf, "</active_task>")) {
            project = gstate.lookup_project(project_master_url);
            if (!project) {
                msg_printf(
                    NULL, MSG_INTERNAL_ERROR,
                    "State file error: project %s not found\n",
                    project_master_url
                );
                return ERR_NULL;
            }
            result = gstate.lookup_result(project, result_name);
            if (!result) {
                msg_printf(
                    project, MSG_INTERNAL_ERROR,
                    "State file error: result %s not found\n",
                    result_name
                );
                return ERR_NULL;
            }

            // various sanity checks
            //
            if (result->got_server_ack
                || result->ready_to_report
                || result->state() != RESULT_FILES_DOWNLOADED
            ) {
                msg_printf(project, MSG_INTERNAL_ERROR,
                    "State file error: result %s is in wrong state\n",
                    result_name
                );
                return ERR_BAD_RESULT_STATE;
            }

            wup = result->wup;
            app_version = gstate.lookup_app_version(
                result->app, result->platform, result->version_num,
                result->plan_class
            );
            if (!app_version) {
                msg_printf(
                    project, MSG_INTERNAL_ERROR,
                    "State file error: app %s platform %s version %d not found\n",
                    result->app->name, result->platform, result->version_num
                );
                return ERR_NULL;
            }

            // make sure no two active tasks are in same slot
            //
            for (i=0; i<gstate.active_tasks.active_tasks.size(); i++) {
                ACTIVE_TASK* atp = gstate.active_tasks.active_tasks[i];
                if (atp->slot == slot) {
                    msg_printf(project, MSG_INTERNAL_ERROR,
                        "State file error: two tasks in slot %d\n", slot
                    );
                    return ERR_BAD_RESULT_STATE;
                }
            }
            return 0;
        }
        else if (parse_str(buf, "<result_name>", result_name, sizeof(result_name))) continue;
        else if (parse_str(buf, "<project_master_url>", project_master_url, sizeof(project_master_url))) continue;
        else if (parse_int(buf, "<slot>", slot)) continue;
        else if (parse_bool(buf, "full_init_done", full_init_done)) continue;
        else if (parse_int(buf, "<active_task_state>", dummy)) continue;
        else if (parse_double(buf, "<checkpoint_cpu_time>", checkpoint_cpu_time)) continue;
        else if (parse_double(buf, "<fraction_done>", fraction_done)) continue;
        else if (parse_double(buf, "<current_cpu_time>", current_cpu_time)) continue;
        else if (parse_int(buf, "<app_version_num>", n)) continue;
        else if (parse_double(buf, "<swap_size>", procinfo.swap_size)) continue;
        else if (parse_double(buf, "<working_set_size>", procinfo.working_set_size)) continue;
        else if (parse_double(buf, "<working_set_size_smoothed>", procinfo.working_set_size_smoothed)) continue;
        else if (parse_double(buf, "<page_fault_rate>", procinfo.page_fault_rate)) continue;

        else if (parse_double(buf, "<stats_mem>", stats_mem)) continue;
        else if (parse_double(buf, "<stats_page>", stats_mem)) continue;
        else if (parse_double(buf, "<stats_pagefault_rate>", stats_mem)) continue;
        else if (parse_double(buf, "<stats_disk>", stats_disk)) continue;
        else if (parse_int(buf, "<stats_checkpoint>", stats_checkpoint)) continue;
        else {
            handle_unparsed_xml_warning("ACTIVE_TASK::parse", buf);
        }
    }
    return ERR_XML_PARSE;
}