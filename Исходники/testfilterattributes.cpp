bool TestFilterAttributes::testBaseMethodsProfile()
{
    QString testName = "testBaseMethodsProfile";

    AttrFilterProfile *profile1 = createProfile( 1, "name");
    AttrFilterProfile *profile2 = createProfile( 1, "name");
    AttrFilterProfile *profile3 = createProfile( 2, "name");
    AttrFilterProfile *profile4 = createProfile( 1, "name");
    AttrFilterProfile *profile5 = createProfile( 1, "name");
    AttrFilterProfile *profile6 = createProfile( 1, "name");
    AttrFilterProfile *profile7 = createProfile( 1, "name");
    AttrFilterProfile *profile8 = createProfile( 1, "name");

    if( !profile1->compareTo(profile1)) {
        return error(testName, "profile compare to itself" );
    }

    if( profile1->compareTo(NULL)) {
        return error(testName, "profile compare to null" );
    }
    if( profile1->compareToBase(NULL)) {
        return error(testName, "profile compare b to null" );
    }
    //--
    if( !profile1->compareTo(profile2)) {
        return error(testName, "profile compare to equals" );
    }
    if( !profile1->compareToBase(profile2)) {
        return error(testName, "profile compare b to equals" );
    }
    //--
    profile3->setId(100);
    if( profile1->compareTo(profile3)) {
        return error(testName, "profile compare id" );
    }
    if( profile1->compareToBase(profile3)) {
        return error(testName, "profile compare b id" );
    }
    //--
    profile4->setName("x");
    if( profile1->compareTo(profile4)) {
        return error(testName, "profile compare name" );
    }
    if( profile1->compareToBase(profile4)) {
        return error(testName, "profile compare b name" );
    }
    //--
    profile5->setDescription("x");
    if( profile1->compareTo(profile5)) {
        return error(testName, "profile compare description" );
    }
    if( profile1->compareToBase(profile5)) {
        return error(testName, "profile compare b description" );
    }
    //--
    profile1->setWhiteList(true);
    profile6->setWhiteList(false);
    if( profile1->compareTo(profile6)) {
        return error(testName, "profile compare whitelist" );
    }
    if( profile1->compareToBase(profile6)) {
        return error(testName, "profile compare whitelist" );
    }
    //--
    QDateTime dtUpdate;
    dtUpdate.setMSecsSinceEpoch(profile1->updateTime().toMSecsSinceEpoch()+1000);
    profile7->setUpdateTime(dtUpdate);
    if( profile1->compareTo(profile7)) {
        return error(testName, "profile compare update time" );
    }
    //--
    QDateTime dtCreation;
    dtCreation.setMSecsSinceEpoch(profile1->creationTime().toMSecsSinceEpoch()+1000);
    profile8->setCreationTime(dtCreation);
    if( profile1->compareTo(profile8)) {
        return error(testName, "profile compare creation time" );
    }
    //---
    dtUpdate.setMSecsSinceEpoch(profile1->updateTime().toMSecsSinceEpoch()+10000);
    dtCreation.setMSecsSinceEpoch(profile1->creationTime().toMSecsSinceEpoch()+10000);
    profile8->setUpdateTime(dtUpdate);
    profile8->setCreationTime(dtCreation);
    if( profile1->compareTo(profile8)) {
        return error(testName, "profile compare times " );
    }
    if( !profile1->compareToBase(profile8)) {
        return error(testName, "profile compare base time differ" );
    }

    deleteProfile(profile1);
    deleteProfile(profile2);
    deleteProfile(profile3);
    deleteProfile(profile4);
    deleteProfile(profile5);
    deleteProfile(profile6);
    deleteProfile(profile7);
    deleteProfile(profile8);

    return true;
}