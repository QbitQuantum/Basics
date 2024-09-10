/*
 * Return a looped back vnode for the given vnode.
 * If no lnode exists for this vnode create one and put it
 * in a table hashed by vnode.  If the lnode for
 * this vnode is already in the table return it (ref count is
 * incremented by lfind).  The lnode will be flushed from the
 * table when lo_inactive calls freelonode.  The creation of
 * a new lnode can be forced via the LOF_FORCE flag even if
 * the vnode exists in the table.  This is used in the creation
 * of a terminating lnode when looping is detected.  A unique
 * lnode is required for the correct evaluation of the current
 * working directory.
 * NOTE: vp is assumed to be a held vnode.
 */
struct vnode *
makelonode(struct vnode *vp, struct loinfo *li, int flag)
{
    lnode_t *lp, *tlp;
    struct vfs *vfsp;
    vnode_t *nvp;

    lp = NULL;
    TABLE_LOCK_ENTER(vp, li);
    if (flag != LOF_FORCE)
        lp = lfind(vp, li);
    if ((flag == LOF_FORCE) || (lp == NULL)) {
        /*
         * Optimistically assume that we won't need to sleep.
         */
        lp = kmem_cache_alloc(lnode_cache, KM_NOSLEEP);
        nvp = vn_alloc(KM_NOSLEEP);
        if (lp == NULL || nvp == NULL) {
            TABLE_LOCK_EXIT(vp, li);
            /* The lnode allocation may have succeeded, save it */
            tlp = lp;
            if (tlp == NULL) {
                tlp = kmem_cache_alloc(lnode_cache, KM_SLEEP);
            }
            if (nvp == NULL) {
                nvp = vn_alloc(KM_SLEEP);
            }
            lp = NULL;
            TABLE_LOCK_ENTER(vp, li);
            if (flag != LOF_FORCE)
                lp = lfind(vp, li);
            if (lp != NULL) {
                kmem_cache_free(lnode_cache, tlp);
                vn_free(nvp);
                VN_RELE(vp);
                goto found_lnode;
            }
            lp = tlp;
        }
        atomic_inc_32(&li->li_refct);
        vfsp = makelfsnode(vp->v_vfsp, li);
        lp->lo_vnode = nvp;
        VN_SET_VFS_TYPE_DEV(nvp, vfsp, vp->v_type, vp->v_rdev);
        nvp->v_flag |= (vp->v_flag & (VNOMOUNT|VNOMAP|VDIROPEN));
        vn_setops(nvp, lo_vnodeops);
        nvp->v_data = (caddr_t)lp;
        lp->lo_vp = vp;
        lp->lo_looping = 0;
        lsave(lp, li);
        vn_exists(vp);
    } else {
        VN_RELE(vp);
    }

found_lnode:
    TABLE_LOCK_EXIT(vp, li);
    return (ltov(lp));
}