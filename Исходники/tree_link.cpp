/*************************************************************************

 Загрузка дескриптора ребра из текстового файла. Распознаются форматы:

 1. <имя_коорд:имя_связки>

   Расширенный формат, явно задано имя координаты имя_коорд, одно из
   состояний которой имя_связки признается за имя связки. Угловые скобки
   обязательны. Частные случаи этого формата:

 1.1 <имя_коорд:*>

   То есть имя связки (состояния координаты имя_коорд) задается квантором
   производьности, и в дальнейших проверках игнорируется.

 1.2 <имя_коорд:?>

   Имя связки задано как квантор UNKNOWN.

 2. <имя_связки>

   Сокращенный формат, имя связки должно быть объявлено как имя
   состояния координаты с предопределенным именем net.

 3. <*>

   Связка задана как квантор всеобщности, так что в операциях сравнения
   она будет подходить для любой другой связки.

 4. <?>

   Особое задание связки - через квантор UNKNOWN.

***************************************************************************/
bool Tree_Link::LoadTxt(Macro_Parser &txtfile, const SynGram &gram)
{
    const BSourceState back = txtfile.tellp();
    BethToken coord_name = txtfile.read();
    if (coord_name.GetToken() == B_OTRIPAREN)
    {
        coord_name = txtfile.read();

        switch (coord_name.GetToken())
        {
        case ANY_STATE:     icoord = ANY_STATE;     break;
        case UNKNOWN_STATE: icoord = UNKNOWN_STATE; break;

        default:
        {
            const BethToken t = txtfile.read();

            if (t.GetToken() == B_COLON)
            {
                // Полный, расширенный формат с указанием имени координаты.
                if ((icoord = gram.FindCoord(coord_name.string()).GetIndex()) == UNKNOWN)
                {
                    lem::Iridium::Print_Error(coord_name, txtfile);

                    gram.GetIO().merr().printf(
                        "The coordinate [%us] is not previously declared in grammar\n"
                        , coord_name.c_str()
                    );
                    throw E_ParserError();
                }
            }
            else
            {
                icoord = I_NET;
                txtfile.seekp(coord_name);
            }

            const BethToken state_name = txtfile.read();
            switch (state_name.GetToken())
            {
            case B_ANY:     istate = ANY_STATE;     break;
            case B_UNKNOWN: istate = UNKNOWN_STATE; break;
            default:
                if ((istate = gram.coords()[icoord].FindState(state_name.string())) == UNKNOWN)
                {
                    lem::Iridium::Print_Error(state_name, txtfile);
                    gram.GetIO().merr().printf(
                        "State [%us] is not declared for coordinate [%us]\n"
                        , state_name.c_str(), gram.coords()[icoord].GetName().string().c_str()
                    );

                    throw E_ParserError();
                }
                break;
            }

            break;
        }
        }

        txtfile.read_it(B_CTRIPAREN);
        return true;
    }
    else
    {
        txtfile.seekp(back);
        icoord = UNKNOWN;
        istate = UNKNOWN;
        return false;
    }

    return false;
}