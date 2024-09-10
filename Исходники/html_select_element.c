static bool is_option(struct dom_node_internal *node, void *ctx);

/**
 * Create a dom_html_select_element object
 *
 * \param doc  The document object
 * \param ele  The returned element object
 * \return DOM_NO_ERR on success, appropriate dom_exception on failure.
 */
dom_exception _dom_html_select_element_create(struct dom_html_document *doc,
		dom_string *namespace, dom_string *prefix,
		struct dom_html_select_element **ele)
{
	struct dom_node_internal *node;

	*ele = malloc(sizeof(dom_html_select_element));
	if (*ele == NULL)
		return DOM_NO_MEM_ERR;
	
	/* Set up vtables */
	node = (struct dom_node_internal *) *ele;
	node->base.vtable = &_dom_html_element_vtable;
	node->vtable = &_protect_vtable;

	return _dom_html_select_element_initialise(doc, namespace, prefix, *ele);
}

/**
 * Initialise a dom_html_select_element object
 *
 * \param doc  The document object