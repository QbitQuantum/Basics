int main(int argc, char *argv[])
{
	char *message;

	if (argc < 2) {
		printf ("usage: %s <message>\n", argv[0]);
		return(1);
	}
	message = argv[1];

	if (!printmessage(message)) {
		printf("%s: No puedo imprimir su Mensaje \n",
			argv[0]);
		return(1);
	} 
	printf("Mensaje entregado\n");
	return(0);
}