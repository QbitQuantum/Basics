/**
 Zapisuje do pliku dany węzęł
 @param[in] node Węzeł
 @param[out] stream Plik
 @return Czy się udało
 */
static bool node_save(trie_node *node, FILE *stream)
{
	for(int i = 0; i < vector_size(node->sons); i++)
	{
		if(putwc(NTH_SON_CHAR(node, i), stream) == WEOF)
			return false;
		if(!node_save(NTH_SON(node, i), stream))
			return false;
	}
	if(putwc(node->end_of_word ? END_OF_WORD : NOT_END_OF_WORD, stream) == WEOF)
		return false;
	return true;
}