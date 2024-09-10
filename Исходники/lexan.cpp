int Lexan::getNextToken()
{
	int State = 0;
	char Char;
	int Exp = 0, ExpSign = 1; /* Velikost a znamenko exponentu */
	double DmsPos = 0.1; /* prave zpracovavany desetinny rad */

	while (true) {	
		Char = getChar();
		switch (State) 
		{
			case 0:
				if (Char == ' ' || Char == '\n' || Char == '\t' || Char == '\r')
					break;
				if (Char == ';')
					return (LEX_SEMICOLON);
				if (Char == '/') {
					State = 2;
					break;
				}				
				if (Char == '=') {
					State = 29;
					break;
				}			
				if (Char == '*') {
					State = 25;
					break;
				}
				if (Char == '(')
					return (LEX_LPA);
				if (Char == ')')
					return (LEX_RPA);							
				if (Char == '}')
					return (LEX_END);
				if (Char == '{')
					return (LEX_BEGIN);								
				if (isalpha(Char)) {
					identifierName = ""; 		//na zacatku je string nazvu prazdny			
					identifierName += Char;		//prvni znak identifikatoru
					State = 38;
					break;
				}				
				if (Char == '0') {
					intValue = 0;
					floatValue = 0.0;
					State = 7;
					break;
				}
				if (isdigit(Char)) 	//nula je chycana drive
				{ 
					intValue = Char - '0';
					floatValue = Char - '0';
					State = 11;
					break;
				}
				if (Char == '+')
				{
					State = 17;
					break;
				}
				if (Char == '-')
				{
					State = 20;
					break;
				}
				if (Char == '%')
				{
					State = 27;
					break;
				}
				if (Char == '!') {
					State = 31;
					break;
				}
				if (Char == '<')
				{
					State = 33;
					break;
				}
				if (Char == '>')
				{
					State = 35;
					break;
				}
				if (Char == '.') {
					floatValue = 0.0;
					DmsPos = 0.1;
					State = 16;
					break;
				}				
				if (Char == EOF)
					return (LEX_NULL);

				return (LEX_ERROR);								


			case 2:
				if (Char == '/') {	//jednoradkovy komentar
					State = 4;
					break;
				}
				if (Char == '=') {	//operator /=				
					return (LEX_DIVASSIGN);
				}
				if (Char == '*') {
					State = 5;
					break;
				}				

				ungetChar(Char);		//operator /
				return (LEX_DIV);


			case 4:
				if (Char == '\n') 
				{
					State = 0;
					break;
				}
				if (Char == EOF)
					return (LEX_ERROR); 
				break; 			//pokud by byl eof uvnitr
								// komentare zustava ve stavu 4

			case 5:
				if (Char == '*')
				{
					State = 6;
					break;
				}
				if(Char == LEX_EOF)			
					return (LEX_ERROR);				

				
			case 6:
				if (Char == '/') {	//konec komentare
					State = 0;
					break;
				}
				if (Char != '*')
				{
					State = 5;
					break;
				}
				
				break;			//state porad = 6 pri *


			case 7:
				if (isodigit(Char)) {
					State = 8;
					intValue = Char - '0';
					break;
				}
				if(Char == 'x' || Char == 'X')
				{				
					State = 9;
					break;
				}
				if(Char == '.')
				{
					State = 12;
					break;
				}
				if (Char == EOF)
					return (LEX_ERROR); 
				if(isalpha(Char))
					return (LEX_ERROR);

				ungetChar(Char);
				cout << "intValue = " << intValue << endl;
				return (LEX_INT);		//pokud neni ani okta ani hexa


			case 8:
				if (isodigit(Char)) {
					intValue = (intValue << 3) + (Char - '0');
					State = 8; 		//state bude porad 8
					break;
				}
				if(isalpha(Char))
					return (LEX_ERROR);

				ungetChar(Char);
				cout << "intValue = " << intValue << endl;
				return(LEX_INT);


			case 9:
				if(isxdigit(Char))
				{			
					Char = (char)toupper(Char);		
					intValue = (Char >= 'A') ? Char - 'A' + 10 : Char - '0';
					State = 10;
					break;
				}
				return(LEX_ERROR);


			case 10:				
				if (isxdigit(Char)) {
					Char = (char)toupper(Char); 
					intValue = (intValue << 4) + ((Char >= 'A') ? Char - 'A' + 10 : Char - '0');					
					break;
				}
			

			case 11:
				if(isdigit(Char))
				{
					intValue = intValue * 10 + Char - '0';
					floatValue = floatValue * 10.0 + Char - '0';
					break;
				}
				if(Char == '.')
				{
					State = 12;
					break;
				}
				if(isalpha(Char))
					return (LEX_ERROR);					

				ungetChar(Char); 		// nalezen integer 
				cout << "intValue = " << intValue << endl;
				return (LEX_INT);				
			

			case 12:
				if(isdigit(Char))
				{
					floatValue += DmsPos * (Char - '0'); 
					DmsPos /= 10.0; 	// pocitat intValue
					break;
				}
				if(Char == 'E' || Char == 'e')
				{	
					Exp = 0;
					ExpSign = 1;
					State = 13;
					break;
				}
				if(isalpha(Char))
					return (LEX_ERROR);

				ungetChar(Char); 		//desetinne cislo s jednim destinnym mistem
				cout << "floatValue = " << floatValue << endl;
				return (LEX_FLOAT);

			
			case 13:
				if(isdigit(Char))
				{
					Exp = Char - 0x30;
					State = 15;
					break;
				}
				if (Char == '+' || Char == '-') {
					ExpSign = (Char == '-') ? -1 : 1;						
					State = 14;
					break;
				}
				return (LEX_ERROR);


			case 14:
				if(isdigit(Char))
				{
					Exp = Char - 0x30;
					State = 15;
					break;
				}

				return (LEX_ERROR);

			
			case 15:
				if(isdigit(Char))
				{
					Exp = 10 * Exp + Char - 0x30; //dalsi cifry exponentu
					break;
				}
				
				ungetChar(Char);
				floatValue *= pow(10.0, Exp * ExpSign);
				cout << "floatValue = " << floatValue << endl;
				return (LEX_FLOAT);


			case 16:
				if(isdigit(Char))	
				{		
					floatValue = 0.1 * (Char - '0');
					DmsPos = 0.01; 			//priste jsou zpracovavany setiny
					State = 12;
					break;
				}


			case 17:
				if (Char == '=' || Char == '+') // ==
				{
					if(Char == '=')
					{
						State = 18;
						ungetChar(Char);
						break;
					}
					if (Char == '+')				
					{
						State = 19;
						ungetChar(Char);
						break;
					}
				}
				else
				{
					ungetChar(Char);
					return (LEX_ADD);
				}
			

			case 18:
				if(Char == '=')
					return LEX_ADDASSIGN; 
				else {
					ungetChar(Char); // jenom =
					return LEX_ADD;
				}
		

			case 19:			
				if(Char == '+')
					return (LEX_INCREMENT);
				else
				{	
					ungetChar(Char);
					return (LEX_ADD);
				}
			

			case 20:
				if(Char == '=' || Char == '-')
				{
					if(Char == '=')
					{
						State = 22;
						ungetChar(Char);
						break;
					
					}
					if(Char == '-')
					{
						State = 21;
						ungetChar(Char);
						break;
					}
				}
				else
				{
					ungetChar(Char);
					return (LEX_SUB);
				}


			case 21:
				if(Char == '-')				
					return (LEX_DECREMENT);
				else
				{
					ungetChar(Char);
					return (LEX_SUB);
				}	
			
			case 22:
				if(Char == '=')
					return (LEX_SUBASSIGN);
				else
				{
					ungetChar(Char);
					return (LEX_SUB);
				}				

			
			case 25:
				if(Char == '=')
					return (LEX_MULASSIGN);
				else
				{
					ungetChar(Char);
					return (LEX_MUL);	
				}

			case 27:
				if(Char == '=')
					return (LEX_MODASSIGN);
				else
				{	
					ungetChar(Char);
					return (LEX_MOD);
				}

			
			case 29:
				if(Char == '=')
					return (LEX_ISEQUAL);
				else
				{
					ungetChar(Char);
					return (LEX_ASSIGN);
				}
		
			case 31:
				if(Char == '=')
					return (LEX_ISNEQUAL);
				else
				{
					ungetChar(Char);
					return (LEX_EXCLAMATION);
				}

			case 33:
				if(Char == '=')
					return (LEX_LESS_EQU_THAN);
				else
				{
					ungetChar(Char);
					return (LEX_LESS_THAN);
				}

			case 35:
				if(Char == '=')
					return (LEX_GREATER_EQU_THAN);
				else
				{
					ungetChar(Char);
					return (LEX_GREATER_THAN);
				}
			
			case 38:
				if(isalpha(Char) || isdigit(Char))
				{
					identifierName += Char;				
					break;
				} else {				

					ungetChar(Char);
					map<int, string>::iterator i;

					for (i = keywords.begin(); i != keywords.end(); i++)
						if (identifierName.compare(i->second) == 0)
						{
							cout << "keyword: " << i->second << endl;
							return (i->first);
						}

					//identifikator nebyl nalezen v klicovych slovech
					cout << "identifier: " << identifierName << endl;
					return (LEX_IDENT);
				}

			default:
				throw "Lexical ERROR: unknown state";
				break;
		}
	}
}