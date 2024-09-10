static void JNICALL
cpu_loop_function(jvmtiEnv *jvmti, JNIEnv *env, void *p)
{
    int         loop_trip_counter;
    jboolean    cpu_loop_running;

    loop_trip_counter          = 0;

    rawMonitorEnter(gdata->cpu_loop_lock); {
        gdata->cpu_loop_running = JNI_TRUE;
        cpu_loop_running = gdata->cpu_loop_running;
        /* Notify cpu_sample_init() that we have started */
        rawMonitorNotifyAll(gdata->cpu_loop_lock);
    } rawMonitorExit(gdata->cpu_loop_lock);

    rawMonitorEnter(gdata->cpu_sample_lock); /* Only waits inside loop let go */

    while ( cpu_loop_running ) {

        ++loop_trip_counter;

        LOG3("cpu_loop()", "iteration", loop_trip_counter);

        /* If a dump is in progress, we pause sampling. */
        rawMonitorEnter(gdata->dump_lock); {
            if (gdata->dump_in_process) {
                gdata->pause_cpu_sampling = JNI_TRUE;
            }
        } rawMonitorExit(gdata->dump_lock);

        /* Check to see if we need to pause sampling (listener_loop command) */
        if (gdata->pause_cpu_sampling) {

            /*
             * Pause sampling for now. Reset sample controls if
             * sampling is resumed again.
             */

            rawMonitorWait(gdata->cpu_sample_lock, 0);

            rawMonitorEnter(gdata->cpu_loop_lock); {
                cpu_loop_running = gdata->cpu_loop_running;
            } rawMonitorExit(gdata->cpu_loop_lock);

            /* Continue the while loop, which will terminate if done. */
            continue;
        }

        /* This is the normal short timed wait before getting a sample */
        rawMonitorWait(gdata->cpu_sample_lock,  (jlong)gdata->sample_interval);

        /* Make sure we really want to continue */
        rawMonitorEnter(gdata->cpu_loop_lock); {
            cpu_loop_running = gdata->cpu_loop_running;
        } rawMonitorExit(gdata->cpu_loop_lock);

        /* Break out if we are done */
        if ( !cpu_loop_running ) {
            break;
        }

        /*
         * If a dump request came in after we checked at the top of
         * the while loop, then we catch that fact here. We
         * don't want to perturb the data that is being dumped so
         * we just ignore the data from this sampling loop.
         */
        rawMonitorEnter(gdata->dump_lock); {
            if (gdata->dump_in_process) {
                gdata->pause_cpu_sampling = JNI_TRUE;
            }
        } rawMonitorExit(gdata->dump_lock);

        /* Sample all the threads and update trace costs */
        if ( !gdata->pause_cpu_sampling) {
            tls_sample_all_threads(env);
        }

        /* Check to see if we need to finish */
        rawMonitorEnter(gdata->cpu_loop_lock); {
            cpu_loop_running = gdata->cpu_loop_running;
        } rawMonitorExit(gdata->cpu_loop_lock);

    }
    rawMonitorExit(gdata->cpu_sample_lock);

    rawMonitorEnter(gdata->cpu_loop_lock); {
        /* Notify cpu_sample_term() that we are done. */
        rawMonitorNotifyAll(gdata->cpu_loop_lock);
    } rawMonitorExit(gdata->cpu_loop_lock);

    LOG2("cpu_loop()", "clean termination");
}