void QStyleItem::paint(QPainter *painter)
{
    if (width() < 1 || height() <1)
        return;

    initStyleOption();

    switch (m_itemType) {
    case Button:
        qApp->style()->drawControl(QStyle::CE_PushButton, m_styleoption, painter);
        break;
    case ItemRow :{
        QPixmap pixmap;
        // Only draw through style once
        const QString pmKey = QLatin1Literal("itemrow") % QString::number(m_styleoption->state,16) % activeControl();
        if (!QPixmapCache::find(pmKey, pixmap) || pixmap.width() < width() || height() != pixmap.height()) {
            int newSize = width();
            pixmap = QPixmap(newSize, height());
            pixmap.fill(Qt::transparent);
            QPainter pixpainter(&pixmap);
            qApp->style()->drawPrimitive(QStyle::PE_PanelItemViewRow, m_styleoption, &pixpainter);
            if (!qApp->style()->styleHint(QStyle::SH_ItemView_ShowDecorationSelected) && selected())
                pixpainter.fillRect(m_styleoption->rect, m_styleoption->palette.highlight());
            QPixmapCache::insert(pmKey, pixmap);
        }
        painter->drawPixmap(0, 0, pixmap);
    }
        break;
    case Item:
        qApp->style()->drawControl(QStyle::CE_ItemViewItem, m_styleoption, painter);
        break;
    case Header:
        qApp->style()->drawControl(QStyle::CE_Header, m_styleoption, painter);
        break;
    case ToolButton:

#ifdef Q_OS_MAC
        if (style() == "mac" && hint().indexOf("segmented") != -1) {
            const QPaintDevice *target = painter->device();
             HIThemeSegmentDrawInfo sgi;
            sgi.version = 0;
            sgi.state = isEnabled() ? kThemeStateActive : kThemeStateDisabled;
            if (sunken()) sgi.state |= kThemeStatePressed;
            sgi.size = kHIThemeSegmentSizeNormal;
            sgi.kind = kHIThemeSegmentKindTextured;
            sgi.value = on() && !sunken() ? kThemeButtonOn : kThemeButtonOff;

            sgi.adornment |= kHIThemeSegmentAdornmentLeadingSeparator;
            if (sunken()) {
                sgi.adornment |= kHIThemeSegmentAdornmentTrailingSeparator;
            }
            SInt32 button_height;
            GetThemeMetric(kThemeMetricButtonRoundedHeight, &button_height);
            sgi.position = info() == "leftmost" ? kHIThemeSegmentPositionFirst:
                                                  info() == "rightmost" ? kHIThemeSegmentPositionLast :
                                                               info() == "h_middle" ? kHIThemeSegmentPositionMiddle :
                                                                                   kHIThemeSegmentPositionOnly;
            QRect centered = m_styleoption->rect;
            centered.setHeight(button_height);
            centered.moveCenter(m_styleoption->rect.center());
            HIRect hirect = qt_hirectForQRect(centered.translated(0, -1), QRect(0, 0, 0, 0));
            HIThemeDrawSegment(&hirect, &sgi, qt_mac_cg_context(target), kHIThemeOrientationNormal);
        } else
#endif
        qApp->style()->drawComplexControl(QStyle::CC_ToolButton, qstyleoption_cast<QStyleOptionComplex*>(m_styleoption), painter);
        break;
    case Tab:
        qApp->style()->drawControl(QStyle::CE_TabBarTab, m_styleoption, painter);
        break;
    case Frame:
        qApp->style()->drawControl(QStyle::CE_ShapedFrame, m_styleoption, painter);
        break;
    case FocusFrame:
        if (style() == "mac" && hint().indexOf("rounded") != -1)
            break; // embedded in the line itself
        else
            qApp->style()->drawControl(QStyle::CE_FocusFrame, m_styleoption, painter);
        break;
    case TabFrame:
        qApp->style()->drawPrimitive(QStyle::PE_FrameTabWidget, m_styleoption, painter);
        break;
    case MenuBar:
        qApp->style()->drawControl(QStyle::CE_MenuBarEmptyArea, m_styleoption, painter);
        break;
    case MenuBarItem:
        qApp->style()->drawControl(QStyle::CE_MenuBarItem, m_styleoption, painter);
        break;
    case MenuItem:
    case ComboBoxItem: // fall through
        qApp->style()->drawControl(QStyle::CE_MenuItem, m_styleoption, painter);
        break;
    case CheckBox:
        qApp->style()->drawControl(QStyle::CE_CheckBox, m_styleoption, painter);
        break;
    case RadioButton:
        qApp->style()->drawControl(QStyle::CE_RadioButton, m_styleoption, painter);
        break;
    case Edit: {
#ifdef Q_OS_MAC
        if (style() == "mac" && hint().indexOf("rounded") != -1) {
            const QPaintDevice *target = painter->device();
            HIThemeFrameDrawInfo fdi;
            fdi.version = 0;
            fdi.state = kThemeStateActive;
            SInt32 frame_size;
            GetThemeMetric(kThemeMetricEditTextFrameOutset, &frame_size);
            fdi.kind = kHIThemeFrameTextFieldRound;
            if ((m_styleoption->state & QStyle::State_ReadOnly) || !(m_styleoption->state & QStyle::State_Enabled))
                fdi.state = kThemeStateInactive;
            fdi.isFocused = hasFocus();
            HIRect hirect = qt_hirectForQRect(m_styleoption->rect,
                                              QRect(frame_size, frame_size,
                                                    frame_size * 2, frame_size * 2));
            HIThemeDrawFrame(&hirect, &fdi, qt_mac_cg_context(target), kHIThemeOrientationNormal);
        } else
#endif
        qApp->style()->drawPrimitive(QStyle::PE_PanelLineEdit, m_styleoption, painter);
    }
        break;
    case MacHelpButton:
#ifdef Q_OS_MAC
    {
        const QPaintDevice *target = painter->device();
        HIThemeButtonDrawInfo fdi;
        fdi.kind = kThemeRoundButtonHelp;
        fdi.version = 0;
        fdi.adornment = 0;
        fdi.state = sunken() ? kThemeStatePressed : kThemeStateActive;
        HIRect hirect = qt_hirectForQRect(m_styleoption->rect,QRect(0, 0, 0, 0));
        HIThemeDrawButton(&hirect, &fdi, qt_mac_cg_context(target), kHIThemeOrientationNormal, NULL);
    }
#endif
        break;
    case Widget:
        qApp->style()->drawPrimitive(QStyle::PE_Widget, m_styleoption, painter);
        break;
    case ScrollAreaCorner:
        qApp->style()->drawPrimitive(QStyle::PE_PanelScrollAreaCorner, m_styleoption, painter);
        break;
    case Splitter:
        if (m_styleoption->rect.width() == 1)
            painter->fillRect(0, 0, width(), height(), m_styleoption->palette.dark().color());
        else
            qApp->style()->drawControl(QStyle::CE_Splitter, m_styleoption, painter);
        break;
    case ComboBox:
    {
        qApp->style()->drawComplexControl(QStyle::CC_ComboBox,
                                          qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                          painter);
        // This is needed on mac as it will use the painter color and ignore the palette
        QPen pen = painter->pen();
        painter->setPen(m_styleoption->palette.text().color());
        qApp->style()->drawControl(QStyle::CE_ComboBoxLabel, m_styleoption, painter);
        painter->setPen(pen);
    }    break;
    case SpinBox:
        qApp->style()->drawComplexControl(QStyle::CC_SpinBox,
                                          qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                          painter);
        break;
    case Slider:
        qApp->style()->drawComplexControl(QStyle::CC_Slider,
                                          qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                          painter);
        break;
    case Dial:
        qApp->style()->drawComplexControl(QStyle::CC_Dial,
                                          qstyleoption_cast<QStyleOptionComplex*>(m_styleoption),
                                          painter);
        break;
    case ProgressBar:
        qApp->style()->drawControl(QStyle::CE_ProgressBar, m_styleoption, painter);
        break;
    case ToolBar:
        qApp->style()->drawControl(QStyle::CE_ToolBar, m_styleoption, painter);
        break;
    case StatusBar:
        if (style() == "mac") {
            m_styleoption->rect.adjust(0, 1, 0, 0);
            qApp->style()->drawControl(QStyle::CE_ToolBar, m_styleoption, painter);
            m_styleoption->rect.adjust(0, -1, 0, 0);
            painter->setPen(m_styleoption->palette.dark().color().darker(120));
            painter->drawLine(m_styleoption->rect.topLeft(), m_styleoption->rect.topRight());
        } else {
            qApp->style()->drawPrimitive(QStyle::PE_PanelToolBar, m_styleoption, painter);
        }
        break;
    case GroupBox:
        qApp->style()->drawComplexControl(QStyle::CC_GroupBox, qstyleoption_cast<QStyleOptionComplex*>(m_styleoption), painter);
        break;
    case ScrollBar:
        qApp->style()->drawComplexControl(QStyle::CC_ScrollBar, qstyleoption_cast<QStyleOptionComplex*>(m_styleoption), painter);
        break;
    case Menu: {
        QStyleHintReturnMask val;
        qApp->style()->styleHint(QStyle::SH_Menu_Mask, m_styleoption, 0, &val);
        painter->save();
        painter->setClipRegion(val.region);
        painter->fillRect(m_styleoption->rect, m_styleoption->palette.window());
        painter->restore();
        qApp->style()->drawPrimitive(QStyle::PE_PanelMenu, m_styleoption, painter);

        QStyleOptionFrame frame;
        frame.lineWidth = qApp->style()->pixelMetric(QStyle::PM_MenuPanelWidth);
        frame.midLineWidth = 0;
        frame.rect = m_styleoption->rect;
        qApp->style()->drawPrimitive(QStyle::PE_FrameMenu, &frame, painter);
    }
        break;
    default:
        break;
    }
}