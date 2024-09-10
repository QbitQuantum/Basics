	ChildListId RetainedEntities::GetChildListId(ObjectTypeId typeId, const utf8 name[]) const
    {
        auto type = GetObjectType(typeId);
        if (!type) return 0;

        for (auto i=type->_childLists.cbegin(); i!=type->_childLists.cend(); ++i)
            if (!XlCompareStringI(i->c_str(), name)) 
                return (PropertyId)std::distance(type->_childLists.cbegin(), i);
        
        type->_childLists.push_back(name);
        return (PropertyId)(type->_childLists.size()-1);
    }