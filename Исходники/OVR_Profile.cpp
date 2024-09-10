void ProfileManager::LoadV1Profiles(JSON* v1)
{
    JSON* item0 = v1->GetFirstItem();
    JSON* item1 = v1->GetNextItem(item0);
    JSON* item2 = v1->GetNextItem(item1);

    // Create the new profile database
    Ptr<JSON> root = *JSON::CreateObject();
    root->AddNumberItem("Oculus Profile Version", 2.0);
    root->AddItem("Users", JSON::CreateArray());
    root->AddItem("TaggedData", JSON::CreateArray());
    ProfileCache = root;

    const char* default_dk1_user = item1->Value;
    
    // Read the number of profiles
    int   profileCount = (int)item2->dValue;
    JSON* profileItem  = item2;

    for (int p=0; p<profileCount; p++)
    {
        profileItem = root->GetNextItem(profileItem);
        if (profileItem == NULL)
            break;

        if (profileItem->Name == "Profile")
        {
            // Read the required Name field
            const char* profileName;
            JSON* item = profileItem->GetFirstItem();
        
            if (item && (item->Name == "Name"))
            {   
                profileName = item->Value;
            }
            else
            {
                return;   // invalid field
            }
            
            // Read the user profile fields
            if (CreateUser(profileName, profileName))
            {
                const char* tag_names[2] = {"User", "Product"};
                const char* tags[2];
                tags[0] = profileName;

                Ptr<Profile> user_profile = *CreateProfile();
                user_profile->SetValue(OVR_KEY_NAME, profileName);

                float neckeye[2] = { 0, 0 };

                item = profileItem->GetNextItem(item);
                while (item)
                {
                    if (item->Type != JSON_Object)
                    {
                        if (item->Name == OVR_KEY_PLAYER_HEIGHT)
                        {   // Add an explicit eye height

                        }
                        if (item->Name == "NeckEyeHori")
                            neckeye[0] = (float)item->dValue;
                        else if (item->Name == "NeckEyeVert")
                            neckeye[1] = (float)item->dValue;
                        else 
                            user_profile->SetValue(item);
                    }
                    else
                    {   
                        // Add the user/device tag values
                        const char* device_name = item->Name.ToCStr();
                        Ptr<Profile> device_profile = *CreateProfile();

                        JSON* device_item = item->GetFirstItem();
                        while (device_item)
                        {
                            device_profile->SetValue(device_item);
                            device_item = item->GetNextItem(device_item);
                        }

                        tags[1] = device_name;
                        SetTaggedProfile(tag_names, tags, 2, device_profile);
                    }

                    item = profileItem->GetNextItem(item);
                }

                // Add an explicit eye-height field
                float player_height = user_profile->GetFloatValue(OVR_KEY_PLAYER_HEIGHT,
                                                                  OVR_DEFAULT_PLAYER_HEIGHT);
                if (player_height > 0)
                {
                    char gender[16];
                    user_profile->GetValue(OVR_KEY_GENDER, gender, 16);
        
                    const float EYE_TO_HEADTOP_RATIO =   0.44538f;
                    const float MALE_AVG_HEAD_HEIGHT =   0.232f;
                    const float FEMALE_AVG_HEAD_HEIGHT = 0.218f;
     
                    // compute distance from top of skull to the eye
                    float head_height;
                    if (OVR_strcmp(gender, "Female") == 0)
                        head_height = FEMALE_AVG_HEAD_HEIGHT;
                    else
                        head_height = MALE_AVG_HEAD_HEIGHT;

                    float skull = EYE_TO_HEADTOP_RATIO * head_height;
                    float eye_height = player_height - skull;

                    user_profile->SetFloatValue(OVR_KEY_EYE_HEIGHT, eye_height);
                }

                // Convert NeckEye values to an array
                if (neckeye[0] > 0 && neckeye[1] > 0)
                    user_profile->SetFloatValues(OVR_KEY_NECK_TO_EYE_DISTANCE, neckeye, 2);

                // Add the user tag values
                SetTaggedProfile(tag_names, tags, 1, user_profile);
            }
        }
    }

    // since V1 profiles were only for DK1, the assign the user to all DK1's
    const char* tag_names[1] = { "Product" };
    const char* tags[1] = { "RiftDK1" };
    Ptr<Profile> product_profile = *CreateProfile();
    product_profile->SetValue("DefaultUser", default_dk1_user);
    SetTaggedProfile(tag_names, tags, 1, product_profile);
}