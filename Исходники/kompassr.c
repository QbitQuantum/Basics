/* подпр.обр.пс.опер.START */
int SSTART()
{
    /* набор рабочих переменных подпрограммы */
    char *PTR;
    char *METKA;
    char *METKA1;
    int J;
    int RAB;

    /* в перем. c указат.METKA1 выбираем первую лексему операнда текущей карты исх.текста АССЕМБЛЕРА */
    METKA1 = strtok((char*) TEK_ISX_KARTA.STRUCT_BUFCARD.METKA, " ");

    for ( J=0; J<=ITSYM; J++ )
    {
        /* все метки исх.текста в табл. T_SYM сравниваем со знач.перем. *METKA1 */
        METKA = strtok ((char*) T_SYM[J].IMSYM , " ");

        /* и при совпадении:      */
        if( !strcmp ( METKA , METKA1 ) )
        {
            /*  берем разность сч.адр. знач.этой метки, образуя длину программы в соглашениях ЕС ЭБМ, и записыв.ее в ESD-карту побайтно */
            RAB = CHADR - T_SYM[J].ZNSYM;
            PTR = (char *)&RAB;
            swab ( PTR , PTR , 2 );
            ESD.STR_ESD.DLPRG [0] = 0;
            ESD.STR_ESD.DLPRG [1] = *PTR;
            ESD.STR_ESD.DLPRG [2] = *(PTR + 1);

            /* устанавл.CHADR, равным операнду операт.START исходного текста */
            CHADR = T_SYM[J].ZNSYM;

            /* формирование поля ADPRG ESD-карты в формате двоичного целого в соглашениях ЕС ЭВМ */
            PTR = (char *)&CHADR;
            ESD.STR_ESD.ADPRG[2]  = *PTR;
            ESD.STR_ESD.ADPRG[1]  = *(PTR+1);
            ESD.STR_ESD.ADPRG[0]  = '\x00';

            /* формирование имени программы и идентификационнго поля ESD - карты */
            memcpy(ESD.STR_ESD.IMPR, METKA, strlen(METKA));
            memcpy(ESD.STR_ESD.POLE11, METKA, strlen(METKA));

            /* запись об'ектной карты в массив об'ектных карт */
            memcpy(OBJTEXT[ITCARD], ESD.BUF_ESD, 80);
            ITCARD += 1;                                /*коррекц.инд-са своб.к-ты*/
            return (0);                                 /*успешное заверш.подпрогр*/
        }
    }
    return (2);                                     /*ошибочное заверш.прогр. */
}