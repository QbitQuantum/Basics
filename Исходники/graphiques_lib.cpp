/******************************************************************************
// dessiner_ligne
// ****************************************************************************
// Cette fonction privée permet de dessiner une des lignes de la route.
// ****************************************************************************
// Parametres : ptA, ptB = les 2 extrémités de la ligne à afficher.
******************************************************************************/
static void dessiner_ligne(t_pt2d ptA, t_pt2d ptB)       
{
	setcolor(LIGNE);    
	setlinestyle(SOLID_LINE, 1, 3);

	/****** ARRONDIR LES POINTS ******/
	moveto(ARRONDI(ptA.X), ARRONDI(ptA.Y));  /* Positionner le crayon au debut de la ligne */
		   
	lineto(ARRONDI(ptB.X), ARRONDI(ptB.Y));  /* Faire une ligne jusqu'a l'extremité de fin */
}