Relation Relation::Join(pair<vector<Token>, vector<Token> >& pair, Relation* nextRelation)
{
    Relation thisAfterSelect = this->select(pair.first);
    Relation thisAfterProject = thisAfterSelect.project(pair.first, 0);
    pair.first = removeStrings(pair.first);

    if(nextRelation != 0)
    {
        Relation thatAfterSelect = nextRelation->select(pair.second);
        Relation thatAfterRename = thatAfterSelect.rename(pair, *this);
        Relation thatAfterProject = thatAfterRename.project(pair.second, 0);
        Relation allAfterCCP = thisAfterProject.CartesianCrossProduct(pair, thatAfterProject);
        return allAfterCCP;
    }
    else
    {
        return thisAfterProject;
    }
}