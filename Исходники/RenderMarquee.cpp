void RenderMarquee::styleDidChange(StyleDifference difference, const RenderStyle* oldStyle)
{
    RenderBlockFlow::styleDidChange(difference, oldStyle);

    RenderStyle* s = style();

    if (m_direction != s->marqueeDirection() || (m_totalLoops != s->marqueeLoopCount() && m_currentLoop >= m_totalLoops))
        m_currentLoop = 0; // When direction changes or our loopCount is a smaller number than our current loop, reset our loop.

    m_totalLoops = s->marqueeLoopCount();
    m_direction = s->marqueeDirection();

    // Hack for WinIE. In WinIE, a value of 0 or lower for the loop count for SLIDE means to only do
    // one loop.
    if (m_totalLoops <= 0 && s->marqueeBehavior() == MSLIDE)
        m_totalLoops = 1;

    // Hack alert: Set the white-space value to nowrap for horizontal marquees with inline children, thus ensuring
    // all the text ends up on one line by default. Limit this hack to the <marquee> element to emulate
    // WinIE's behavior. Someone using CSS3 can use white-space: nowrap on their own to get this effect.
    // Second hack alert: Set the text-align back to auto. WinIE completely ignores text-align on the
    // marquee element.
    // FIXME: Bring these up with the CSS WG.
    if (isHorizontal() && childrenInline()) {
        s->setWhiteSpace(NOWRAP);
        s->setTextAlign(TASTART);
    }

    // Legacy hack - multiple browsers default vertical marquees to 200px tall.
    if (!isHorizontal() && s->height().isAuto())
        s->setHeight(Length(200, Fixed));

    if (speed() != marqueeSpeed()) {
        m_speed = marqueeSpeed();
        if (m_timer.isActive())
            m_timer.startRepeating(speed() * 0.001, FROM_HERE);
    }

    // Check the loop count to see if we should now stop.
    bool activate = (m_totalLoops <= 0 || m_currentLoop < m_totalLoops);
    if (activate && !m_timer.isActive())
        setNeedsLayoutAndFullPaintInvalidation();
    else if (!activate && m_timer.isActive())
        m_timer.stop();
}