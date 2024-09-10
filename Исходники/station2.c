/**
 * Realise le parcourt avec la piece courante
 */
void processPiece()
{
    // Attend que la station 1 nous ai donne une piece
    printf("Attend que la station 1 nous ai donne une piece ...\n");
    while(!getPieceReceived())
        waitTime(500);
    
    printf("Attend que la piece soit en place ...\n");
    waitBit(PIECE, TRUE);
    waitTime(1000);
    
    // Regarde si c'est une piece metallique
    pieceMetal = getCapteur(PIECE_METAL);
    if(pieceMetal) {
        printf("--->>> Piece en métal\n");
        SendTo(station_3, ADDR_STATION_3, PORT_LISTEN_3_2, "PIECE_METAL", 11);
    }
    
    // Monte l'ascenseur
    printf("Monte l'ascensseur ...\n");
    setActuateur(ASC_DESCEND, OFF);
    setActuateur(ASC_MONTE, ON);
    waitBit(ASC_HAUT, TRUE);
    setActuateur(ASC_MONTE, OFF);
    
    waitTime(1000);
    
    // Piece noire
    pieceNoire = !getCapteur(HAUTEUR_PIECE);
    if(pieceNoire && !pieceMetal) {
        printf("--->>> Piece noire\n");
        SendTo(station_3, ADDR_STATION_3, PORT_LISTEN_3_2, "PIECE_NOIRE", 11);
    }
    else if(!pieceMetal) {
        printf("--->>> Piece rouge\n");
        SendTo(station_3, ADDR_STATION_3, PORT_LISTEN_3_2, "PIECE_ROUGE", 11);
    }
    
    // Attend que la station 3 soit en reception
    printf("Attend que la station 3 soit prete a recevoir une piece ...\n");
    while(!getCanGivePiece())
        waitTime(500);
    
    // Active le pousseur
    printf("Active le pousseur de piece ...\n");
    setActuateur(PP, ON);
    waitTime(1000);
    setActuateur(PP, OFF);
    
    // Active le coussin
    printf("Active le coussin d'air ...\n");
    setActuateur(COUSSIN_AIR, ON);
    waitTime(2000);
    setActuateur(COUSSIN_AIR, OFF);
    
    // Previens la station 3 qu'on lui donne une piece
    printf("Previens la station 3 qu'on lui donne une piece ...\n");
    SendTo(station_3, ADDR_STATION_3, PORT_LISTEN_3_2, "DONNE_PIECE", 11);
    setCanGivePiece(FALSE);
}