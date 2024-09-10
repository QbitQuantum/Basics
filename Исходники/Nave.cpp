//Salas opcionais
void Nave::DesenhaSalasOpcionais() {
	Consola c;
	int sala,posicao=0;
	string nome;
	/*c.gotoxy(125, 18); cout << "Indique o NUMERO da sala que pretende adicionar a nave e a POSICAO:";
	c.gotoxy(130, 19);  cout << "1: Propulsor Adicional";
	c.gotoxy(130, 20);  cout << "2: Beliches";
	c.gotoxy(130, 21);  cout << "3: Raio Laser";
	c.gotoxy(130, 22);  cout << "4: Auto-Reparador";
	c.gotoxy(130, 23);  cout << "5: Sistema de Seguranca Interno "<<endl;
	c.gotoxy(125, 24); cout << "SALA NUMERO: ";  cin >> sala;
	c.gotoxy(125, 25); cout << "POSICAO: ";  cin >> posicao;*/

	for (unsigned int i = 0; i <= Salas.size(); i++) {
		if (i == 0) {
			c.setTextColor(c.VERMELHO);
			c.gotoxy(16, 16); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.gotoxy(11, 17); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(11, 18); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(11, 19);  cout<<"Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();
		}
		
		if (i == 1) {
			c.setTextColor(c.AZUL);
			c.gotoxy(32, 16); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.setTextColor(c.PRETO);
			c.gotoxy(32, 17); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(32, 18); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(32, 19); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();
		}
		else if (i == 2) {
			c.setTextColor(c.AZUL);
			c.gotoxy(51, 16); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.setTextColor(c.PRETO);
			c.gotoxy(51, 17); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(51, 18); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(51, 19); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();
		}

		else if (i == 3) {
			c.setTextColor(c.AZUL);
			c.gotoxy(71, 16); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.setTextColor(c.PRETO);
			c.gotoxy(71, 17); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(71, 18); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(71, 19); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();
		}

		else if (i == 4) {
			c.setTextColor(c.VERMELHO);
			c.gotoxy(33, 26); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.gotoxy(31, 27); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(31, 28); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(31, 29); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();
		}

		else if (i == 5) {
			c.setTextColor(c.VERMELHO);
			c.gotoxy(53, 26); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.gotoxy(51, 27); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(51, 28); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(51, 29); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();

		}

		else if (i == 6) {
			c.setTextColor(c.VERMELHO);
			c.gotoxy(71, 26); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.gotoxy(71, 27); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(71, 28); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(71, 29); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();
		}
		else if (i == 7) {

			c.setTextColor(c.VERMELHO);
			c.gotoxy(98, 26); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.gotoxy(91, 27); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(91, 28); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(91, 29); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();
		}

		else if (i == 8) {
			c.setTextColor(c.VERMELHO);
			c.gotoxy(16, 36); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.gotoxy(11, 37); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(11, 38); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(11, 39); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();

		}

		else if (i == 9) {
			c.setTextColor(c.AZUL);
			c.gotoxy(31, 36); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.setTextColor(c.PRETO);
			c.gotoxy(31, 37); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(31, 38); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(31, 39); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();

		}

		else if (i == 10) {
			c.setTextColor(c.AZUL);
			c.gotoxy(51, 36); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.setTextColor(c.PRETO);
			c.gotoxy(51, 37); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(51, 38); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(51, 39); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();

		}

		else if (i == 11) {
			c.setTextColor(c.AZUL);
			c.gotoxy(71, 36); cout << Salas[i]->getNomeSala();
			c.setTextColor(c.PRETO);
			c.setTextColor(c.PRETO);
			c.gotoxy(71, 37); cout << "Integridade: "; cout << Salas[i]->getIntegridade();
			c.gotoxy(71, 38); cout << "Oxigenio: "; cout << Salas[i]->getOxigenio();
			c.gotoxy(71, 39); cout << "Tripulacao: ";
			cout << Salas[i]->mostraUnidadesnaSala();


		}


	}
	


		
}