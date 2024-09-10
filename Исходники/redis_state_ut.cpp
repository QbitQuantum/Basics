TEST(ConsumerStateTable, double_set)
{
    clearDB();

    /* Prepare producer */
    int index = 0;
    string tableName = "UT_REDIS_THREAD_" + to_string(index);
    DBConnector db(TEST_VIEW, "localhost", 6379, 0);
    ProducerStateTable p(&db, tableName);
    string key = "TheKey";
    int maxNumOfFields = 2;

    /* First set operation */
    {
        vector<FieldValueTuple> fields;
        for (int j = 0; j < maxNumOfFields; j++)
        {
            FieldValueTuple t(field(j), value(j));
            fields.push_back(t);
        }
        p.set(key, fields);
    }

    /* Second set operation */
    {
        vector<FieldValueTuple> fields;
        for (int j = 0; j < maxNumOfFields * 2; j += 2)
        {
            FieldValueTuple t(field(j), value(j));
            fields.push_back(t);
        }
        p.set(key, fields);
    }

    /* Prepare consumer */
    ConsumerStateTable c(&db, tableName);
    Select cs;
    Selectable *selectcs;
    cs.addSelectable(&c);
    int tmpfd;

    /* First pop operation */
    {
        int ret = cs.select(&selectcs, &tmpfd);
        EXPECT_TRUE(ret == Select::OBJECT);
        KeyOpFieldsValuesTuple kco;
        c.pop(kco);
        EXPECT_TRUE(kfvKey(kco) == key);
        EXPECT_TRUE(kfvOp(kco) == "SET");

        auto fvs = kfvFieldsValues(kco);
        EXPECT_EQ(fvs.size(), (unsigned int)(maxNumOfFields + maxNumOfFields/2));

        map<string, string> mm;
        for (auto fv: fvs)
        {
            mm[fvField(fv)] = fvValue(fv);
        }

        for (int j = 0; j < maxNumOfFields; j++)
        {
            EXPECT_EQ(mm[field(j)], value(j));
        }
        for (int j = 0; j < maxNumOfFields * 2; j += 2)
        {
            EXPECT_EQ(mm[field(j)], value(j));
        }
    }

    /* Second select operation */
    {
        int ret = cs.select(&selectcs, &tmpfd, 1000);
        EXPECT_TRUE(ret == Select::TIMEOUT);
    }
}