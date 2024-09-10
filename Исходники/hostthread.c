/*******************************************************************************
 *	NOME:		refresh_messages
 *	FUNÇÃO:		Cuida da mostra de mensagens. Melhora formatacao da exibicao.
 *				Utiliza arquivos para guardar as mensagens recebidas e mostra
 * 				elas sob demanda
 *
 *	RETORNO:	void
 *******************************************************************************/
void refresh_messages(){
	int pos;		//posicao no arquivo de dados
	char check;		//checa se o arquivo esta vazio ou nao
	char option;	//lida com o menu
	char buffer[100];
	int end;

	do{
		printf("Deseja:\n1-Imprimir ultimas mensagens\n2-Imprimir todas as mensagens\n3-Excluir historico completo\n4-Sair\n");

		__fpurge(stdin);
		option = getchar();
		__fpurge(stdin);

		if(option != '4'){
			sem_wait(&sem_file);

			fseek(chat_log, 0, SEEK_END);
			end = ftell(chat_log);
			fseek(chat_log, 0, SEEK_SET);

			//O primeiro caracter do arquivo indica se ele esta vazio ou nao. 0 = vazio, 1 = nao vazio.
			check = fgetc(chat_log);
			if(check == '0'){
				printf("Voce nao recebeu nenhuma mensagem. Nao ha nada para imprimir ou excluir. D:\n");
			}
			else{

				if(option == '1'){
					fread(&pos, sizeof(int), 1, chat_log);
					fseek(chat_log, pos, SEEK_SET);
					if(ftell(chat_log) == (end-1)){
						printf("Voce nao tem nenhuma nova mensagem\n");
					}
					else{
						do{
							fread(&buffer, sizeof(buffer), 1, chat_log);
							printf("%s", buffer);
						}while(ftell(chat_log) != end);
					}
					fseek(chat_log, 0, SEEK_END);
					pos = ftell(chat_log);
					pos--;	//Volta para o ultimo caracter que e um \0. 
					fseek(chat_log, 1, SEEK_SET);
					fwrite(&pos, sizeof(int), 1, chat_log);
				}
				else if(option == '2'){
					fread(&pos, sizeof(int), 1, chat_log);
					do{
						fread(buffer, sizeof(buffer), 1, chat_log);
						printf("%s", buffer);
					}while(ftell(chat_log) != end);
					fseek(chat_log, 0, SEEK_END);
					pos = ftell(chat_log);
					pos--; //Volta para o ultimo caracter que e um \0. 
					fseek(chat_log, 1, SEEK_SET);
					fwrite(&pos, sizeof(int), 1, chat_log);
				}
				else if(option == '3'){
					fseek(chat_log, 0, SEEK_SET);
					fputc('0', chat_log);
				}
			}
			sem_post(&sem_file);
		}
	}while(option != '4');
	sem_post(&sem_client);
}