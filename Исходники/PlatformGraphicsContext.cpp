void PlatformGraphicsContext::storeButtonInfo(Node* node, const IntRect& r)
{
    if (m_buttons == NULL)
        return;
    // Check to see if we already have a Container for this node.  If so, update
    // it with the new rectangle and make the new recording canvas reference
    // its picture.
    Container* end = m_buttons->end();
    for (Container* ptr = m_buttons->begin(); ptr != end; ptr++) {
        if (ptr->matches(node)) {
            mCanvas->drawPicture(*(ptr->picture()));
            ptr->setRect(r);
            return;
        }
    }
    // We did not have a Container representing this node, so create a new one.
    Container container(node, r);
    // Place a reference to our subpicture in the Picture.
    mCanvas->drawPicture(*(container.picture()));
    // Keep track of the information about the button.
    m_buttons->append(container);
}