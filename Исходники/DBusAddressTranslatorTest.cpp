TEST_F(AddressTranslatorTest, ParsesCommonAPIAddresses) {
    std::shared_ptr<CommonAPI::DBus::DBusAddressTranslator> translator = CommonAPI::DBus::DBusAddressTranslator::get();

    for(unsigned int i = 0; i < commonApiAddresses.size(); i++) {
        CommonAPI::Address commonApiAddress;
        translator->translate(CommonAPI::DBus::DBusAddress(dbusAddresses[i].getService(), dbusAddresses[i].getObjectPath(), dbusAddresses[i].getInterface()), commonApiAddress);
        std::cout << dbusAddresses[i].getService() << " " << dbusAddresses[i].getObjectPath() << " " << dbusAddresses[i].getInterface() << std::endl;
        std::cout << commonApiAddress.getDomain() << " " << commonApiAddress.getInterface() << " " << commonApiAddress.getInstance() << std::endl;
        ASSERT_EQ(commonApiAddresses[i], commonApiAddress.getAddress());
    }
}