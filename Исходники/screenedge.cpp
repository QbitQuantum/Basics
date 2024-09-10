void ScreenEdge::check(const QPoint& pos, Time now)
{
    if ((pos.x() != m_screenEdgeLeft) &&
            (pos.x() != m_screenEdgeRight) &&
            (pos.y() != m_screenEdgeTop) &&
            (pos.y() != m_screenEdgeBottom))
        return;

    bool have_borders = false;
    for (int i = 0; i < ELECTRIC_COUNT; ++i)
        if (m_screenEdgeWindows[i] != None)
            have_borders = true;
    if (!have_borders)
        return;

    Time treshold_set = options->electricBorderDelay(); // Set timeout
    Time treshold_reset = 250; // Reset timeout
    Time treshold_trigger = options->electricBorderCooldown(); // Minimum time between triggers
    int distance_reset = 30; // Mouse should not move more than this many pixels
    int pushback_pixels = options->electricBorderPushbackPixels();

    ElectricBorder border;
    if (pos.x() == m_screenEdgeLeft && pos.y() == m_screenEdgeTop)
        border = ElectricTopLeft;
    else if (pos.x() == m_screenEdgeRight && pos.y() == m_screenEdgeTop)
        border = ElectricTopRight;
    else if (pos.x() == m_screenEdgeLeft && pos.y() == m_screenEdgeBottom)
        border = ElectricBottomLeft;
    else if (pos.x() == m_screenEdgeRight && pos.y() == m_screenEdgeBottom)
        border = ElectricBottomRight;
    else if (pos.x() == m_screenEdgeLeft)
        border = ElectricLeft;
    else if (pos.x() == m_screenEdgeRight)
        border = ElectricRight;
    else if (pos.y() == m_screenEdgeTop)
        border = ElectricTop;
    else if (pos.y() == m_screenEdgeBottom)
        border = ElectricBottom;
    else
        abort();

    if (m_screenEdgeWindows[border] == None)
        return;

    if (pushback_pixels == 0) {
        // no pushback so we have to activate at once
        m_screenEdgeTimeLast = now;
        m_currentScreenEdge = border;
        m_screenEdgePushPoint = pos;
    }

    if ((m_currentScreenEdge == border) &&
            (timestampDiff(m_screenEdgeTimeLast, now) < treshold_reset) &&
            (timestampDiff(m_screenEdgeTimeLastTrigger, now) > treshold_trigger) &&
            ((pos - m_screenEdgePushPoint).manhattanLength() < distance_reset)) {
        m_screenEdgeTimeLast = now;

        if (timestampDiff(m_screenEdgeTimeFirst, now) > treshold_set) {
            m_currentScreenEdge = ElectricNone;
            m_screenEdgeTimeLastTrigger = now;
            if (Workspace::self()->getMovingClient()) {
                // If moving a client or have force doing the desktop switch
                if (options->electricBorders() != Options::ElectricDisabled)
                    switchDesktop(border, pos);
                return; // Don't reset cursor position
            } else {
                if (options->electricBorders() == Options::ElectricAlways &&
                        (border == ElectricTop || border == ElectricRight ||
                         border == ElectricBottom || border == ElectricLeft)) {
                    // If desktop switching is always enabled don't apply it to the corners if
                    // an effect is applied to it (We will check that later).
                    switchDesktop(border, pos);
                    return; // Don't reset cursor position
                }
                switch(options->electricBorderAction(border)) {
                case ElectricActionDashboard: { // Display Plasma dashboard
                    QDBusInterface plasmaApp("org.kde.plasma-desktop", "/App");
                    plasmaApp.call("toggleDashboard");
                }
                break;
                case ElectricActionShowDesktop: {
                    Workspace::self()->setShowingDesktop(!Workspace::self()->showingDesktop());
                    break;
                }
                case ElectricActionLockScreen: { // Lock the screen
                    QDBusInterface screenSaver("org.kde.screensaver", "/ScreenSaver");
                    screenSaver.call("Lock");
                }
                break;
                case ElectricActionPreventScreenLocking: {
                    break;
                }
                case ElectricActionNone: // Either desktop switching or an effect
                default: {
                    if (effects && static_cast<EffectsHandlerImpl*>(effects)->borderActivated(border))
                        {} // Handled by effects
                    else {
                        if (options->electricBorders() == Options::ElectricAlways) {
                            switchDesktop(border, pos);
                            return; // Don't reset cursor position
                        }
                        emit activated(border);
                    }
                }
                }
            }
        }
    } else {
        m_currentScreenEdge = border;
        m_screenEdgeTimeFirst = now;
        m_screenEdgeTimeLast = now;
        m_screenEdgePushPoint = pos;
    }

    // Reset the pointer to find out whether the user is really pushing
    // (the direction back from which it came, starting from top clockwise)
    const int xdiff[ELECTRIC_COUNT] = { 0,
                                        -pushback_pixels,
                                        -pushback_pixels,
                                        -pushback_pixels,
                                        0,
                                        pushback_pixels,
                                        pushback_pixels,
                                        pushback_pixels
                                      };
    const int ydiff[ELECTRIC_COUNT] = { pushback_pixels,
                                        pushback_pixels,
                                        0,
                                        -pushback_pixels,
                                        -pushback_pixels,
                                        -pushback_pixels,
                                        0,
                                        pushback_pixels
                                      };
    QCursor::setPos(pos.x() + xdiff[border], pos.y() + ydiff[border]);
}