int main(int argc, char *argv[])
{

    char **playersNameList;
    int totalPlayersNumber;
    int turn, i;
    char buffer[BUFF_SIZE];
    FILE *configFile;

    /* legge gli argomenti */
    char **name1, **name2;

    if (argc < 4) {
        fprintf(stderr,
                "ERROR: Wrong number of arguments. \n USAGE: %s\n",
                USAGE);
        exit(EXIT_FAILURE);
    }
    playersNameList = argv + 3;
    totalPlayersNumber = argc - 3;

    /* controlla se ci sono due giocatori con lo stesso nome */
    for (name1 = playersNameList; *name1; name1++)
        for (name2 = name1 + 1; *name2; name2++)
            if (strcmp(*name1, *name2) == 0) {
                fprintf(stderr, "ERROR: found two player with the"
                        "same name \"%s\"\n", *name1);
                exit(EXIT_FAILURE);
            }
    initIoInterface(argv[2]);
    /* crea e inizializza le strutture dati per i giocatori */
    initPlayersManager(totalPlayersNumber);
    for (; *playersNameList; playersNameList++)
        addPlayer(*playersNameList);

    initBoard();
    /*
     * legge il file di configurazione secondo il formato: 
     *     numero_casella:descrizione della prova\n
     * e aggiunge le descrizioni al tabellone
     */
    if ((configFile = fopen(argv[1], "r")) == NULL) {
        printErr("ERROR: error while opening configuration file\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(buffer, BUFF_SIZE, configFile)) {
        char *description;
        int boxNumber;
        /* legge il numero di casella */
        if ((boxNumber = atoi(buffer)) <= 0) {
            printErr("ERROR:invalid box num(\"%s\") in"
                     " configuration file\n", buffer);
            exit(EXIT_FAILURE);
        }
        /* aggiunge una nuova casella con la relativa descrizione */
        if ((description = strchr(buffer, ':')) == NULL) {
            printErr("ERROR: missing ':' in configuration file\n");
            exit(EXIT_FAILURE);
        }
        addBox(boxNumber, description + 1);
    }
    if (getTotalBoxesNumber() == 0) {
        printErr("ERROR: invalid configuration file\n");
        exit(EXIT_FAILURE);
    }
    fclose(configFile);
    printBoard();
    showGame();
    /* avvia la simulazione del gioco */
    srand(time(NULL));
    for (turn = 0; !allPlayersDone(); turn++) {
        if (!nextStep())
            return EXIT_SUCCESS;
        printMessage("\n**************************************\n");
        printMessage("turno %d", turn + 1);
        printMessage("\n**************************************\n");
        showGame();
        /*
         * per ogni giocatore G che non ha terminato il gioco: 
         * 1. se G  e' fermo per un turno cambia il suo stato in
         *      modo che al turno successivo venga rimesso in gioco 
         * 2. altrimenti viene lanciato il dado, mosso il giocatore
         *              e visualizzata la sua prova 
         */
        while (nextPlayer()) {
            int state = getPlayerState();

            if (state == ACTIVE || state == TEST_PASSED
                || state == TO_BE_ACTIVATED) {
                if (state != ACTIVE)
                    setPlayerState(ACTIVE, 0);
                movePlayer((rand() % 6) + 1);
                if (getPlayerBox() > getTotalBoxesNumber())
                    setPlayerState(DONE, turn);
                else
                    printMessage("player %s: \"%s\"\n",
                                 getPlayerName(),
                                 getDescription(getPlayerBox()));
            } else if (state == OUT_OF_TURN)
                setPlayerState(TO_BE_ACTIVATED, 0);
        }
        showGame();
        /*
         * Legge e registra l'esito di tutte le prove sostenute nel
         * turno corrente dai giocatori 
         */
        for (i = getActivePlayersNumber(); i > 0; i--) {
            int playerNumber;
            bool result;

            do {
                result = askPlayerResult(&playerNumber);
                if (playerNumber > totalPlayersNumber)
                    printErr("WARNING: player number %d out of "
                             "bounds [1; %d]\n", playerNumber,
                             totalPlayersNumber);
                else {
                    setCurrentPlayer(playerNumber);
                    if (getPlayerState() != ACTIVE)
                        printErr("WARNING: player number %d not "
                                 "valid because player:"
                                 "\n\t-won"
                                 "\n\t-is out of turn"
                                 "\n\t-already passed the test\n",
                                 playerNumber);
                }
            }
            while (playerNumber > totalPlayersNumber
                   || getPlayerState() != ACTIVE);
            if (result)
                setPlayerState(TEST_PASSED, 0);
            else
                setPlayerState(OUT_OF_TURN, 0);
        }
    }
    printScore();
    closeIoInterface();

    return EXIT_SUCCESS;
}