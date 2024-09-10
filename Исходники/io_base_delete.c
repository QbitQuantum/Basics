int mca_io_base_delete(const char *filename, struct opal_info_t *info)
{
    int err;
    opal_list_t *selectable;
    opal_list_item_t *item;
    avail_io_t *avail, selected;

    /* Announce */

    opal_output_verbose(10, ompi_io_base_framework.framework_output,
                        "io:base:delete: deleting file: %s",
                        filename);

    /* See if a set of component was requested by the MCA parameter.
       Don't check for error. */

    /* Compute the intersection of all of my available components with
       the components from all the other processes in this file */

    /* JMS CONTINUE HERE */

    /* See if there were any listed in the MCA parameter; parse them
       and check them all */

    err = OMPI_ERROR;
    opal_output_verbose(10, ompi_io_base_framework.framework_output,
                        "io:base:delete: Checking all available modules");
    selectable = check_components(&ompi_io_base_framework.framework_components,
                                  filename, info, NULL, 0);

    /* Upon return from the above, the modules list will contain the
       list of modules that returned (priority >= 0).  If we have no
       io modules available, it's an error */

    if (NULL == selectable) {
        /* There's no modules available.  Doh! */
        /* show_help */
        return OMPI_ERROR;
    }
    /* Do some kind of collective operation to find a module that
       everyone has available */
#if 1
    /* For the moment, just take the top module off the list */
    /* MSC actually take the buttom */
    item = opal_list_remove_last(selectable);
    avail = (avail_io_t *) item;
    selected = *avail;
    OBJ_RELEASE(avail);
#else
    /* JMS CONTINUE HERE */
#endif

    /* Everything left in the selectable list is therefore unwanted,
       and we call their unquery() method (because they all had
       query() invoked, but will never have init() invoked in this
       scope). */

    for (item = opal_list_remove_first(selectable); item != NULL;
         item = opal_list_remove_first(selectable)) {
        avail = (avail_io_t *) item;
        unquery(avail, filename, info);
        OBJ_RELEASE(item);
    }
    OBJ_RELEASE(selectable);

    if (!strcmp (selected.ai_component.v2_0_0.io_version.mca_component_name,
                 "ompio")) {
        int ret;

        opal_mutex_lock(&ompi_mpi_ompio_bootstrap_mutex);
        if (OMPI_SUCCESS != (ret = mca_base_framework_open(&ompi_fs_base_framework, 0))) {
            opal_mutex_unlock(&ompi_mpi_ompio_bootstrap_mutex);
            return err;
        }
        opal_mutex_unlock(&ompi_mpi_ompio_bootstrap_mutex);

        if (OMPI_SUCCESS !=
            (ret = mca_fs_base_find_available(OPAL_ENABLE_PROGRESS_THREADS, 1))) {
            return err;
        }
    }

    
    /* Finally -- delete the file with the selected component */
    if (OMPI_SUCCESS != (err = delete_file(&selected, filename, info))) {
        return err;
    }

    /* Announce the winner */

    opal_output_verbose(10, ompi_io_base_framework.framework_output,
                        "io:base:delete: Selected io component %s",
                        selected.ai_component.v2_0_0.io_version.mca_component_name);

    return OMPI_SUCCESS;
}