        void testGenerate_XEP0115ComplexExample() {
            DiscoInfo discoInfo;
            discoInfo.addIdentity(DiscoInfo::Identity("Psi 0.11", "client", "pc", "en"));
            discoInfo.addIdentity(DiscoInfo::Identity("\xce\xa8 0.11", "client", "pc", "el"));
            discoInfo.addFeature("http://jabber.org/protocol/disco#items");
            discoInfo.addFeature("http://jabber.org/protocol/caps");
            discoInfo.addFeature("http://jabber.org/protocol/disco#info");
            discoInfo.addFeature("http://jabber.org/protocol/muc");

            Form::ref extension(new Form(Form::ResultType));
            FormField::ref field = std::make_shared<FormField>(FormField::HiddenType, "urn:xmpp:dataforms:softwareinfo");
            field->setName("FORM_TYPE");
            extension->addField(field);
            field = std::make_shared<FormField>(FormField::ListMultiType);
            field->addValue("ipv6");
            field->addValue("ipv4");
            field->setName("ip_version");
            extension->addField(field);
            field = std::make_shared<FormField>(FormField::TextSingleType, "Psi");
            field->setName("software");
            extension->addField(field);
            field = std::make_shared<FormField>(FormField::TextSingleType, "0.11");
            field->setName("software_version");
            extension->addField(field);
            field = std::make_shared<FormField>(FormField::TextSingleType, "Mac");
            field->setName("os");
            extension->addField(field);
            field = std::make_shared<FormField>(FormField::TextSingleType, "10.5.1");
            field->setName("os_version");
            extension->addField(field);
            discoInfo.addExtension(extension);

            CapsInfoGenerator testling("http://psi-im.org", crypto.get());
            CapsInfo result = testling.generateCapsInfo(discoInfo);

            CPPUNIT_ASSERT_EQUAL(std::string("q07IKJEyjvHSyhy//CH0CxmKi8w="), result.getVersion());
        }