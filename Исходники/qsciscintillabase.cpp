// The dtor.
QsciScintillaBase::~QsciScintillaBase()
{
    // Remove it from the pool.
    poolList.remove(this);

    delete sci;
}