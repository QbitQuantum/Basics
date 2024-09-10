static void test_TextField_ime_off()
{
    TextField* t = createTextField();
    keyPress(t, 'a');
    EXPECT_STR_EQ("a", t->getText());

    keyPress(t, 'i');
    EXPECT_EQ_TEXT_FIELD("ai", 2, t);

    keyPress(t, KeyEvent::VKEY_BACKSPACE);
    EXPECT_EQ_TEXT_FIELD("a", 1, t);

    keyPress(t, KeyEvent::VKEY_LEFT);
    EXPECT_EQ_TEXT_FIELD("a", 0, t);

    keyPress(t, 'c');
    EXPECT_EQ_TEXT_FIELD("ca", 1, t);

    keyPress(t, KeyEvent::VKEY_RIGHT);
    EXPECT_EQ(2, t->getCursor());
    keyPress(t, 'b');
    EXPECT_EQ_TEXT_FIELD("cab", 3, t);
    destroyTextField(t);
}