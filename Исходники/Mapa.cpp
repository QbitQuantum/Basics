void Mapa::mostraMapa() {
	Consola c;
	//couttringstream cout;
	c.setBackgroundColor(c.BRANCO_CLARO);
	c.clrscr();

	c.gotoxy(10, 0);
	c.setTextSize(20, 20);
	c.setTextColor(c.AZUL);
	cout << "Trabalho Realizado por: ";
	c.setTextColor(c.VERDE);
	cout << "F" << (char)160 << "bio Minas";
	c.setTextColor(c.AMARELO_CLARO);
	cout << " & ";
	c.setTextColor(c.VERMELHO_CLARO);
	cout << "Gon" << (char)135 << "alo Lopes";
	c.setTextColor(c.ROXO);
	cout << " @ISEC";

	//c.setBackgroundColor(c.VERDE); 
	

	c.setTextColor(c.PRETO);
	c.setScreenSize(40, 200);
	for (int i = 0; i < 4; i++) 
	{
		c.gotoxy(2 + (i * 21), 4);
		if (i == 0)
			cout << (char)218; // ┌
		else
			cout << (char)194; // ┬ 
		for (int j = 0; j < 20; j++)
			cout << (char)196; // ─

		cout << (char)191; // ┐
		
		c.gotoxy(2 + (i * 21),5);
		cout << (char)179; // │
		if (this->salas[i] != NULL)
			cout << " " << this->salas[i]->getNome();
		c.gotoxy(23 + (i*21), 5);
		cout << (char)179; 

		c.gotoxy(2 + (i * 21), 6);
		cout << (char)179;
		if (this->salas[i] != NULL)
			cout << " " << "Oxigenio: " << this->salas[i]->getOxigenio() ;
		c.gotoxy(23 + (i * 21), 6);
		cout << (char)179;

		c.gotoxy(2 + (i * 21), 7);
		cout << (char)179;
		if (this->salas[i] != NULL)
			cout << " " << "Integridade: " << this->salas[i]->getIntegridade();
		c.gotoxy(23 + (i * 21), 7);
		cout << (char)179;

		c.gotoxy(2 + (i * 21), 8);
		cout << (char)179;
		c.gotoxy(23 + (i * 21), 8);
		cout << (char)179;

		c.gotoxy(2 + (i * 21), 9);
		cout << (char)179;
		if (this->salas[i] != NULL)
			for (int f = 0; f < this->salas[i]->getUnidades().size(); f++)
				cout << " " << this->salas[i]->getUnidades().at(f)->getNome();
		c.gotoxy(23 + (i * 21), 9);
		cout << (char)179;

		c.gotoxy(2 + (i * 21), 10);
		if (i == 0)
			cout << (char)192; // └
		else 
			cout << (char)197; // ┼
		for (int j = 0; j < 20; j++)
			cout << (char)196;
		c.gotoxy(23 + (i * 21), 10);
		if (i == 3)
			cout << (char)197; // ┼
		else
			cout << (char)217; // ┘
	}

	for (int i = 0; i < 4; i++)
	{
		if (i == 3) 
		{
			c.gotoxy(24 + (i * 21), 10);
			for (int j = 0; j < 20; j++)
				cout << (char)196; // ─

			cout << (char)191;
		}
		c.gotoxy(23 + (i * 21), 11);
		cout << (char)179;

		if (this->salas[i + 4] != NULL)
			cout << " " << this->salas[i + 4]->getNome();
		c.gotoxy(44 + (i * 21), 11);
		cout << (char)179;

		c.gotoxy(23 + (i * 21), 12);
		cout << (char)179;
		if (this->salas[i + 4] != NULL)
			cout << " " << "Oxigenio: " << this->salas[i + 4]->getOxigenio();
		c.gotoxy(44 + (i * 21), 12);
		cout << (char)179;

		c.gotoxy(23 + (i * 21), 13);
		cout << (char)179;
		if (this->salas[i + 4] != NULL)
			cout << " " << "Integridade: " << this->salas[i + 4]->getIntegridade();
		c.gotoxy(44 + (i * 21), 13);
		cout << (char)179;

		c.gotoxy(23 + (i * 21), 14);
		cout << (char)179;
		c.gotoxy(44 + (i * 21), 14);
		cout << (char)179;

		c.gotoxy(23 + (i * 21), 15);
		cout << (char)179;
		if (this->salas[i + 4] != NULL)
			for (int f = 0; f < this->salas[i + 4]->getUnidades().size(); f++)
				cout << " " << this->salas[i + 4]->getUnidades().at(f)->getNome();
		c.gotoxy(44+ (i * 21), 15);
		cout << (char)179;

		c.gotoxy(23 + (i * 21), 16);
		if (i == 0)
			cout << (char)192; // └
		else
			cout << (char)197; //
		for (int j = 0; j < 20; j++)
			cout << (char)196;
		c.gotoxy(44 + (i * 21), 16);
		cout << (char)217;
	}

	for (int i = 0; i < 4; i++)
	{
		c.gotoxy(2 + (i * 21), 16);
		if (i == 0)
			cout << (char)218; // ┌
		else
			cout << (char)197; // ┼ 
		for (int j = 0; j < 20; j++)
			cout << (char)196; // ─

		c.gotoxy(2 + (i * 21), 17);
		cout << (char)179; // │
		if (this->salas[i + 8] != NULL)
			cout << " " << this->salas[i + 8]->getNome(); // Nome da Sala
		c.gotoxy(23 + (i * 21), 17);
		cout << (char)179;

		c.gotoxy(2 + (i * 21), 18);
		cout << (char)179;
		if (this->salas[i + 8] != NULL)
			cout << " " << "Oxigenio: " << this->salas[i + 8]->getOxigenio();
		c.gotoxy(23 + (i * 21), 18);
		cout << (char)179;

		c.gotoxy(2 + (i * 21), 19);
		cout << (char)179;
		if (this->salas[i + 8] != NULL)
			cout << " " << "Integridade: " << this->salas[i + 8]->getIntegridade();
		c.gotoxy(23 + (i * 21), 19);
		cout << (char)179;

		c.gotoxy(2 + (i * 21), 20);
		cout << (char)179;
		c.gotoxy(23 + (i * 21), 20);
		cout << (char)179;

		c.gotoxy(2 + (i * 21), 21);
		cout << (char)179;
		if (this->salas[i + 8] != NULL)
			for (int f = 0; f < this->salas[i + 8]->getUnidades().size(); f++)
				cout << " " << this->salas[i + 8]->getUnidades().at(f)->getNome();
		c.gotoxy(23 + (i * 21), 21);
		cout << (char)179;

		c.gotoxy(2 + (i * 21), 22);
		if (i == 0)
			cout << (char)192; // └
		else
			cout << (char)193; // ┴
		for (int j = 0; j < 20; j++)
			cout << (char)196;
		c.gotoxy(23 + (i * 21), 22);
			cout << (char)217; // ┘
	}

	c.gotoxy(135, 4);
	cout << (char)218; // ┌
	for (int j = 0; j < 50; j++)
		cout << (char)196; // ─
	cout << (char)191; // ┐

	for (int z = 5; z <= 22; z++) {

		c.gotoxy(135,z);
		cout << (char)179; // │
		if (z == 6)
			cout << "Nome da Nave: " << this->nome;
		if (z == 7)
			cout << "Distancia Objetivo: " << this->getDistancia();
		if (z == 8)
			cout << "Distancia Que Falta para o Objetivo: " << this->distanciaEmFalta;
		if (z == 9)
			cout << "Turno Numero: " << this->turno;
		if (z == 10)
			cout << "Fase: " << this->fase;
		c.gotoxy(186, z);
		cout << (char)179; // │
	}

	c.gotoxy(135, 22);
	cout << (char)192; // └
	for (int j = 0; j < 50; j++)
		cout << (char)196; // ─
	cout << (char)217; // ┘

	c.gotoxy(0, 25);
	for (int i = 0; i < 200; i++)
		cout << (char)196;

	cout << endl << endl;

	if (turno == 0) {
		this->adicionaSala(new Propulsor("Propulsor", this));
		this->adicionaSala(listaSalas(2));
		this->adicionaSala(listaSalas(3));
		this->adicionaSala(listaSalas(4));
		this->adicionaSala(new SalaMaquinas(this));
		this->adicionaSala(new SuporteVida(this));
		this->adicionaSala(new ControloEscudo(this));
		this->adicionaSala(new Ponte(this));
		this->adicionaSala(new Propulsor("Propulsor", this));
		this->adicionaSala(listaSalas(10));
		this->adicionaSala(listaSalas(11));
		this->adicionaSala(listaSalas(12));

		int sala_i;
		cout << "A que sala pretende adicionar as Unidades: ";
		while (!(cin >> sala_i) || sala_i < 1 || sala_i > 12){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Tenta outra vez: ";
		}

		salas[sala_i - 1]->adicionaUnidade(new MembroTripulacao());
		salas[sala_i - 1]->adicionaUnidade(new MembroTripulacao());
		salas[sala_i - 1]->adicionaUnidade(new MembroTripulacao());

		turno = 1;
	}