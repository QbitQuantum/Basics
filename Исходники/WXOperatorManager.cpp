//-----------------------------------------------------------------------
size_t OperatorManager::redo(const String& groupName, size_t count)
{
    size_t n = 0;

    Group* group = findGroup(groupName);
    if (group)
    {
        n = group->redo(count);

        // Move all redo'ed operator from redo list to undo list
        size_t m = 0;
        OperatorList::iterator itRedo = mRedoList.begin();
        OperatorList::iterator itUndo = mUndoList.begin();
        while (m < n && itRedo != mRedoList.end())
        {
            Operator* op = *itRedo;
            if (op->getGroupName() == groupName)
            {
                // Find the correct insert place, undo list is sort descend by timestamp
                size_t timestamp = op->getTimestamp();
                while (itUndo != mUndoList.end() && timestamp < (*itUndo)->getTimestamp())
                {
                    ++itUndo;
                }
                mUndoList.insert(itUndo, op);
                mRedoList.erase(itRedo++);
                ++m;
            }
            else
            {
                ++itRedo;
            }
        }
        assert(m == n);
    }

    return n;
}