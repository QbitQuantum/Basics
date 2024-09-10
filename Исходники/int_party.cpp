// パーティデータのロード
int inter_party_init(void)
{
    std::ifstream in(party_txt.c_str());
    if (!in.is_open())
        return 1;

    // TODO: convert to use char_id, and change to extract()
    FString line;
    int c = 0;
    while (io::getline(in, line))
    {
        int i, j = 0;
        if (SSCANF(line, "%d\t%%newid%%\n%n", &i, &j) == 1 && j > 0
            && party_newid <= i)
        {
            party_newid = i;
            continue;
        }

        struct party p {};
        if (extract(line, &p) && p.party_id > 0)
        {
            if (p.party_id >= party_newid)
                party_newid = p.party_id + 1;
            party_db.insert(p.party_id, p);
            party_check_empty(&p);
        }
        else
        {
            PRINTF("int_party: broken data [%s] line %d\n", party_txt,
                    c + 1);
        }
        c++;
    }
//  PRINTF("int_party: %s read done (%d parties)\n", party_txt, c);

    return 0;
}