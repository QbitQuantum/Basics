    static void getValueTreePath (ValueTree v, const ValueTree& topLevelTree, Array<int>& path)
    {
        while (v != topLevelTree)
        {
            ValueTree parent (v.getParent());

            if (! parent.isValid())
                break;

            path.add (parent.indexOf (v));
            v = parent;
        }
    }