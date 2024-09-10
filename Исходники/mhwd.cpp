std::vector<std::string> mhwd::splitValue(Vita::string str, Vita::string onlyEnding) {
    std::vector<Vita::string> work = str.toLower().explode(" ");
    std::vector<std::string> final;

    for (std::vector<Vita::string>::const_iterator iterator = work.begin(); iterator != work.end(); iterator++) {
        if (*iterator != "" && onlyEnding.empty())
            final.push_back(*iterator);
        else if (*iterator != "" && Vita::string(*iterator).explode(".").back() == onlyEnding && (*iterator).size() > 5)
            final.push_back(Vita::string(*iterator).substr(0, (*iterator).size() - 5));
    }