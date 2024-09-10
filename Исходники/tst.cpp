int main(int argc, char **argv)
{
    void* lStore = StoreManager::getStore();
    Zorba *lZorba = Zorba::getInstance(lStore);

    assert(lZorba);

    example_1(lZorba);

    example_2(lZorba);

    lZorba->shutdown();
    StoreManager::shutdownStore(lStore);
    return 0;
}