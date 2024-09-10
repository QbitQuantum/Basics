static int discover(opal_list_t* nodelist, ICluster* pCluster)
{
    int ret = ORTE_ERROR;
    int32_t nodeid;
    orte_node_t *node;
    opal_list_item_t* item;
    opal_list_t new_nodes;
    struct timeval start, stop;

    HRESULT hr = S_OK;  
    long idle_processors = 0;
    IClusterEnumerable* pNodesCollection = NULL;
    IEnumVARIANT* pNodes = NULL;
    INode* pNode = NULL;
    BSTR node_name = NULL, node_arch = NULL;
    VARIANT var;
    NodeStatus Status;
    size_t len;

    /* check for timing request - get start time if so */
    if (orte_timing) {
        gettimeofday(&start, NULL);
    }
    
    /* Get the collection of nodes. */
    hr = pCluster->get_ComputeNodes(&pNodesCollection);
    if (FAILED(hr)) {
        ras_get_cluster_message(pCluster);
        OPAL_OUTPUT_VERBOSE((1, orte_ras_base.ras_output,
                            "ras:ccp:pCluster->get_ComputeNodes failed."));
        return ORTE_ERROR;
    }

    /* Get the enumerator used to iterate through the collection. */
    hr = pNodesCollection->GetEnumerator(&pNodes);
    if (FAILED(hr)) {
        ras_get_cluster_message(pCluster);
        OPAL_OUTPUT_VERBOSE((1, orte_ras_base.ras_output,
                            "ras:ccp:pNodesCollection->GetEnumerator failed."));
        return ORTE_ERROR;
    }

    VariantInit(&var);

    /* Construct new node list. */
    OBJ_CONSTRUCT(&new_nodes, opal_list_t);
    nodeid=0;

    /* Loop through the collection. */
    while (hr = pNodes->Next(1, &var, NULL) == S_OK) {
        var.pdispVal->QueryInterface(IID_INode, reinterpret_cast<void **> (&pNode));

        /* Check wether the node is ready. 
         * There are four states:
         *          NodeStatus_Ready = 0,
         *          NodeStatus_Paused = 1,
         *          NodeStatus_Unreachable = 2, probably not a windows cluster node.
         *          NodeStatus_PendingApproval = 3
         */
        hr = pNode->get_Status(&Status);
        if (FAILED(hr)) {
            OPAL_OUTPUT_VERBOSE((1, orte_ras_base.ras_output,
                                "ras:ccp:pNode->get_Status failed."));
            ret = ORTE_ERROR;
            goto cleanup;
        }

        /* Get available number of processors on each node. */
        hr = pNode->get_NumberOfIdleProcessors(&idle_processors);
        if (FAILED(hr)) {
            OPAL_OUTPUT_VERBOSE((1, orte_ras_base.ras_output,
                                "ras:ccp:pNode->get_NumberOfIdleProcessors failed."));
            ret = ORTE_ERROR;
            goto cleanup;
        }

        /* Do we have enough processors on the available nodes? 
         * Question: How do we get the required number of processors?
         */
        if ( (Status == NodeStatus_Ready) && (idle_processors > 0) ) {

            /* Get node name. */
            hr = pNode->get_Name(&node_name);
            if (FAILED(hr)) {
                OPAL_OUTPUT_VERBOSE((1, orte_ras_base.ras_output,
                                    "ras:ccp:pNode->get_Name failed."));
                ret = ORTE_ERROR;
                goto cleanup;
            }

            /* Get node processor architecture. */
            hr = pNode->get_ProcessorArchitecture(&node_arch);
            if (FAILED(hr)) {
                OPAL_OUTPUT_VERBOSE((1, orte_ras_base.ras_output,
                                    "ras:ccp:pNode->get_ProcessorArchitecture failed."));
                ret = ORTE_ERROR;
                goto cleanup;
            }

            /* Prevent duplicated nodes in the list*/
            for (item = opal_list_get_first(&new_nodes);
                 opal_list_get_end(&new_nodes) != item;
                 item = opal_list_get_next(item)) {

                node = (orte_node_t*) item;
                if (0 == strcmp(node->name, (char *)node_name)) {
                    ++node->slots;
                    OPAL_OUTPUT_VERBOSE((1, orte_ras_base.ras_output,
                                        "ras:ccp:allocate:discover: found -- bumped slots to %d",
                                        node->slots));
                    break;
                }
            }
            /* Did we find it? */

            if (opal_list_get_end(&new_nodes) == item) {

                /* Nope -- didn't find it, so add a new item to the list */

                OPAL_OUTPUT_VERBOSE((1, orte_ras_base.ras_output,
                                    "ras:ccp:allocate:discover: not found -- added to list"));

                node = OBJ_NEW(orte_node_t);

                /* The function _dupenv_s is much safer than getenv on Windows. */
                _dupenv_s(&node->username, &len, "username");

                node->name = _com_util::ConvertBSTRToString(node_name);
                node->launch_id = nodeid;
                node->slots_inuse = 0;
                node->slots_max = 0;
                node->slots = 1;
                opal_list_append(nodelist, &node->super);
            } 
            /* up the nodeid */
            nodeid++;
        }

        pNode->Release();
        VariantClear(&var);
    }

    pNodes->Release();

    if (nodeid > 0) ret = ORTE_SUCCESS;

    /* All done */
cleanup:

    if (ORTE_SUCCESS == ret) {
        OPAL_OUTPUT_VERBOSE((1, orte_ras_base.ras_output,
                            "ras:ccp:allocate:discover: success"));
    } else {
        OPAL_OUTPUT_VERBOSE((1, orte_ras_base.ras_output,
                            "ras:ccp:allocate:discover: failed (rc=%d)", ret));
    }

    OBJ_DESTRUCT(&new_nodes);
    SysFreeString(node_name);
    SysFreeString(node_arch);

    /* check for timing request - get stop time and report elapsed time if so */
    if (orte_timing) {
        gettimeofday(&stop, NULL);
        opal_output(0, "ras_ccp: time to allocate is %ld usec",
                    (long int)((stop.tv_sec - start.tv_sec)*1000000 +
                               (stop.tv_usec - start.tv_usec)));
        gettimeofday(&start, NULL);
    }
    
    return ret;
}