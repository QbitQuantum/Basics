void
acpi_ut_init_globals (
    void)
{
    u32                     i;


    FUNCTION_TRACE ("Ut_init_globals");

    /* Memory allocation and cache lists */

    MEMSET (acpi_gbl_memory_lists, 0, sizeof (ACPI_MEMORY_LIST) * ACPI_NUM_MEM_LISTS);

    acpi_gbl_memory_lists[ACPI_MEM_LIST_STATE].link_offset      = (u16) (NATIVE_UINT) &(((acpi_generic_state *) NULL)->common.next);
    acpi_gbl_memory_lists[ACPI_MEM_LIST_PSNODE].link_offset     = (u16) (NATIVE_UINT) &(((acpi_parse_object *) NULL)->next);
    acpi_gbl_memory_lists[ACPI_MEM_LIST_PSNODE_EXT].link_offset = (u16) (NATIVE_UINT) &(((acpi_parse2_object *) NULL)->next);
    acpi_gbl_memory_lists[ACPI_MEM_LIST_OPERAND].link_offset    = (u16) (NATIVE_UINT) &(((acpi_operand_object *) NULL)->cache.next);
    acpi_gbl_memory_lists[ACPI_MEM_LIST_WALK].link_offset       = (u16) (NATIVE_UINT) &(((acpi_walk_state *) NULL)->next);

    acpi_gbl_memory_lists[ACPI_MEM_LIST_NSNODE].object_size     = sizeof (acpi_namespace_node);
    acpi_gbl_memory_lists[ACPI_MEM_LIST_STATE].object_size      = sizeof (acpi_generic_state);
    acpi_gbl_memory_lists[ACPI_MEM_LIST_PSNODE].object_size     = sizeof (acpi_parse_object);
    acpi_gbl_memory_lists[ACPI_MEM_LIST_PSNODE_EXT].object_size = sizeof (acpi_parse2_object);
    acpi_gbl_memory_lists[ACPI_MEM_LIST_OPERAND].object_size    = sizeof (acpi_operand_object);
    acpi_gbl_memory_lists[ACPI_MEM_LIST_WALK].object_size       = sizeof (acpi_walk_state);

    acpi_gbl_memory_lists[ACPI_MEM_LIST_STATE].max_cache_depth  = MAX_STATE_CACHE_DEPTH;
    acpi_gbl_memory_lists[ACPI_MEM_LIST_PSNODE].max_cache_depth = MAX_PARSE_CACHE_DEPTH;
    acpi_gbl_memory_lists[ACPI_MEM_LIST_PSNODE_EXT].max_cache_depth = MAX_EXTPARSE_CACHE_DEPTH;
    acpi_gbl_memory_lists[ACPI_MEM_LIST_OPERAND].max_cache_depth = MAX_OBJECT_CACHE_DEPTH;
    acpi_gbl_memory_lists[ACPI_MEM_LIST_WALK].max_cache_depth   = MAX_WALK_CACHE_DEPTH;

    ACPI_MEM_TRACKING (acpi_gbl_memory_lists[ACPI_MEM_LIST_GLOBAL].list_name    = "Global Memory Allocation");
    ACPI_MEM_TRACKING (acpi_gbl_memory_lists[ACPI_MEM_LIST_NSNODE].list_name    = "Namespace Nodes");
    ACPI_MEM_TRACKING (acpi_gbl_memory_lists[ACPI_MEM_LIST_STATE].list_name     = "State Object Cache");
    ACPI_MEM_TRACKING (acpi_gbl_memory_lists[ACPI_MEM_LIST_PSNODE].list_name    = "Parse Node Cache");
    ACPI_MEM_TRACKING (acpi_gbl_memory_lists[ACPI_MEM_LIST_PSNODE_EXT].list_name = "Extended Parse Node Cache");
    ACPI_MEM_TRACKING (acpi_gbl_memory_lists[ACPI_MEM_LIST_OPERAND].list_name   = "Operand Object Cache");
    ACPI_MEM_TRACKING (acpi_gbl_memory_lists[ACPI_MEM_LIST_WALK].list_name      = "Tree Walk Node Cache");

    /* ACPI table structure */

    for (i = 0; i < NUM_ACPI_TABLES; i++)
    {
        acpi_gbl_acpi_tables[i].prev        = &acpi_gbl_acpi_tables[i];
        acpi_gbl_acpi_tables[i].next        = &acpi_gbl_acpi_tables[i];
        acpi_gbl_acpi_tables[i].pointer     = NULL;
        acpi_gbl_acpi_tables[i].length      = 0;
        acpi_gbl_acpi_tables[i].allocation  = ACPI_MEM_NOT_ALLOCATED;
        acpi_gbl_acpi_tables[i].count       = 0;
    }


    /* Address Space handler array */

    for (i = 0; i < ACPI_NUM_ADDRESS_SPACES; i++)
    {
        acpi_gbl_address_spaces[i].handler  = NULL;
        acpi_gbl_address_spaces[i].context  = NULL;
    }

    /* Mutex locked flags */

    for (i = 0; i < NUM_MTX; i++)
    {
        acpi_gbl_acpi_mutex_info[i].mutex   = NULL;
        acpi_gbl_acpi_mutex_info[i].owner_id = ACPI_MUTEX_NOT_ACQUIRED;
        acpi_gbl_acpi_mutex_info[i].use_count = 0;
    }

    /* Global notify handlers */

    acpi_gbl_sys_notify.handler         = NULL;
    acpi_gbl_drv_notify.handler         = NULL;

    /* Global "typed" ACPI table pointers */

    acpi_gbl_RSDP                       = NULL;
    acpi_gbl_XSDT                       = NULL;
    acpi_gbl_FACS                       = NULL;
    acpi_gbl_FADT                       = NULL;
    acpi_gbl_DSDT                       = NULL;

    /* Global Lock support */

    acpi_gbl_global_lock_acquired       = FALSE;
    acpi_gbl_global_lock_thread_count   = 0;

    /* Miscellaneous variables */

    acpi_gbl_system_flags               = 0;
    acpi_gbl_startup_flags              = 0;
    acpi_gbl_rsdp_original_location     = 0;
    acpi_gbl_cm_single_step             = FALSE;
    acpi_gbl_db_terminate_threads       = FALSE;
    acpi_gbl_shutdown                   = FALSE;
    acpi_gbl_ns_lookup_count            = 0;
    acpi_gbl_ps_find_count              = 0;
    acpi_gbl_acpi_hardware_present      = TRUE;
    acpi_gbl_next_table_owner_id        = FIRST_TABLE_ID;
    acpi_gbl_next_method_owner_id       = FIRST_METHOD_ID;
    acpi_gbl_debugger_configuration     = DEBUGGER_THREADING;

    /* Hardware oriented */

    acpi_gbl_gpe0enable_register_save   = NULL;
    acpi_gbl_gpe1_enable_register_save  = NULL;
    acpi_gbl_original_mode              = SYS_MODE_UNKNOWN;   /*  original ACPI/legacy mode   */
    acpi_gbl_gpe_registers              = NULL;
    acpi_gbl_gpe_info                   = NULL;

    /* Namespace */

    acpi_gbl_root_node                  = NULL;

    acpi_gbl_root_node_struct.name      = ACPI_ROOT_NAME;
    acpi_gbl_root_node_struct.data_type = ACPI_DESC_TYPE_NAMED;
    acpi_gbl_root_node_struct.type      = ACPI_TYPE_ANY;
    acpi_gbl_root_node_struct.child     = NULL;
    acpi_gbl_root_node_struct.peer      = NULL;
    acpi_gbl_root_node_struct.object    = NULL;
    acpi_gbl_root_node_struct.flags     = ANOBJ_END_OF_PEER_LIST;


#ifdef ACPI_DEBUG
    acpi_gbl_lowest_stack_pointer       = ACPI_UINT32_MAX;
#endif

    return_VOID;
}