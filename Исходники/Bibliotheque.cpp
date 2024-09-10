/*
Cette méthode tri le vecteur en fonction du type du tri (par Titre ou Auteur).
Une fois le vecteur trié, on efface la BDD et on recopie chaque élément du vecteur dans le fichier.
Pour le tri, on utilise un tri à bulle.
*/
void Bibliotheque::tri(string pTri)
{
	bool tab_en_ordre = false;
	bool deja_tri = true; 
	//Ce booléen va permettre de savoir si le vecteur est déjà trié, évitant de perdre du temps à le parcourir

	//On vérifie que le choix du tri est valide
    if(pTri == "titre")
    {
		unsigned int taille = this->_bibli.size();

		while(!tab_en_ordre)
		{
		    tab_en_ordre = true;

		    for(unsigned int i=0 ; i < taille-1 ; i++)
		    {
		        if(this->_bibli[i]->getTitre() > this->_bibli[i+1]->getTitre())
		        {
		        	//On compare les titres, et on les échanges si besoin
		            swap(this->_bibli[i], this->_bibli[i+1]);
		            tab_en_ordre = false;
		            deja_tri = false;
		        }
		    }
		    taille--;
		}
	} //Si le Tri est en fonction de l'auteur
	else if (pTri == "auteur")
	{
		unsigned int taille = _bibli.size();

		while(!tab_en_ordre)
		{
		    tab_en_ordre = true;

		    for(unsigned int i=0 ; i < taille-1 ; i++)
		    {
		        if(this->_bibli[i]->getAuteur() > this->_bibli[i+1]->getAuteur())
		        {
		        	//On compare les auteurs, et on les échanges si besoin
		            swap(this->_bibli[i], this->_bibli[i+1]);
		            tab_en_ordre = false;
		            deja_tri = false;
		        }
		    }
		    taille--;
		}
	}
	else cout << "Votre choix de tri n'est pas valide, merci de choisir soit 'auteur' ou 'titre'. " << endl;

	//On affiche si la Bibliothèque à été trié ou non
	if (deja_tri == false)
		cout << "Votre Bibliotheque a ete triee." << endl;
	else
        cout << "Votre Bibliotheque est deja triee" << endl;
	
	
	//On ouvre le fichier et on efface son contenu
	ofstream fichier("Bibli.txt", ios::out | ios::trunc);
   	if(fichier)  // si l'ouverture a réussi
   	{     
   	fichier.close();  // on referme le fichier
    }
    else
     cerr << "Erreur à l'ouverture !" << endl;
	
	//On recopie chaque élément du vecteur dans la BDD
	for (unsigned int u(0); u < this->_bibli.size(); u++)
	{
       this->_bibli[u]->ajout();
	}
}