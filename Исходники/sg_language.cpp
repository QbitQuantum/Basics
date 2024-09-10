void SG_Language::LoadTxt(int Id, Macro_Parser& txt, GraphGram& gram)
{
    // Store the beginning of language specification
    BSourceState beg = txt.tellp();

    id = Id;

    name = txt.read().string();

    const bool Me = gram.GetDict().GetDebugLevel_ir() >= 3;
    if (Me)
    {
        // Эхо-сообщение: начали трансляцию языка.
        gram.GetIO().mecho().printf(
            "%us [%vfE%us%vn]->",
            sol_get_token(B_LANGUAGE).c_str(),
            name.c_str()
        );
    }


    BethToken t = txt.read();
    if (t.GetToken() == B_AS)
    {
        c_name = txt.read().string();
        t = txt.read();
    }

    if (t.GetToken() != B_OFIGPAREN)
    {
        // Пустое объявление языка.
        txt.seekp(t.GetBegin());
    }
    else
    {
        // Load the list of alphabets, allowed for the language. Also do load other
        // language parameters.
        while (!txt.eof())
        {
            BethToken t = txt.read();

            if (t.GetToken() == B_CFIGPAREN)
                break;

            if (t.GetToken() == B_ALPHABET)
            {
                // Add the valid alphabet name for this language

                BethToken abc_name = txt.read();
                int id_abc = gram.Find_Alphabet(abc_name.string());

                if (id_abc == UNKNOWN)
                {
                    lem::Iridium::Print_Error(abc_name, txt);
                    gram.GetIO().merr().printf("Unknown alphabet [%us] used in in language [%us] specification\n", abc_name.string().c_str(), name.c_str());
                    throw E_ParserError();
                }

                alphabet.push_back(id_abc);
                continue;
            }
            else if (t.GetToken() == B_LINK)
            {
                Tree_Link l;
                l.LoadTxt(txt, gram.GetDict().GetSynGram());

                txt.read_it(B_LANGUAGE);
                BethToken lang_name = txt.read();

                int id_lang = gram.GetDict().GetSynGram().Find_Language(lang_name);
                if (id_lang == UNKNOWN)
                {
                    lem::Iridium::Print_Error(lang_name, txt);
                    gram.GetIO().merr().printf("Unknown language [%us] used in in language [%us] specification\n", lang_name.string().c_str(), name.c_str());
                    throw E_ParserError();
                }

                lang_links.push_back(std::make_pair(l, id_lang));
                continue;
            }
            else
            {
                // Синтаксис задания параметра: 
                // 1. скалярный param_name = value
                // 2. векторный param_name = { value1 values2 ... }

                if (txt.pick().GetToken() == B_EQUAL)
                {
                    txt.read_it(B_EQUAL);
                    SG_LanguageParam *param = new SG_LanguageParam;
                    param->name = t;

                    if (txt.pick().GetToken() == B_OFIGPAREN)
                    {
                        txt.read_it(B_OFIGPAREN);

                        while (!txt.eof())
                        {
                            if (txt.pick().GetToken() == B_CFIGPAREN)
                            {
                                txt.read_it(B_CFIGPAREN);
                                break;
                            }

                            UFString v = txt.read().GetFullStr();
                            v.strip(L'"');
                            v.trim();
                            param->values.push_back(v);
                        }
                    }
                    else
                    {
                        param->values.push_back(lem::trim(lem::UFString(txt.read().GetFullStr())));
                    }

                    params.push_back(param);

                    continue;
                }
            }

            lem::Iridium::Print_Error(t, txt);
            gram.GetIO().merr().printf("Invalid token in language [%us] specification\n", name.c_str());
            throw E_ParserError();
        }
    }

    if (Me)
    {
        // Эхо-сообщение: закончили трансляцию.
        gram.GetIO().mecho().printf("%vfAOK%vn\n");
    }

    return;
}