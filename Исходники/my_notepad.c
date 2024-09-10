int main(/*int argc, char* argv[]*/){
	char selection;
	char filename[10];
	//if(argc == 0){// si le programme est lancé sans un fichier on affiche le menu
		while(1){
			afficherMenu();
			selection = GetChar();
			switch (selection){
				case '1':// creation du fichier
					creerFichier();
					break;
				case '2' :// ouverture d'un fichier existant
					Printf("Quel fichier voulez vous ouvrir ?\n",0);
					Scanf("%s",filename);
					ouvrirFichier(filename);
					break;
				case '3' : //on quitte l'application
					Printf("Au Revoir\n",0);
					Exit(0);
					break;
				default : // au cas ou on rentre une commande qui n'est pas dans le menu
					Printf("Commande non reconnu\n",0);
					Printf("Fonctionnement : my_notepad <FILE>...\n",0);
					break;
			}
		}
		return 0;
	/*}else{ // si le programme est lancé avec un fichier alors on l'affiche

		// si le fichier existe on l'ouvre
		if(ouvrirFichier(argv[1]) == -1){
			creerFichier(argv[1]);//si le fichier n'existe pas on le crée et on l'ouvre.
		}


	}*/
	//return 0;
}