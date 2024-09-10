// helper function to parse node in tldString
int readTldString(tldnode* node, const wchar_t* s, int len, int pos) {

	int start = pos;
	int state = 0;

	memset(node, 0, sizeof(tldnode));
	do {
		wchar_t c = *(s+pos);

		switch(state) {
			case 0: // general read

				if (c==L',' || c==L')' || c==L'(') {
					// add last domain
					int count = node->attr == THIS ? pos - start : pos - start + 1;
					node->dom = (wchar_t*) malloc(count * sizeof(wchar_t));
					wcsncpy_s(node->dom, count, s+start, _TRUNCATE);

					if (c==L'(') {
						// read number of children
						start = pos;
						state = 1;
					} else if (c==L')' || c==L',') {
						// return to parent domains
						return pos;
					}

				} else if (c==L'!') {
					node->attr=THIS;
				}

				break;
			case 1: // reading number of elements (<number>:

				if (c==L':') {
					int count = pos - start;
					wchar_t* buf = (wchar_t*) malloc(count * sizeof(wchar_t));
					wcsncpy_s(buf, count, s+start+1, _TRUNCATE);
					node->num_children = wcstol(buf, NULL, 10);
					free(buf);

					// allocate space for children
					node->subnodes = (tldnode**) malloc(node->num_children * sizeof(tldnode*));

					int i;
					for (i=0; i<node->num_children; i++) {
						tldnode* subnode = (tldnode*)malloc(sizeof(tldnode));
						pos = readTldString(subnode, s, len, pos + 1);
						node->subnodes[i] = subnode;
					}

					// sort alphabetically for better search performance
					sort(node->subnodes, node->subnodes + node->num_children,
						[] (const tldnode* node1, const tldnode* node2) -> bool {
							// asterisks always comes first
							if (wcscmp(node1->dom, ALL) == 0) return true;
							if (wcscmp(node2->dom, ALL) == 0) return false;
							
							return wcscmp(node1->dom, node2->dom) < 0;
						}
					);

					return pos + 1;
				}

				break;
		}

		pos++;
	} while (pos < len);

	return pos;
}