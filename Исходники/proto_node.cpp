int ProtoNode::row()
{
    if (!isChild()) {
        return -1;
    }

    int cur_row = 0;
    ProtoNode::ChildIterator kids = parentNode().children();
    while ( kids.element().isValid() )
    {
        if ( kids.element().protoNode() == node_ ) {
            break;
        }
        cur_row++;
        kids.next();
    }
    if ( ! kids.element().isValid() ) {
        return -1;
    }
    return cur_row;
}