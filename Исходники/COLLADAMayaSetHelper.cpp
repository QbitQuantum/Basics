    // ------------------------------------------------------
    // Unlike Maya's default behavior, we want to consider set membership to be inheritable
    bool SetHelper::isMemberOfSet ( const MDagPath& dagPath, MFnSet& Set )
    {
        if ( Set.isMember ( dagPath ) )
        {
            return true;
        }

        else
        {
            MFnDagNode dagNode ( dagPath );
            MSelectionList setMembers;
            Set.getMembers ( setMembers, true );

            for ( unsigned int i = 0; i < setMembers.length(); ++i )
            {
                MObject memberObject;

                if ( setMembers.getDependNode ( i, memberObject ) )
                {
                    if ( dagNode.isChildOf ( memberObject ) )
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }