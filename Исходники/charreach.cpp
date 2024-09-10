TEST(ng_charreach, string) {
    CharReach cr;

    cr.set(1);
    cr.set(2);
    cr.set('a');
    cr.set('Z');
    cr.set('m');
    cr.set('~');
    cr.set(210);
    ASSERT_FALSE(cr.isAlpha());
    cr.flip(1);
    cr.flip(2);
    cr.flip('~');
    cr.flip(210);
    ASSERT_TRUE(cr.isAlpha());

    ASSERT_EQ("Zam", cr.to_string());
}