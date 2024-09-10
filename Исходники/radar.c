/*
 * new_rnode_allowed
 *
 * add a new allowed rnode in the `alr' llist which has
 * already `*alr_counter' members. `gid', `min_lvl', and `tot_lvl' are the
 * respective field of the new allowed_rnode struct.
 */
void
new_rnode_allowed(struct allowed_rnode **alr, int *alr_counter,
                  int *gid, int min_lvl, int tot_lvl)
{
    struct allowed_rnode *new_alr;

    new_alr = xmalloc(sizeof(struct allowed_rnode));

    new_alr->min_level = min_lvl;
    new_alr->tot_level = tot_lvl;

    setzero(new_alr->gid, sizeof(int) * MAX_LEVELS);
    memcpy(&new_alr->gid[min_lvl], &gid[min_lvl],
           sizeof(int) * (tot_lvl - min_lvl));

    debug(DBG_SOFT,
          "new_rnode_allowed: %d, %d, %d, %d. min_lvl: %d, tot_lvl: %d",
          gid[0], gid[1], gid[2], gid[3], min_lvl, tot_lvl);

    clist_add(alr, alr_counter, new_alr);
}