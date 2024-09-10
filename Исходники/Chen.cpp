//陰陽「太極図」
int CBossChenMiddle::Taikyoku()
{
    flag = 1;
    deffence = 1;
    SetHP(2000);
    SetTime(40);
    Suspend(60);

    for( int i = 0; i < 60; ++i ) {
        x += ( 450 - GetX() ) / 60;
        y += ( GAME_CENTER_Y - GetY() ) / 60;
        mt.Suspend(1);
    }

    CTamaTaikyoku tama;
    tama.x = GetX();
    tama.y = GetY();
    tama.type = 12;
    tama.v = 3;
    int offset = 0.0;
    while(1) {
        for( int i = 0;; i++) {
            //攻撃
            tama.color = 1;
            tama.a = offset;
            g_lTama.Add( tama.Copy() );
            tama.color = 0;
            tama.a = offset + 180;
            g_lTama.Add( tama.Copy() );

            g_pMaterial->sndFire.Play(0);
            double m;
            if( GetDifficult() == DIFF_LUNATIC )
                m = 1.5*(4-GetDifficult());
            else
                m = 2.0*(4-GetDifficult());

            if( i > 120/m )
                offset += 3.0*m*Sin((double)i*2);
            this->Suspend(m);
        }
    }
    return 1;
}