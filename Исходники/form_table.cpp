void Form_Table::LoadBody(Macro_Parser &txtfile, Grammar& gram)
{
    txtfile.read_it(B_OFIGPAREN);

    // *** Считываем описание Таблицы ***
    BethToken token;
    CP_Array common;

    FOREVER
    {
     if (txtfile.eof())
      {
       Print_Error(txtfile);
       gram.GetIO().merr().printf("End of file has been reached before entry body completely loaded\n");
       throw E_ParserError();
      }

     const BSourceState back = txtfile.tellp();
     token = txtfile.read();

     if (token.GetToken() == B_CFIGPAREN)
      {
         // Описание Таблицы закончено.
         break;
        }

       if (ProcessSection(txtfile,gram,token))
        continue;

       txtfile.seekp(back);

       if (LoadAttribute(txtfile,gram))
        continue;

       LoadForm(
                txtfile,
                gram,
                common,
                GramCoordAdr(UNKNOWN,UNKNOWN),
                UNKNOWN,
                GramCoordAdr(UNKNOWN,UNKNOWN),
                UNKNOWN,
                UNKNOWN
                ); // Загружаем словоформу.

    } // конец цикла считывания описания статьи

    return;
}