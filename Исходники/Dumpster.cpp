Item* Dumpster::take(Int index) {
    CORRADE_INTERNAL_ASSERT(_dumpsterItems[index]);

    Item* i = _dumpsterItems[index];
    i->drawables()->remove(*i);
    i->setParent(nullptr);

    _dumpsterItems[index] = nullptr;
    _dumpsterSprites[index]->reset(dumpsterSpriteSize, "dumpster-off");

    return i;
}