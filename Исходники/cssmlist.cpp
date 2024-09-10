//
// Deep-destruction of CssmLists and ListElements.
// The underlying assumption is that all components were allocated from a single
// Allocator in canonical chunks.
//
void ListElement::clear(Allocator &alloc)
{
	switch (type()) {
	case CSSM_LIST_ELEMENT_WORDID:
		break;	// no substructure
	case CSSM_LIST_ELEMENT_DATUM:
		alloc.free(data().data());
		break;
	case CSSM_LIST_ELEMENT_SUBLIST:
		list().clear(alloc);
		break;
	default:
		assert(false);
	}
}