void GridLabel::deselect(void)
{
    RectF r;
    r.setLeft(-2);
    r.setRight(-2);
    r.setTop(-1);
    r.setBottom(-1);
    m_pEditData->setCatchRect(r);
    update();
}