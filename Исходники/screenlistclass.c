STATIC SIPTR ScreenCompareFunc(struct Hook *h, struct ScreenNode *node1, struct ScreenNode *node2)
{
	return Stricmp(node2->title, node1->title);
}