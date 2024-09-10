int main(int argc, char **argv)
{
    YAZ_CHECK_INIT(argc, argv);
    YAZ_CHECK_LOG();

#if YAZ_HAVE_ICU

    check_icu_casemap();
    check_icu_sortmap();
    check_icu_normalizer();
    check_icu_tokenizer();
    check_icu_chain();
    check_chain_empty_token();
    check_chain_empty_chain();
    check_icu_iter1();
    check_icu_iter2();
    check_icu_iter3();
    check_icu_iter4();

    check_bug_1140();
    check_norm();

    u_cleanup();
#else /* YAZ_HAVE_ICU */

    yaz_log(YLOG_LOG, "ICU unit tests omitted");
    YAZ_CHECK(0 == 0);

#endif /* YAZ_HAVE_ICU */

    YAZ_CHECK_TERM;
}