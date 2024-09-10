void swap_nodes(node_t *n1, node_t *n2)
{
    if (n1 == NULL || n2 == NULL || n1 == n2)
        return;

    PUTS("swap nodes");

    /* (n1 and n2 are leaves) */
    node_t *pn1 = n1->parent;
    node_t *pn2 = n2->parent;
    bool n1_first_child = is_first_child(n1);
    bool n2_first_child = is_first_child(n2);

    if (pn1 != NULL) {
        if (n1_first_child)
            pn1->first_child = n2;
        else
            pn1->second_child = n2;
    }

    if (pn2 != NULL) {
        if (n2_first_child)
            pn2->first_child = n1;
        else
            pn2->second_child = n1;
    }

    n1->parent = pn2;
    n2->parent = pn1;

    if (n1->vacant != n2->vacant) {
        update_vacant_state(n1->parent);
        update_vacant_state(n2->parent);
    }
}