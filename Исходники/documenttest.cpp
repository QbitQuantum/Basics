TEST(Document, ParseStream_EncodedInputStream) {
    // UTF8 -> UTF16
    FILE* fp = OpenEncodedFile("utf8.json");
    char buffer[256];
    FileReadStream bis(fp, buffer, sizeof(buffer));
    EncodedInputStream<UTF8<>, FileReadStream> eis(bis);

    GenericDocument<UTF16<> > d;
    d.ParseStream<0, UTF8<> >(eis);
    EXPECT_FALSE(d.HasParseError());

    fclose(fp);

    wchar_t expected[] = L"I can eat glass and it doesn't hurt me.";
    GenericValue<UTF16<> >& v = d[L"en"];
    EXPECT_TRUE(v.IsString());
    EXPECT_EQ(sizeof(expected) / sizeof(wchar_t) - 1, v.GetStringLength());
    EXPECT_EQ(0, StrCmp(expected, v.GetString()));

    // UTF16 -> UTF8 in memory
    StringBuffer bos;
    typedef EncodedOutputStream<UTF8<>, StringBuffer> OutputStream;
    OutputStream eos(bos, false);   // Not writing BOM
    {
        Writer<OutputStream, UTF16<>, UTF8<> > writer(eos);
        d.Accept(writer);
    }

    // Condense the original file and compare.
    fp = OpenEncodedFile("utf8.json");
    FileReadStream is(fp, buffer, sizeof(buffer));
    Reader reader;
    StringBuffer bos2;
    Writer<StringBuffer> writer2(bos2);
    reader.Parse(is, writer2);
    fclose(fp);

    EXPECT_EQ(bos.GetSize(), bos2.GetSize());
    EXPECT_EQ(0, memcmp(bos.GetString(), bos2.GetString(), bos2.GetSize()));
}