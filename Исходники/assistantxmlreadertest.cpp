TEST(AssistantXmlReader, testParsingCDATANotes) {
    const QString XML =
            "<assistants>\n"
            "<assistant name=\"assistant1\">\n"
            "<item name=\"item1\">\n"
            "<notes>Simple notes</notes>\n"
            "<![CDATA[\n"
            "  content\n"
            "    content\n"
            "  content\n"
            "]]>\n"
            "<notes><![CDATA[\n"
            "  notes\n"
            "    notes\n"
            "  notes\n"
            "]]>\n"
            "</notes>\n"
            "more content\n"
            "</item>\n"
            "</assistant>\n"
            "</assistants>\n"
            ;
    const QString FILE_NAME = "assistant.xml";
    writeFile(XML, FILE_NAME);
    AssistantXmlReader reader;
    reader.readFile(FILE_NAME);

    ASSERT_EQ(1, reader.size());
    const Assistant *assistant = reader.assistant(0);
    EXPECT_EQ("assistant1", assistant->name());
    ASSERT_EQ(1, assistant->size());
    const AssistantItem *item = assistant->item(0);
    EXPECT_EQ("item1", item->name());
    EXPECT_EQ("content\n  content\ncontent\nmore content", item->data());
    EXPECT_EQ("Simple notes\nnotes\n  notes\nnotes", item->notes());
}