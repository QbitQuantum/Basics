int main(int argc, char* argv[])
{
	int infoMago = 0xFFA82000;
	int opcion = 0;
	unsigned int balas = 0;

	do {
		printf_s("MENU DEL PERSONAJE:\n");

		printf_s("Elija una de las siguientes opciones\n");
		printf_s("1. Mostrar número de balas\n");
		printf_s("2. Añadir balas\n");
		printf_s("3. Comprobar si tienes balas infinitas\n");
		printf_s("4. Activar las balas infinitas\n");
		printf_s("5. Salir\n\n");

		scanf_s("%i", &opcion);
		printf_s("\n");


		switch (opcion) {
		case 1:
			printf_s("Balas en el inventario: %d\n", balasInventario(infoMago));
			printf_s("\n");
			break;
		case 2:
			printf_s("Número de balas actual: %u\n", balasInventario(infoMago));
			printf_s("¿Cuántas balas quieres añadir?: ");
			scanf_s("%i", &balas);
			printf_s("\n");
			if (balas > 255) {
				printf_s("El máximo de balas que puedes llevar es 255\n");
			}
			printf_s("Balas en el inventario: %u\n", anadirBalas(infoMago, balas));
			printf_s("\n");
			break;
		case 3:
			if (comprobarBalasInfinitas(infoMago)) {
				printf_s("Tienes balas infinitas\n");
				printf_s("\n");
			}
			else {
				printf_s("No tienes balas infinitas\n");
				printf_s("\n");
			}
			break;
		case 4:
			if (activarBalasInfinitas(infoMago)) {
				printf_s("Ya tienes balas infinitas\n");
				printf_s("\n");
			}
			else {
				printf_s("No tienes balas infinitas\n");
				printf_s("\n");
			}
			break;
		case 5:
			break;
		}
	} while (opcion != 5);
}