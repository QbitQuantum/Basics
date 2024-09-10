std::string CostFactory::camelCasedToUnderscored(const std::string& name)
{
    std::string result;
    
    for (int i=0; i<name.size(); i++)
    {
        if (i && isUpper(name[i]))
            result += std::string("_") + toLower(name[i]);
        else
            result += toLower(name[i]);
    }
    
    return result;
}