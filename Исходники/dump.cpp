void LexStream::Dump()
{
    FILE* tokfile;
    // +1 for '\0' +4 for length(".tok")
    char* tokfile_name = new char[FileNameLength() + 5];
    strcpy(tokfile_name, FileName());
    strcat(tokfile_name, StringConstant::U8S_DO_tok);

    if ((tokfile = SystemFopen(tokfile_name, "w")) == NULL)
    {
        Coutput << "*** Cannot open LexStream dump output file "
                << tokfile_name << endl;
        return;
    }

    RereadInput();
    SetUpComments();

    TokenIndex tok = 0;
    for (CommentIndex com = FirstComment(tok);
         com > 0 && com < NumComments() && PrecedingToken(com) == tok; com++)
    {
        fprintf(tokfile, "*%5d ", com);
        fprintf(tokfile, "%s", FileName());
        fprintf(tokfile, ", line %d.%d: ",
                FindLine(comments[com].location),
                FindColumn(comments[com].location - 1) + 1);
        for (const wchar_t* s = CommentString(com); *s; s++)
            fprintf(tokfile, "%c", *s);
        fprintf(tokfile, "\n");
    }
    do
    {
        tok = Gettoken();
        fprintf(tokfile, "%6d ", tok);
        fprintf(tokfile, " %s", FileName());
        fprintf(tokfile, ", %cline %d.%d: %s %s  ",
                (AfterEol(tok) ? '*' : ' '),
                Line(tok), (Kind(tok) == TK_EOF ? 0 : Column(tok)),
                token_type(Kind(tok)),
                (tokens[tok].Deprecated() ? "(d)" : " "));
        for (const wchar_t* s = NameString(tok); *s; s++)
            fprintf(tokfile, "%c", *s);
        fprintf(tokfile, "\n");

        for (CommentIndex com = FirstComment(tok);
             com > 0 && com < NumComments() && PrecedingToken(com) == tok; com++)
        {
            fprintf(tokfile, "*%5d ", com);
            fprintf(tokfile, " %s", FileName());
            fprintf(tokfile, ", line %d.%d: ",
                    FindLine(comments[com].location),
                    FindColumn(comments[com].location - 1) + 1);
            for (const wchar_t* s = CommentString(com); *s; s++)
                fprintf(tokfile, "%c", *s);
            fprintf(tokfile, "\n");
        }
    } while (Kind(tok) != TK_EOF);

    DestroyInput();
    fprintf(tokfile, "\n");
#ifdef UNIQUE_NAMES
    fprintf(tokfile, "\nThe unique names are:\n\n");
    for (int i = 0; i < control.name_table.symbol_pool.length(); i++)
    {
        fprintf(tokfile, "%4d ", i);
        for (const wchar_t* s = control.name_table.symbol_pool[i].name();
             *s; s++)
        {
            fprintf(tokfile, "%c", *s);
        }
        fprintf(tokfile, "\n");
    }
#endif // UNIQUE_NAMES

    if (tokfile)
        fclose(tokfile);
    delete [] tokfile_name;
}