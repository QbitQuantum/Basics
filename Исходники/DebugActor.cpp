    void DebugActor::onDAEvent(Event* ev)
    {
        TouchEvent* t = safeCast<TouchEvent*>(ev);
        Vector2 loc = parent2local(t->localPosition);
        if (t->type == TouchEvent::MOVE)
        {
            setAlpha(isOn(loc) ? 64 : 255);

            if (_dragging)
            {
                Transform tr = getTransform();
                tr.x = 0;
                tr.y = 0;
                Vector2 p = tr.transform(_local);
                setPosition(t->localPosition - p);
            }
        }

        if (t->type == TouchEvent::TOUCH_DOWN)
        {
            if (isOn(loc))
            {
                _local = loc;
                _dragging = true;
            }
        }
        if (t->type == TouchEvent::TOUCH_UP)
        {
            _dragging = false;
        }
    }