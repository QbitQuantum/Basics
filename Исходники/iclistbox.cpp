//
// ICListBox::SetupCellSize
//
// Setup cell size if needed
//
Bool ICListBox::SetupCellSize()
{
    ASSERT(IsActive())

#ifdef LOGGING
    Clock::CycleWatch t;
    t.Start();
#endif

    S32 idx = 0;
    S32 visible = 0;
    NList<IControl>::Iterator i(&container->children);

    for (; idx < top; idx++, i++)
    {
        if (*i)
        {
            (*i)->MoveTo(Point<S32>(0, paintInfo.client.Height()));
            (*i)->SetVisible(FALSE);
        }
    }

    for (S32 y = 0; *i;)
    {
        IControl *p = *i;
        S32 h = p->GetPaintInfo().window.Height();

        // No more room
        if (y + h > GetPaintInfo().client.Height())
        {
            break;
        }

        // Move it
        p->MoveTo(Point<S32>(0, y));

        // And make it visible
        p->SetVisible(TRUE);

        /*
        // If it's bigger than the client window, setup tool tip
        if (p->GetPaintInfo().window.p1.x > paintInfo.client.p1.x)
        {
          if (p->textStr)
          {
            p->SetTipText(p->textStr, TRUE);
          }
        }
        else
        {
          p->SetTipText(NULL, FALSE);
        }
        */


        idx++;
        i++;
        visible++;
        y += h;
    }

    vis = visible;

    for (; *i; i++)
    {
        (*i)->MoveTo(Point<S32>(0, paintInfo.client.Height()));
        (*i)->SetVisible(FALSE);
    }

#ifdef LOGGING
    t.Stop();
    LOG_IFACE(("SetupCellSize [%s] %d cycles", Name(), U32(t.GetTotal())))
#endif

    return (TRUE);
}