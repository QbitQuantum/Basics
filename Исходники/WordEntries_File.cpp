void WordEntries_File::DetailedReport(OFormatter &txtfile)
{
    txtfile.printf("\n%80h-\nLexical LookUp Table:\n");
    /*
     for( std::map< SG_EntryGroup::KEY, SG_EntryGroup* >::const_iterator it=group.begin(); it!=group.end(); ++it )
      {
       it->second->Print(txtfile);
       txtfile.eol();
      }
    */

    txtfile.printf("\n\n%10h- MULTILEXEM DICTIONARY %10h-\n\n");

    txtfile.printf(
        "Multilexem dictionary contains %d unique items\n"
        , ml_ref.get_list().size()
    );

    int n_real = 0; // счетчик реально многолексемных
    int max_len = 0;
    for (lem::Container::size_type i = 0; i < ml_ref.get_list().size(); i++)
    {
        if (ml_ref.get_list()[i].Count_Lexems() > 1)
            n_real++;

        max_len = std::max(max_len, ml_ref.get_list()[i].length());
    }


    txtfile.printf("%d of them have more than 1 lexem:\n", n_real);

    txtfile.printf("Max length of a lexem=%d\n", max_len);

    for (lem::Container::size_type i4 = 0; i4 < ml_ref.get_list().size(); i4++)
        if (ml_ref.get_list()[i4].Count_Lexems() > 1)
            txtfile.printf("%us\n", ml_ref.get_list()[i4].c_str());

    txtfile.printf("%10h- END OF MULTILEXEM DICTIONARY %10h-\n");

    return;
}