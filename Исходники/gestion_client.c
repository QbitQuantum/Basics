// Fonction qui indique la connexion d'un joueur aux autres joueurs
void indiquerConnexion(Session *session, Joueur *myJoueur) {
  char buf[TBUF];
  char *plateau;
  ListeJoueurs *listeJ = session->liste;
  pthread_mutex_lock(&(session->liste->mutex));
  pthread_cond_signal(&(session->condConnexion)); // indique que y a 1 connexion
  pthread_mutex_unlock(&(session->liste->mutex));
  printf("[Connexion] : '%s', %d joueurs\n", myJoueur->pseudo, nbJoueurListe(listeJ));
  plateau = session->p->plateauString;
  sprintf(buf, "SESSION/%s/\n", plateau); // plateau provient de session normalement
  sendTo(buf, listeJ, myJoueur, 1); // Send le plateau
}