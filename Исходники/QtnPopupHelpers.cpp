QRect PopupDrawHelper::subControlRect(ComplexControl control, const QStyleOptionComplex* opt, SubControl subControl, const QWidget* widget) const
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QRect rect = QCommonStyle::subControlRect(control, opt, subControl, widget);
#else
    QRect rect = QWindowsStyle::subControlRect(control, opt, subControl, widget);
#endif

    switch (control) 
    {
        case CC_TitleBar:
            if (const StyleOptionPopupTitleBar* bar = qstyleoption_cast<const StyleOptionPopupTitleBar*>(opt)) 
            {
                const int controlMargin = 2;
                const int controlHeight = bar->rect.height() - controlMargin/* *2*/;
                const int delta = controlHeight + controlMargin;
                switch (subControl) 
                {
                    case SC_TitleBarLabel: 
                        {
                            QRect rc = opt->rect;
                            QRect labelRect = bar->fontMetrics.boundingRect(bar->text);
                            int titleBarHeight = proxy()->pixelMetric(PM_TitleBarHeight, opt, widget);
                            rc.setHeight(titleBarHeight); 
                            int width = labelRect.width();
                            labelRect.moveCenter(rc.center());
                            labelRect.setLeft(0);
                            labelRect.setWidth(qMax(rc.width(), width));

                            if (bar->subControls & SC_TitleBarCloseButton)
                            {
                              QRect ir = proxy()->subControlRect(CC_TitleBar, bar, SC_TitleBarCloseButton, widget);
                              labelRect.adjust(bar->subControls & SC_TitleBarSysMenu ? delta : controlMargin, 0, -ir.width(), controlMargin);
                            }
                            else
                              labelRect.adjust(bar->subControls & SC_TitleBarSysMenu ? delta : controlMargin, 0, controlMargin, controlMargin);
                            rect = labelRect;
                            break;
                        }
                    case SC_TitleBarCloseButton:
                        {
                            QRect rc = opt->rect;
                            QRect rcButton;
                            rcButton.setHeight(13);
                            rcButton.setWidth(13);
                            int titleBarHeight = proxy()->pixelMetric(PM_TitleBarHeight, opt, widget);
                            rc.setHeight(titleBarHeight); 
                            int offsetX = rc.right() - 13 - 2;
                            int offsetY = (rc.height() - rcButton.height())/2;
                            rcButton.translate(offsetX, offsetY);
                            rect = rcButton;
                            break;
                        }
                    case SC_TitleBarSysMenu :
                        {
                            QRect rc = opt->rect;
                            rc.setRect(bar->rect.left() + controlMargin, bar->rect.top() + controlMargin,
                                controlHeight, controlHeight);
                            rect = rc;
                            break;
                        }
                    default:
                        break;
                }
            }
            break;
        default:
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
            return QCommonStyle::subControlRect(control, opt, subControl, widget);
#else
            return QWindowsStyle::subControlRect(control, opt, subControl, widget);
#endif
    }

    return rect;
}