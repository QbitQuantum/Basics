int main(AVAHI_GCC_UNUSED int argc, AVAHI_GCC_UNUSED char*argv[]) {

    DNSServiceRef ref1, ref2, ref3, ref4 = NULL;

    DNSServiceRegister(&ref1, 0, 0, "simple", "_simple._tcp", NULL, NULL, 4711, 0, NULL, NULL, NULL);
    DNSServiceRegister(&ref2, 0, 0, "subtype #1", "_simple._tcp,_subtype1", NULL, NULL, 4711, 0, NULL, NULL, NULL);
    DNSServiceRegister(&ref3, 0, 0, "subtype #2", "_simple._tcp,_subtype1,_subtype2", NULL, NULL, 4711, 0, NULL, NULL, NULL);

    DNSServiceRegister(&ref4, 0, 0, "subtype #3", "_simple._tcp,,", NULL, NULL, 4711, 0, NULL, NULL, NULL);
    assert(!ref4);
    DNSServiceRegister(&ref4, 0, 0, "subtype #3", "", NULL, NULL, 4711, 0, NULL, NULL, NULL);
    assert(!ref4);
    DNSServiceRegister(&ref4, 0, 0, "subtype #3", ",", NULL, NULL, 4711, 0, NULL, NULL, NULL);
    assert(!ref4);
    DNSServiceRegister(&ref4, 0, 0, "subtype #3", ",,", NULL, NULL, 4711, 0, NULL, NULL, NULL);
    assert(!ref4);

    DNSServiceBrowse(&ref4, 0, 0, "_simple._tcp,_gurke", NULL, reply, NULL);

    sleep(20);

    DNSServiceRefDeallocate(ref1);
    DNSServiceRefDeallocate(ref2);
    DNSServiceRefDeallocate(ref3);
    DNSServiceRefDeallocate(ref4);

    return 0;
}