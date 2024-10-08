bool AutoResponse::processMsg(std::string msg, uint16_t whatModule, std::string nick, std::string ownNick, std::vector<std::string>& out)
{
    bool ok = false;

    toLower(msg);

    std::vector<ConfigHandler::AutoResponseRule>::iterator it;
    ConfigHandler::AutoResponseRule r;
    for(it = _rules->begin(); it != _rules->end(); it++)
    {
        r = *it;

        //std::cout << "AutoResponse::processMsgRetroShare() rule " << r.name << std::endl;

        // check if rule applies to retroshare
        //std::cout << "AutoResponse::processMsgRetroShare() usedBy=" << r.usedBy << " mod=" << whatModule << std::endl;
        if(!Utils::isModuleAll(r.usedBy) && !(r.usedBy & whatModule))
            continue;

        //std::cout << "AutoResponse::processMsgRetroShare() rule " << r.name << " applies" << std::endl;

        {
            std::string tmpNick = ownNick;
            toLower(tmpNick);
            ApplyReplacements(r.searchFor, nick, tmpNick);
        }
        std::size_t pos = msg.find(r.searchFor);

        //std::cout << "AutoResponse::processMsgRetroShare() find()=" << pos << " found" << std::endl;
        //std::cout << "AutoResponse::processMsgRetroShare() msg=" << msg << " searchFor=" << r.searchFor << std::endl;

        // check if keyword is in the message at all
        if(pos == std::string::npos)
            continue;

        //std::cout << "AutoResponse::processMsgRetroShare() key word " << r.searchFor << " found" << std::endl;

        // check for leading character
        if(r.hasLeadingChar && (pos == 0 || msg[pos-1] != r.leadingChar))
            continue;

        //std::cout << "AutoResponse::processMsgRetroShare() leading char check passed" << std::endl;

        // FYI: at this point we know that the key word is in the message at position pos
        //      and that the leading character - if required - is ok

        // check for context
        if(!r.allowContext && ( // no context is allowed
                    (msg.size() > r.searchFor.size() && !r.hasLeadingChar) ||   // msg == key word
                    (msg.size() > r.searchFor.size() + 1 && r.hasLeadingChar)   // msg == key word + 1 char
                ))
            continue;

        // "/me bla" is ok - "/mebla" not -> check if there is space around the key word(s)
        if(r.isSeparated && (
                (msg.size() > pos + r.searchFor.size() && msg[pos + r.searchFor.size()] != ' ') ||  // after the key word(s)
                (r.hasLeadingChar && pos > 1 && msg[pos - 2] != ' ') ||                             // before with leading chat
                (!r.hasLeadingChar && pos > 0 && msg[pos - 1] != ' ')))                             // before withou leading char
            continue;

        //std::cout << "AutoResponse::processMsgRetroShare() context check passed" << std::endl;

        // all seems good
        std::string ans = r.answer;
        ApplyReplacements(ans, nick, ownNick);
        if(whatModule == Utils::MODULE_IRC)
            fixNewLineForIrc(ans);
        out.push_back(ans);
        ok = true;
    }

    return ok;
}