    bool DialogueManager::isMatching (const MWWorld::Ptr& actor,
        const ESM::DialInfo::SelectStruct& select) const
    {
        char type = select.selectRule[1];

        if (type!='0')
        {
            char comp = select.selectRule[4];
            std::string name = select.selectRule.substr (5);

            // TODO types 4, 5, 6, 7, 8, 9, A, B, C

            switch (type)
            {
                case '1': // function

                    return false; // TODO implement functions

                case '2': // global

                    if (select.type==ESM::VT_Short || select.type==ESM::VT_Int ||
                        select.type==ESM::VT_Long)
                    {
                        if (!checkGlobal (comp, toLower (name), select.i, *mEnvironment.mWorld))
                            return false;
                    }
                    else if (select.type==ESM::VT_Float)
                    {
                        if (!checkGlobal (comp, toLower (name), select.f, *mEnvironment.mWorld))
                            return false;
                    }
                    else
                        throw std::runtime_error (
                            "unsupported variable type in dialogue info select");

                    return true;

                case '3': // local

                    if (select.type==ESM::VT_Short || select.type==ESM::VT_Int ||
                        select.type==ESM::VT_Long)
                    {
                        if (!checkLocal (comp, toLower (name), select.i, actor,
                            mEnvironment.mWorld->getStore()))
                            return false;
                    }
                    else if (select.type==ESM::VT_Float)
                    {
                        if (!checkLocal (comp, toLower (name), select.f, actor,
                            mEnvironment.mWorld->getStore()))
                            return false;
                    }
                    else
                        throw std::runtime_error (
                            "unsupported variable type in dialogue info select");

                    return true;

                default:

                    std::cout << "unchecked select: " << type << " " << comp << " " << name << std::endl;
            }
        }

        return true;
    }