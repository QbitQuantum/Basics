CFSArray<CFSWString> do_all(CFSWString utt, bool print_label, bool print_utt) {
    CFSArray<CFSWString> res;
    CFSArray<CPTWord> PTW;
    utterance_struct u;
    

    u.s = utt.ToLower();
    u.syl_c = 0;
    u.phone_c = 0;
    u.phra_c = do_phrases(u);
    INTPTR word_count = 0;
    
    if (print_utt) fprintf(stderr, "%s\n", ccstr(utt));
       
    for (INTPTR i = 0; i < u.phr_vector.GetSize(); i++) {
        u.phr_vector[i].utt_p = i;        
        phrase2words(u.phr_vector[i], PTW);
        word_count += u.phr_vector[i].word_c;        
        
    }
    

    CFSArray<CMorphInfo> words;
    for (INTPTR i = 0; i < PTW.GetSize(); i++) {
        CMorphInfo MI;
        MI.m_szRoot = PTW[i].m_szWord;
        words.AddItem(MI);
    }
        
    
    u.word_c = words.GetSize();


    word_struct w;

    INTPTR utt_phone_c = 1;
    INTPTR syl_utt_p = 1;
    INTPTR phone_utt_p = 1;



    for (INTPTR i = 0; i < u.phr_vector.GetSize(); i++) {
        u.phr_vector[i].utt_p = i + 1;
        INTPTR syl_phr_p = 1;
        INTPTR phone_phr_p = 1;
        INTPTR phrase_pho_c = 1;
        for (INTPTR i1 = 0; i1 < u.phr_vector[i].word_c; i1++) {
            
            w.utt_p = utt_phone_c++;
            w.phr_p = i1 + 1;
            w.mi = words[0];
            w.mi.m_szRoot += make_char_string(w.mi.m_szEnding) + w.mi.m_szClitic;
            w.mi.m_szRoot = w.mi.m_szRoot.ToLower();
            do_syls(w);
            u.phr_vector[i].word_vector.AddItem(w);

            INTPTR phone_word_p = 1;
            INTPTR word_pho_c = 1;
            for (INTPTR i2 = 0; i2 < u.phr_vector[i].word_vector[i1].syl_vector.GetSize(); i2++) {
                u.syl_c++;
                u.phr_vector[i].syl_c++;
                u.phr_vector[i].word_vector[i1].syl_c++;
                u.phr_vector[i].word_vector[i1].syl_vector[i2].phr_p = syl_phr_p++;
                u.phr_vector[i].word_vector[i1].syl_vector[i2].utt_p = syl_utt_p++;
                INTPTR syl_phone_c = 1;

                do_phones(u.phr_vector[i].word_vector[i1].syl_vector[i2]);

                for (INTPTR i3 = 0; i3 < u.phr_vector[i].word_vector[i1].syl_vector[i2].phone_vector.GetSize(); i3++) {
                    u.phone_c++;
                    u.phr_vector[i].phone_c = phrase_pho_c++;
                    u.phr_vector[i].word_vector[i1].phone_c = word_pho_c++;
                    u.phr_vector[i].word_vector[i1].syl_vector[i2].phone_c = syl_phone_c++;
                    phone_struct p = u.phr_vector[i].word_vector[i1].syl_vector[i2].phone_vector[i3];
                    p.utt_p = phone_utt_p++;
                    p.phr_p = phone_phr_p++;
                    p.word_p = phone_word_p++;
                    u.phr_vector[i].word_vector[i1].syl_vector[i2].phone_vector[i3] = p;

                }

            }
            words.RemoveItem(0, 1);
        }
    }




    if (print_label) print_u(u);
    res = do_label(u);
    return res;
}