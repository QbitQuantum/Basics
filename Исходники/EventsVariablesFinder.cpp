std::set < std::string > EventsVariablesFinder::FindAllGlobalVariables(const gd::Platform & platform, const gd::Project & project)
{
    std::set < std::string > results;

    for (unsigned int i = 0;i<project.GetLayoutsCount();++i)
    {
        std::set < std::string > results2 = FindArgumentsInEvents(platform, project, project.GetLayout(i), project.GetLayout(i).GetEvents(), "globalvar");
        results.insert(results2.begin(), results2.end());
    }

    return results;
}