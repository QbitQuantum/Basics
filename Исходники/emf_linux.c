/*
 * Description: This function is called when the user application enables
 *              EMF on a bridge interface. It primarily allocates memory
 *              for instance data and calls the common code init function.
 *
 * Input:       emf     - EMF module global data pointer
 *              inst_id - EMF instance name
 *              br_ptr  - Bridge device pointer
 */
static emf_info_t *
emf_instance_add(emf_struct_t *emf, int8 *inst_id, struct net_device *br_ptr)
{
	emf_info_t *emfi;
	osl_t *osh;
#ifdef CONFIG_PROC_FS
	uint8 proc_name[64];
#endif /* CONFIG_PROC_FS */
	emfc_wrapper_t emfl;

	if (emf->inst_count > EMF_MAX_INST)
	{
		EMF_ERROR("Max instance limit %d exceeded\n", EMF_MAX_INST);
		return (NULL);
	}

	emf->inst_count++;

	EMF_INFO("Creating EMF instance for %s\n", inst_id);

	osh = osl_attach(NULL, PCI_BUS, FALSE);

	ASSERT(osh);

	/* Allocate os specfic EMF info object */
	emfi = MALLOC(osh, sizeof(emf_info_t));
	if (emfi == NULL)
	{
		EMF_ERROR("Out of memory allocating emf_info\n");
		osl_detach(osh);
		return (NULL);
	}

	emfi->osh = osh;

	/* Save the EMF instance identifier */
	strncpy(emfi->inst_id, inst_id, IFNAMSIZ);
	emfi->inst_id[IFNAMSIZ - 1] = 0;

	/* Save the device pointer */
	emfi->br_dev = br_ptr;

	/* Fill the linux wrapper specific functions */
	emfl.forward_fn = (forward_fn_ptr)emf_forward;
	emfl.sendup_fn = (sendup_fn_ptr)emf_sendup;
	emfl.hooks_register_fn = (hooks_register_fn_ptr)emf_hooks_register;
	emfl.hooks_unregister_fn = (hooks_unregister_fn_ptr)emf_hooks_unregister;

	/* Initialize EMFC instance */
	if ((emfi->emfci = emfc_init(inst_id, (void *)emfi, osh, &emfl)) == NULL)
	{
		EMF_ERROR("EMFC init failed\n");
		MFREE(osh, emfi, sizeof(emf_info_t));
		osl_detach(osh);
		return (NULL);
	}

	EMF_INFO("Created EMFC instance for %s\n", inst_id);

	/* Initialize the iflist head */
	emfi->iflist_head = NULL;

#ifdef CONFIG_PROC_FS
	sprintf(proc_name, "emf/emf_stats_%s", inst_id);
	create_proc_read_entry(proc_name, 0, 0, emf_stats_get, emfi);
	sprintf(proc_name, "emf/emfdb_%s", inst_id);
	create_proc_read_entry(proc_name, 0, 0, emf_mfdb_list, emfi);
#endif /* CONFIG_PROC_FS */

	/* Add to the global EMF instance list */
	emfi->next = emf->list_head;
	emf->list_head = emfi;

	return (emfi);
}