int two_means(int nb_dimensions,groupe_t *groupe,groupe_t *groupe1,groupe_t *groupe2,
	      int type_donnees)
{
  /*declaration des variables*/
  int i,j,point1,point2,*groupes_des_individus,succes_affectation;
  int compteur_iterations,nb_iterations_two_means,compteur_while;
  double *centre,*centre1,*centre2,inertie_inter_classe_precedente;
  double inertie_inter_classe_courante,meilleure_inertie_inter_classe;
  /*fin declaration des variables*/

  nb_iterations_two_means=10;
  meilleure_inertie_inter_classe=NOT_DEFINED;
  
  /*allocation memoire*/
  centre1=(double *)malloc(sizeof(double)*nb_dimensions);
  centre2=(double *)malloc(sizeof(double)*nb_dimensions);
  centre=(double *)malloc(sizeof(double)*nb_dimensions);
  groupes_des_individus=(int *)malloc(sizeof(int)*groupe->nb_individus);
  /*fin allocation memoire*/

  if((type_donnees==SIMILARITES)||(type_donnees==ALIGNEMENT))
    {
      for(i=0;i<groupe->nb_individus;i++)
	{
	  centre[i]=0;
	  for(j=0;j<groupe->nb_individus;j++)
	    {
	      centre[i]+=groupe->individus[j]->valeurs_traitees[groupe->individus[i]->id];
	    }
	  centre[i]/=(double)groupe->nb_individus;
	}
    }
  else
    {
      for(i=0;i<nb_dimensions;i++)
	{
	  centre[i]=0;
	  for(j=0;j<groupe->nb_individus;j++)
	    {
	      centre[i]+=groupe->individus[j]->valeurs_traitees[i];
	    }
	  centre[i]/=(double)groupe->nb_individus;
	}
    }

  for(compteur_iterations=0;compteur_iterations<nb_iterations_two_means;compteur_iterations++)
    {
      point1=(int)floor((double)groupe->nb_individus-1.0)*((double)rand()/(double)RAND_MAX);
      compteur_while=0;
      while(compteur_while<50)
	{
	  point2=(int)floor((double)groupe->nb_individus-1.0)*((double)rand()/(double)RAND_MAX);
	  if(calcul_distance(nb_dimensions,groupe->individus[point1]->valeurs_traitees,
			     groupe->individus[point2]->valeurs_traitees)>ZERO_LIMIT)
	    {
	      break;
	    }
	  compteur_while++;
	}
      if(compteur_while==50)
	{
	  return NON;
	}

      /*initialisation*/
      if((type_donnees==SIMILARITES)||(type_donnees==ALIGNEMENT))
	{
	  for(i=0;i<groupe->nb_individus;i++)
	    {
	      centre1[i]=
		groupe->individus[point1]->valeurs_traitees[groupe->individus[i]->id];
	      centre2[i]=
		groupe->individus[point2]->valeurs_traitees[groupe->individus[i]->id];
	    }
	}
      else
	{
	  for(i=0;i<nb_dimensions;i++)
	    {
	      centre1[i]=groupe->individus[point1]->valeurs_traitees[i];
	      centre2[i]=groupe->individus[point2]->valeurs_traitees[i];
	    }
	}

      /*premiere affectation des individus aux deux groupes*/
      succes_affectation=
	affectation_individus2means(nb_dimensions,groupe->nb_individus,groupe->individus,
				    centre1,centre2,groupes_des_individus,
				    &inertie_inter_classe_precedente,type_donnees,centre);
      if(succes_affectation==NON)
	{
	  return NON;
	}

      /*fin initialisation*/
      compteur_while=0;
      while(compteur_while<10)
	{
	  succes_affectation=
	    affectation_individus2means(nb_dimensions,groupe->nb_individus,groupe->individus,
					centre1,centre2,groupes_des_individus,
					&inertie_inter_classe_courante,type_donnees,centre);
	  if(succes_affectation==NON)
	    {
	      return NON;
	    }

	  if((inertie_inter_classe_courante-inertie_inter_classe_precedente<ZERO_LIMIT)&&
	     (-inertie_inter_classe_courante+inertie_inter_classe_precedente<ZERO_LIMIT))
	    {
	      break;
	    }
	  else
	    {
	      inertie_inter_classe_precedente=inertie_inter_classe_courante;
	    }
	  compteur_while++;
	}
      
      if((meilleure_inertie_inter_classe==NOT_DEFINED)||
	 (inertie_inter_classe_courante>meilleure_inertie_inter_classe))
	{
	  groupe1->nb_individus=0;
	  groupe2->nb_individus=0;
	  for(i=0;i<groupe->nb_individus;i++)
	    {
	      if(groupes_des_individus[i]==GROUPE1)
		{
		  groupe1->individus[groupe1->nb_individus]=groupe->individus[i];
		  (groupe1->nb_individus)++;
		}
	      else
		{
		  groupe2->individus[groupe2->nb_individus]=groupe->individus[i];
		  (groupe2->nb_individus)++;
		}
	    }
	  meilleure_inertie_inter_classe=inertie_inter_classe_courante;
	}
    }      

  /*desallocation memoire*/
  free(centre1);
  free(centre2);
  free(centre);
  free(groupes_des_individus);
  /*fin desallocation memoire*/

  return OUI;
}