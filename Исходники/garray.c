/*  calc_target()
 */
static void calc_target(garray_t *ga, int64_t gidx, int64_t *tnid_, int64_t *tidx_)
{
    /* if this node has no local elements, there are less than nnodes
       elements, so the array index is the node index */
    if (ga->nlocal_elems == 0) {
        *tnid_ = gidx;
        *tidx_ = 0;
        return;
    }

    /* compute the target nid+idx */
    ldiv_t res = ldiv(gidx, ga->nlocal_elems);

    /* if the distribution is not perfectly even, we have to adjust
       the target nid+idx appropriately */
    if (ga->nextra_elems > 0) {
        int64_t tnid = res.quot, tidx = res.rem;

        /* if i have an extra element... */
        if (ga->g->nid < ga->nextra_elems) {
            /* but the target does not */
            if (tnid >= ga->nextra_elems) {
                /* then the target index has to be adjusted upwards */
                tidx += (tnid - ga->nextra_elems);
                /* which may mean that the target nid does too */
                while (tidx >= (ga->nlocal_elems - 1)) {
                    ++tnid;
                    tidx -= (ga->nlocal_elems - 1);
                }
            }
        }

        /* i don't have an extra element... */
        else {
            /* so adjust the target index downwards */
            tidx -= (tnid < ga->nextra_elems ? tnid : ga->nextra_elems);
            /* which may mean the target nid has to be adjusted too */
            while (tidx < 0) {
                --tnid;
                tidx += ga->nelems_per_node + (tnid < ga->nextra_elems ? 1 : 0);
            }
        }

        res.quot = tnid; res.rem = tidx;
    }

    LOG_DEBUG(ga->g->glog, "[%d] garray calc %ld, target %ld.%ld\n",
              ga->g->nid, gidx, res.quot, res.rem);

    *tnid_ = res.quot;
    *tidx_ = res.rem;
}