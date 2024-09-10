void cadastrar(Hashtable *table) {
	Jogador player;
	Chave key;

	readData(&player);

	strcpy(key.pk, player.pk);
	key.rrn = (strlen(ARQUIVO) / TAM_REGISTRO);

	if(buscaLista(table, key)) {
		printf(ERRO_PK_REPETIDA, key.pk);
	} else {
		if(insereLista(table, key))
			insertFile(player, key.rrn);
			printf(REGISTRO_INSERIDO, key.pk);
	}

}