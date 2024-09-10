void HTMLSearchFieldCancelButtonElement::defaultEventHandler(Event* evt)
{
    // If the element is visible, on mouseup, clear the value, and set selection
    HTMLInputElement* input = static_cast<HTMLInputElement*>(shadowAncestorNode());
    if (evt->type() == mousedownEvent) {
        input->focus();
        input->select();
        evt->setDefaultHandled();
    } else if (evt->type() == mouseupEvent) {
        if (renderer() && renderer()->style()->visibility() == VISIBLE) {
            input->setValue("");
            //input->onSearch();
            evt->setDefaultHandled();
        }
    }
    if (!evt->defaultHandled())
        HTMLDivElement::defaultEventHandler(evt);
}