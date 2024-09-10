/**********************************************************
 Загрузка тела описания статьи из текстового файла Словаря.
 Само тело состоит из нескольких факультативных частей.
***********************************************************/
void Base_Entry::LoadBody(
    Macro_Parser &txtfile,
    Grammar& gram
)
{
    if (is_realized)
    {
        // Если теперь встретится '{', то значит имеем расширенное
        // описание словарной статьи.

        const BSourceState prefig = txtfile.tellp();
        const BethToken isfig = txtfile.read();

#if LEM_DEBUGGING==1
        int nf = CountForms();
#endif

        if (isfig.GetToken() != B_OFIGPAREN)
            txtfile.seekp(prefig);
        else
            LoadTxtEx(txtfile, gram);

        if (CountForms() == 0)
            BeforeFirstForm(gram);

        CheckAttr(txtfile, gram);
    }

#if defined SOL_DETAILED
    if (gram.GetDict().GetDebugLevel_ir() >= 3)
    {
        // Эхо-сообщение: закончили трансляцию статьи.
        gram.GetIO().mecho().printf("Ok\n");
    }
#endif

    return;
}