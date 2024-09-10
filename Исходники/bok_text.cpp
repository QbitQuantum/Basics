void glyphatlas::freeTile(struct glyphtile *t)
{
    t->release();

    if (!t->face_)
        return;

    used_.remove(t);
    free_.push_front(t);
}