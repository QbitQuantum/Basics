int stail(const char* nomFichier, const unsigned int nbr)
{
    int nbAffichees = nbr;
    
    // Indice de parcours
    int i=0;
    
    // Indicateur d'erreur lors du parcours du fichier / sert aussi de code retour
    int doNotDisplay=0;
    
    // Tampon des positions de debut de lignes
    int *t_positions = malloc(sizeof(int)*100);
    
    // Nombre de lignes dans le fichier
    int nbLignes = 0;
    
    // Tampon de la ligne courante
    char *t_ligne = malloc(sizeof(char)*TAILLE_LIGNE);
    
    FILE *pt_fic = fopen(nomFichier, "r");
    if(NULL==pt_fic)
    {
        printf("Impossible d'ouvrir le fichier %s : (%d) %s\n", nomFichier, errno, strerror(errno));

        // On positionne le code retour
        doNotDisplay=1;
    }
    else
    {        
        // La premiere ligne commence maintenant
        *(t_positions+i)=ftell(pt_fic);        
        if(1L==*(t_positions+i))
        {
            perror("Erreur lors de la lecture");
            doNotDisplay=1;
        }
        i+=1;
        
        // Flag de lecture
        int keepReading=1;
        
        // Boucler sur le fichier pour determiner les positions des debuts de lignes
        while( 1 == keepReading )
        {
            // Lecture d'une nouvelle ligne
            t_ligne = fgets(t_ligne, TAILLE_LIGNE, pt_fic);
            
            // On continue a lire ?
            if(t_ligne==NULL)
            {
                // Stopper la lecture
                keepReading=0;
                
                // On determine la cause de l'erreur
                if(0 != feof(pt_fic))
                {
                    // Fin du fichier atteinte
                    //puts("Fichier parcouru avec succes");
                }
                else
                {
                    // Autre erreur
                    perror("Erreur lors de la lecture");
                    
                    // On n'affichera pas le fichier
                    doNotDisplay=1;
                }
            }
            else
            {
                // Ligne lu en entier ou buffer trop petit ?
                if(NULL==strrchr(t_ligne, '\n'))
                {
                    //DEBUG
                    //printf("(%dd)%s", i, t_ligne);
                    
                    // Buffer trop petit pour contenir la ligne entiere : on continue a lire sans memoriser la position
                }
                else
                {                    
                    //DEBUG
                    //printf("(%d) %s", i, t_ligne);
                    
                    // Memorisation de la position
                    *(t_positions+i)=ftell(pt_fic);
                    if(1L==*(t_positions+i))
                    {
                        perror("Erreur lors de la lecture");
                        doNotDisplay=1;
                    }
                    i+=1;
                }                          
            }
        }//while
        
        
        // --------------------------------------------------------------------------------------------
        // Affichage a la facon de tail si pas d'erreur lors du parcours
        if (1!=doNotDisplay)
        {
            // Tampon de lecture
            char carac=0;
            
            // Nombre de lignes
            nbLignes = i-1;
            
            //printf("\n\nOn finit de lire le fichier. Il y a %d lignes.\nOn va maintenant afficher la fin du fichier, soit les %d dernieres lignes.\n\n", nbLignes, nbAffichees);
            
            // Enlever le flag de fin de fichier
            clearerr(pt_fic);
            
            // Se positionner au bon endroit
            if(nbLignes>nbAffichees)
            {
                fseek(pt_fic, *(t_positions+nbLignes-nbAffichees), SEEK_SET);                
            }
            else
            {
                fseek(pt_fic, *(t_positions), SEEK_SET);
            }
            
            // Affichage 
            while ( EOF!=(carac=fgetc(pt_fic)) )
            {
                putchar(carac);
            }
        }
        
        // Fermeture du fichier
        fclose(pt_fic);
        
    }//Ouverture du fichier
    
    return doNotDisplay;

}//stail   