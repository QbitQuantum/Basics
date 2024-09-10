void CLayoutVertical::addChild(IWidget * widget, TAlignment align, int pos, int stretch)
{
    if (widget && !isChild(widget))
    {
        widget->setParent(this);

        int i = 0;
        int y = 0;

        TLayoutItem tmp;
        tmp.widget  = widget;
        tmp.align   = align;
        tmp.stretch = stretch;
        tmp.size    = widget->getHeight() + m_padding.getTop() + m_padding.getBottom();

        // On insère l'objet à la fin de la liste
        if (pos < 0 || pos >= getNumChildren())
        {
            m_children.push_back(tmp);
        }
        else
        {
            for (std::list<TLayoutItem>::iterator it = m_children.begin(); it != m_children.end(); ++it, ++i)
            {
                if (i == pos)
                {
                    it = m_children.insert(it, tmp);
                    y += tmp.size;
                }

                y += it->widget->getHeight();
            }
        }

        if (y > m_height)
        {
            setHeight(y);
        }
        else
        {
            computeSize();
        }
    }
}