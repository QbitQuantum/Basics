/* Attempt to schedule a specific job on specific available nodes
 * IN job_ptr - job to schedule
 * IN/OUT avail_bitmap - nodes available/selected to use
 * IN exc_core_bitmap - cores which can not be used
 * RET SLURM_SUCCESS on success, otherwise an error code
 */
static int  _try_sched(struct job_record *job_ptr, bitstr_t **avail_bitmap,
                       uint32_t min_nodes, uint32_t max_nodes,
                       uint32_t req_nodes, bitstr_t *exc_core_bitmap)
{
    bitstr_t *tmp_bitmap;
    int rc = SLURM_SUCCESS;
    int feat_cnt = _num_feature_count(job_ptr);
    List preemptee_candidates = NULL;
    List preemptee_job_list = NULL;

    if (feat_cnt) {
        /* Ideally schedule the job feature by feature,
         * but I don't want to add that complexity here
         * right now, so clear the feature counts and try
         * to schedule. This will work if there is only
         * one feature count. It should work fairly well
         * in cases where there are multiple feature
         * counts. */
        struct job_details *detail_ptr = job_ptr->details;
        ListIterator feat_iter;
        struct feature_record *feat_ptr;
        int i = 0, list_size;
        uint16_t *feat_cnt_orig = NULL, high_cnt = 0;

        /* Clear the feature counts */
        list_size = list_count(detail_ptr->feature_list);
        feat_cnt_orig = xmalloc(sizeof(uint16_t) * list_size);
        feat_iter = list_iterator_create(detail_ptr->feature_list);
        while ((feat_ptr =
                    (struct feature_record *) list_next(feat_iter))) {
            high_cnt = MAX(high_cnt, feat_ptr->count);
            feat_cnt_orig[i++] = feat_ptr->count;
            feat_ptr->count = 0;
        }
        list_iterator_destroy(feat_iter);

        if ((job_req_node_filter(job_ptr, *avail_bitmap) !=
                SLURM_SUCCESS) ||
                (bit_set_count(*avail_bitmap) < high_cnt)) {
            rc = ESLURM_NODES_BUSY;
        } else {
            preemptee_candidates =
                slurm_find_preemptable_jobs(job_ptr);
            rc = select_g_job_test(job_ptr, *avail_bitmap,
                                   high_cnt, max_nodes, req_nodes,
                                   SELECT_MODE_WILL_RUN,
                                   preemptee_candidates,
                                   &preemptee_job_list,
                                   exc_core_bitmap);
            if (preemptee_job_list) {
                list_destroy(preemptee_job_list);
                preemptee_job_list = NULL;
            }
        }

        /* Restore the feature counts */
        i = 0;
        feat_iter = list_iterator_create(detail_ptr->feature_list);
        while ((feat_ptr =
                    (struct feature_record *) list_next(feat_iter))) {
            feat_ptr->count = feat_cnt_orig[i++];
        }
        list_iterator_destroy(feat_iter);
        xfree(feat_cnt_orig);
    } else {
        /* Try to schedule the job. First on dedicated nodes
         * then on shared nodes (if so configured). */
        uint16_t orig_shared;
        time_t now = time(NULL);
        char str[100];

        preemptee_candidates = slurm_find_preemptable_jobs(job_ptr);
        orig_shared = job_ptr->details->shared;
        job_ptr->details->shared = 0;
        tmp_bitmap = bit_copy(*avail_bitmap);

        if (exc_core_bitmap) {
            bit_fmt(str, (sizeof(str) - 1), exc_core_bitmap);
            debug2(" _try_sched with exclude core bitmap: %s",str);
        }

        rc = select_g_job_test(job_ptr, *avail_bitmap, min_nodes,
                               max_nodes, req_nodes,
                               SELECT_MODE_WILL_RUN,
                               preemptee_candidates,
                               &preemptee_job_list,
                               exc_core_bitmap);
        if (preemptee_job_list) {
            list_destroy(preemptee_job_list);
            preemptee_job_list = NULL;
        }

        job_ptr->details->shared = orig_shared;

        if (((rc != SLURM_SUCCESS) || (job_ptr->start_time > now)) &&
                (orig_shared != 0)) {
            FREE_NULL_BITMAP(*avail_bitmap);
            *avail_bitmap= tmp_bitmap;
            rc = select_g_job_test(job_ptr, *avail_bitmap,
                                   min_nodes, max_nodes, req_nodes,
                                   SELECT_MODE_WILL_RUN,
                                   preemptee_candidates,
                                   &preemptee_job_list,
                                   exc_core_bitmap);
            if (preemptee_job_list) {
                list_destroy(preemptee_job_list);
                preemptee_job_list = NULL;
            }
        } else
            FREE_NULL_BITMAP(tmp_bitmap);
    }

    if (preemptee_candidates)
        list_destroy(preemptee_candidates);
    return rc;

}