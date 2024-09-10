int main(int argc, char *argv[])
{
	char *mes;
        retorno *vuelta;
	if (argc < 2) {
		printf( "uso: %s <message>\n", argv[0]);
		return(1);
	}
        mes=argv[1];
        vuelta = printmessage(mes); 
	if (! vuelta->cod_ret ) {
		printf("%s: No puedo grabar su Mensaje \n",
			argv[0]);
		return(1);
	} 
	printf("Mensaje entregado\n");
	printf("Respuesta: %s \n",vuelta->retorno_u.message);
	return(0);
}