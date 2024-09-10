// --------- INICIALIZACION DEL JUEGO
//
bool TProfanationGame::init(void)
{ 
    lb_init=false; 
     
    if (!TMAGame::init()) return false;
    inputController.setNumControls(GKEY_MAX);
    loadConfiguration();
    
    if (!setGraphicsMode(640/_REDUCE,480/_REDUCE,16,config_fullscreen)) return false;
    
    setWindowTitle("Abusimbel Profanation Deluxe");
    setGameFPS(32);
    
    lb_init = true;
                
    // Cargamos los tipos de letras constantes en el juego
    //
    #ifdef SMALL_GAME
        fontMulti.load("Data/Fonts/FuenteMulti.png",10,15,gs_charset.length(),1,false,0);
        fontBlue.load("Data/Fonts/FuenteBlue.png",10,15,gs_charset.length(),1,false,0);
    #else
        fontMulti.load("Data/Fonts/FuenteMulti.png",20,30,gs_charset.length(),1,false,MAKERGBCOLOR(255,0,255));
        fontBlue.load("Data/Fonts/FuenteBlue.png",20,30,gs_charset.length(),1,false,MAKERGBCOLOR(255,0,255));
    #endif
    fontMulti.setCharacters(*gs_charset);
    fontBlue.setCharacters(*gs_charset);
    
    // Cargamos los sonidos
    //
    if (isSoundAvailable())
    {
        setVolume(gi_volume);
        gsnd_Gota.load("Data/Sonidos/gota.wav");
        gsnd_Roca.load("Data/Sonidos/roca.wav");
        gsnd_Camina.load("Data/Sonidos/camina.wav");
        gsnd_Salto.load("Data/Sonidos/salto.wav");
        gsnd_Caida.load("Data/Sonidos/caida.wav");
        gsnd_Tesoro.load("Data/Sonidos/tesoro.wav");
        gsnd_Scroll.load("Data/Sonidos/scroll.wav");
        gsnd_Teletransporte.load("Data/Sonidos/teletransporte.wav");
        gsnd_Grito.load("Data/Sonidos/grito.wav");
    }
    
    miRND.init();
    
    // Establecemos el escenario inicial
    //    
    setScene(new TESC_Seleccion_Idioma());
    
    return true;
}