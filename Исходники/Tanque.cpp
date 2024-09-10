void Tanque::MovaCima(BITMAP *db)
	{
   // iden ...
   int r =  getr(getpixel(db, col-velocidade, lin));
   int g =  getg(getpixel(db, col-velocidade, lin));
   int b =  getb(getpixel(db, col-velocidade, lin));

   lin-=velocidade;
   //evia que o tanque saia  da tela por cima
   if ( lin <= 50 )
      lin = 50;
}