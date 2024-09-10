void mc_fstr(double valeur, int signe, int nbint, int nbfrac,int zeros,char *chaine)
/***************************************************************************/
/* Formatage d'une chaine de sortie a partir d'une valeur numerique.       */
/***************************************************************************/
/* valeur : valeur numerique a formater                                    */
/* signe : =OK pour ajouter + ou - devant la chaine                        */
/*         =PBB pour ajouter ' ' ou - devant la chaine                     */
/*         =PB pour la valeur absolue                                      */
/* nbint : nombre de chiffres pour la partie entiere                       */
/* nbfrac : nombre de chiffres pour la partie decimale                     */
/* zeros  : =OK pour laisser les zeros devant sinon (=PB) des espaces      */
/***************************************************************************/
{
   double v,vint,vfrac,cstint,cstfrac;
   int s,dec,lon,k,ssigne;
   char chaines[3],chaine1[84],chaine2[84],chaine3[84],chainezero[84];

   /*--- test de depassement de chaine ---*/
   memset(chaine3,'-',83);chaine3[83]='\0';
   lon=0;
   if (signe==1) {
      lon+=1;
   }
   if (nbfrac>0) {
      lon+=1;
   }
   lon+=(nbint+nbfrac);
   if (lon>(int)(strlen(chaine3))) {
      memset(chaine3,'-',strlen(chaine3));chaine3[strlen(chaine3)]='\0';
      strcpy(chaine,chaine3);
      return;
   }

   /*--- constantes multiplicatives pour les parties entieres et decimales */
   cstint =pow(10,nbint ) ;
   cstfrac=pow(10,nbfrac) ;

   /*--- on traite le signe ---*/
   s=(int) (mc_sgn(valeur));
   if (signe==OK) {
      if (s>=0) { strcpy(chaines,"+"); } else { strcpy(chaines,"-"); }
   } else if (signe==PBB) {
      if (s>=0) { strcpy(chaines," "); } else { strcpy(chaines,"-"); }
   } else {
      strcpy(chaines,"");
   }

   /*--- on arondit la valeur tronquee ---*/
   v=fabs(valeur);
   vfrac=mc_frac(v*cstfrac);
   vint=floor(v*cstfrac);
   if (vfrac>=.5) {
      v=(vint+1.)/cstfrac;
   }

   /*--- on traite la partie entiere ---*/
   vint=floor(v);
   if (vint>=cstint) {
      vint=cstint-1;
   }
   vint+=cstint;
   strcpy(chaine1,fcvt(vint,nbint+2,&dec,&ssigne)+1);
   *(chaine1+nbint)='\0';
   if ((nbint>1)&&(zeros==PB)) {
      for (k=1;k<=nbint-1;k++) {
         if (chaine1[k-1]=='0') {
            if (signe==PB) {
               chaine1[k-1]=' ';
            } else {
               if (k==1) {
                  chaine1[k-1]=chaines[0];
                  chaines[0]=' ';
               } else {
                  chaine1[k-1]=chaine1[k-2];
                  chaine1[k-2]=' ';
               }
            }
         } else {
            break;
         }
      }
   }

   /*--- on traite la partie decimale ---*/
   if (nbfrac==0) {
      strcpy(chaine2,"");
   } else {
      vfrac=cstfrac+floor(mc_frac(v)*(cstfrac+.1));
      strcpy(chaine2,fcvt(vfrac,nbfrac+2,&dec,&ssigne)+1);
      memset(chainezero,'0',nbfrac);chainezero[nbfrac]='\0';
      strcat(chaine2,chainezero);
      *(chaine2+nbfrac)='\0';
   }

   /*--- creation de la chaine de sortie formatee ---*/
   strcpy(chaine3,chaines);
   strcat(chaine3,chaine1);
   if (nbfrac>0) {
      strcat(chaine3,".");
      strcat(chaine3,chaine2);
   }
   strcpy(chaine,chaine3);
   return;
}