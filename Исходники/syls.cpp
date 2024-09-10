CFSWString the_shift(CFSWString s) {
    /*
            On mingi võimalus, et lihtsustus tuleb teha kahes astmes. LQ-ta ja LQ-ga (vt shift_pattern). Kõik 
            seotud sellega, et pole	vältenihutusreeglitest lõpuni aru saanud. Eksisteerib Mihkla versioon ja 
            ametlik versioon. Tänud	Mihklale, kes kala asemel annab tattninale õnge, see õpetab ujuma.
            Maadlesin õngega pikalt.
     */

    CFSWString res;
    CFSWString code;
    INTPTR pos;
    INTPTR i = 0;
    INTPTR x;

    while (s.GetLength() > 0) {
        CFSWString c = s.GetAt(0);
        s.Delete(0, 1);
        if (is_uvowel(c)) {
            c = c.ToLower();
            code += shift_pattern(c);
            res += c;
            pos = i;
        } else
            if (c == d && code.GetLength() > 0) {
            res += c;
            code += c;
            CFSWString t_code = code;
            t_code += shift_pattern(s.GetAt(0));

            x = pattern_lookup(t_code); //orig üle silbipiiri
            if (x > -1) {
                x += pos;
                if (x > res.GetLength()) { // kui kargab järgmisse silpi
                    x = x - res.GetLength();
                    s.Insert(x, colon);
                } else
                    res.Insert(x, colon);
                i++;
            } else {
                t_code = simplify_pattern(t_code);
                x = pattern_lookup(t_code); //liht üle silbipiiri
                if (x > -1) {
                    x += pos;
                    if (x > res.GetLength()) { // kui kargab järgmisse silpi
                        x = x - res.GetLength();
                        s.Insert(x, colon);
                    } else
                        res.Insert(x, colon);
                    i++;
                } else {
                    x = pattern_lookup(code); //orig 
                    if (x > -1) {
                        x += pos;
                        res.Insert(x, colon);
                        i++;
                    } else {
                        code = simplify_pattern(code);
                        x = pattern_lookup(code); //liht
                        if (x > -1) {
                            x += pos;
                            res.Insert(x, colon);
                            i++;
                        }
                    }
                }
            }

            code = empty_str;
        } else {
            res += c;
            if (code.GetLength() > 0) {
                code += shift_pattern(c);
            }
        }
        i++;
    } //while

    // sõna lõpus
    if (code.GetLength() > 0) {
        code += L"#";
        //imelik koht ainult "lonksu" pärast
        if ((code.Left(3) == L"VLQ") && ((code.GetAt(3) == L's') || (code.GetAt(3) == L'h') || (code.GetAt(3) == L'v') || (code.GetAt(3) == L'j'))) {
            code = L"VLQC#";
        }
        INTPTR x = pattern_lookup(code);
        if (x > -1) {
            x += pos;
            res.Insert(x, colon);
        } else {
            code = simplify_pattern(code);
            x = pattern_lookup(code);
            if (x > -1) {
                x += pos;
                res.Insert(x, colon);
            }
        }
        code = empty_str;
    }
    return res;
}