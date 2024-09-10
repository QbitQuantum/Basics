int main()
{
    _set_se_translator(se_translator);
    try {
        Test();
    }
    catch(...) {
        printf("catched\n");
    }
}