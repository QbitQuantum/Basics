StackTamper StackTamperVisitor::tampersStack(AST::Ptr a, Address &newAddr) {

    if(tamper_ != TAMPER_UNSET) {
        newAddr = modpc_;
        return tamper_;
    }

    a->accept(this);

    if (tamper_ == TAMPER_NONZERO) {
        return tamper_;
    }

    assert(diffs_.size() == 1);

    modpc_ = diffs_.top().a.x;

    switch(diffs_.top().b.x) {
    case 0:
        tamper_ = TAMPER_ABS;
        break;
    case 1:
        if (modpc_) {
            tamper_ = TAMPER_REL;
        } else {
            tamper_ = TAMPER_NONE;
        }
        break;
    default:
        tamper_ = TAMPER_NONZERO;
        break;
    }
    newAddr = modpc_;
    return tamper_;
}