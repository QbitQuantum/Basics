static	pANTLR3_COMMON_TOKEN    
getToken	(pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE t)
{
	return t->getToken(t);
}