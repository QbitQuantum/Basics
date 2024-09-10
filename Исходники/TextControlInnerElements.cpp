void SearchFieldCancelButtonElement::defaultEventHandler(Event* event)
{
    // If the element is visible, on mouseup, clear the value, and set selection
    HTMLInputElement* input = static_cast<HTMLInputElement*>(shadowAncestorNode());
    if (event->type() == eventNames().mousedownEvent && event->isMouseEvent() && static_cast<MouseEvent*>(event)->button() == LeftButton) {
        if (renderer() && renderer()->visibleToHitTesting()) {
            if (Frame* frame = document()->frame()) {
                frame->eventHandler()->setCapturingMouseEventsNode(this);
                m_capturing = true;
            }
        }
        input->focus();
        input->select();
        event->setDefaultHandled();
    }
    if (event->type() == eventNames().mouseupEvent && event->isMouseEvent() && static_cast<MouseEvent*>(event)->button() == LeftButton) {
        if (m_capturing && renderer() && renderer()->visibleToHitTesting()) {
            if (Frame* frame = document()->frame()) {
                frame->eventHandler()->setCapturingMouseEventsNode(0);
                m_capturing = false;
            }
#if !PLATFORM(OLYMPIA)
            // FIXME: It's always false on OLYMPIA platform. This problem depends on RIM bug #1067.
            if (hovered()) {
#else
            if (event->target() == this) {
#endif
                RefPtr<HTMLInputElement> protector(input);
                String oldValue = input->value();
                input->setValue("");
                if (!oldValue.isEmpty()) {
                    toRenderTextControl(input->renderer())->setChangedSinceLastChangeEvent(true);
                    input->dispatchEvent(Event::create(eventNames().inputEvent, true, false));
                }
                input->onSearch();
                event->setDefaultHandled();
            }
        }
    }

    if (!event->defaultHandled())
        HTMLDivElement::defaultEventHandler(event);
}

// ----------------------------

inline SpinButtonElement::SpinButtonElement(HTMLElement* shadowParent)
    : TextControlInnerElement(shadowParent->document(), shadowParent)
    , m_capturing(false)
    , m_upDownState(Indeterminate)
    , m_pressStartingState(Indeterminate)
    , m_repeatingTimer(this, &SpinButtonElement::repeatingTimerFired)
{
}

PassRefPtr<SpinButtonElement> SpinButtonElement::create(HTMLElement* shadowParent)
{
    return adoptRef(new SpinButtonElement(shadowParent));
}

void SpinButtonElement::defaultEventHandler(Event* event)
{
    if (!event->isMouseEvent()) {
        if (!event->defaultHandled())
            HTMLDivElement::defaultEventHandler(event);
        return;
    }

    RenderBox* box = renderBox();
    if (!box) {
        if (!event->defaultHandled())
            HTMLDivElement::defaultEventHandler(event);
        return;        
    }
    
    HTMLInputElement* input = static_cast<HTMLInputElement*>(shadowAncestorNode());
    if (input->disabled() || input->isReadOnlyFormControl()) {
        if (!event->defaultHandled())
            HTMLDivElement::defaultEventHandler(event);
        return;
    }

    MouseEvent* mouseEvent = static_cast<MouseEvent*>(event);
    IntPoint local = roundedIntPoint(box->absoluteToLocal(mouseEvent->absoluteLocation(), false, true));
    if (mouseEvent->type() == eventNames().mousedownEvent && mouseEvent->button() == LeftButton) {
        if (box->borderBoxRect().contains(local)) {
            RefPtr<Node> protector(input);
            input->focus();
            input->select();
            input->stepUpFromRenderer(m_upDownState == Up ? 1 : -1);
            event->setDefaultHandled();
            startRepeatingTimer();
        }
    } else if (mouseEvent->type() == eventNames().mouseupEvent && mouseEvent->button() == LeftButton)
        stopRepeatingTimer();
    else if (event->type() == eventNames().mousemoveEvent) {
        if (box->borderBoxRect().contains(local)) {
            if (!m_capturing) {
                if (Frame* frame = document()->frame()) {
                    frame->eventHandler()->setCapturingMouseEventsNode(this);
                    m_capturing = true;
                }
            }
            UpDownState oldUpDownState = m_upDownState;
            m_upDownState = local.y() < box->height() / 2 ? Up : Down;
            if (m_upDownState != oldUpDownState)
                renderer()->repaint();
        } else {
            if (m_capturing) {
                stopRepeatingTimer();
                if (Frame* frame = document()->frame()) {
                    frame->eventHandler()->setCapturingMouseEventsNode(0);
                    m_capturing = false;
                }
            }
        }
    }

    if (!event->defaultHandled())
        HTMLDivElement::defaultEventHandler(event);
}

void SpinButtonElement::startRepeatingTimer()
{
    m_pressStartingState = m_upDownState;
    ScrollbarTheme* theme = ScrollbarTheme::nativeTheme();
    m_repeatingTimer.start(theme->initialAutoscrollTimerDelay(), theme->autoscrollTimerDelay());
}