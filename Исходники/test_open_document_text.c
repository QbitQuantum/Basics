void
test_1_2_ja(void)
{
    cut_assert_equal_string("Sample of OpenDocument Text 1.2\n"
                            "OpenDocument Text 1.2 の日本語サンプル\n",
                            decompose("1.2_ja.odt"));
}