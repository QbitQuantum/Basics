int length(Doublet doublet) {
    if (doublet.getCar()->getObjectType() == NIL) {
        return 0;
    }

    Object * cdr = doublet.getCdr();

    if (cdr->getObjectType() != DOUBLET) {
        return 1;
    }

    Doublet * doubletCdr = dynamic_cast<Doublet *>(cdr);

    return 1 + length(*doubletCdr);
}