void FancyTabProxyStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *p, const QWidget *widget) const
{

    const QStyleOptionTabV3 *v3Opt = qstyleoption_cast<const QStyleOptionTabV3*>(option);

    if (element != CE_TabBarTab || !v3Opt) {
        QProxyStyle::drawControl(element, option, p, widget);
        return;
    }

    const QRect rect = v3Opt->rect;
    const bool selected = v3Opt->state  &State_Selected;
    const bool verticalTabs = v3Opt->shape == QTabBar::RoundedWest;
    const QString text = v3Opt->text;

    QTransform m;
    if (verticalTabs) {
        m = QTransform::fromTranslate(rect.left(), rect.bottom());
        m.rotate(-90);
    } else {
        m = QTransform::fromTranslate(rect.left(), rect.top());
    }

    const QRect draw_rect(QPoint(0, 0), m.mapRect(rect).size());

    if (!selected && GtkStyle::isActive()) {
        p->fillRect(option->rect, option->palette.background());
    }

    p->save();
    p->setTransform(m);

    QRect iconRect(QPoint(8, 0), v3Opt->iconSize);
    QRect textRect(iconRect.topRight() + QPoint(4, 0), draw_rect.size());
    textRect.setRight(draw_rect.width());
    iconRect.translate(0, (draw_rect.height() - iconRect.height()) / 2);

    QStyleOptionViewItemV4 styleOpt;
    styleOpt.palette=option->palette;
    styleOpt.rect=draw_rect;
    if (QStyleOptionTab::Beginning==v3Opt->position) {
        styleOpt.rect.adjust(0, 0, -1, 0);
    }
    styleOpt.state=option->state;
    styleOpt.state&=~(QStyle::State_Selected|QStyle::State_MouseOver);
    styleOpt.state|=QStyle::State_Selected|QStyle::State_Enabled;
    styleOpt.viewItemPosition = QStyleOptionViewItemV4::OnlyOne;
    styleOpt.showDecorationSelected=true;
    bool drawBgnd=true;
    int fader = 1;

    if (!selected && drawBgnd) {
        const QString faderKey = "tab_" + text + "_fader";
        const QString animationKey = "tab_" + text + "_animation";

        const QString tab_hover = widget->property("tab_hover").toString();
        fader=widget->property(faderKey.toUtf8().constData()).toInt();
        QPropertyAnimation *animation = widget->property(animationKey.toUtf8().constData()).value<QPropertyAnimation*>();

        if (!animation) {
            QWidget* mut_widget = const_cast<QWidget*>(widget);
            fader = 0;
            mut_widget->setProperty(faderKey.toUtf8().constData(), fader);
            animation = new QPropertyAnimation(mut_widget, faderKey.toUtf8(), mut_widget);
            connect(animation, SIGNAL(valueChanged(QVariant)), mut_widget, SLOT(update()));
            mut_widget->setProperty(animationKey.toUtf8().constData(), QVariant::fromValue(animation));
        }

        if (text == tab_hover) {
            if (animation->state() != QAbstractAnimation::Running && fader != 40) {
                animation->stop();
                animation->setDuration(80);
                animation->setEndValue(50);
                animation->start();
            }
        } else {
            if (animation->state() != QAbstractAnimation::Running && fader != 0) {
                animation->stop();
                animation->setDuration(160);
                animation->setEndValue(0);
                animation->start();
            }
        }

        if (fader<1) {
            drawBgnd=false;
        } else {
            QColor col(styleOpt.palette.highlight().color());
            col.setAlpha(fader);
            styleOpt.palette.setColor(styleOpt.palette.currentColorGroup(), QPalette::Highlight, col);
        }
    }

    if (drawBgnd) {
        if (!selected && GtkStyle::isActive()) {
            GtkStyle::drawSelection(styleOpt, p, (fader*1.0)/150.0);
        } else {
            #ifdef Q_OS_MAC
            OSXStyle::self()->drawSelection(styleOpt, p, selected ? 1.0 : (fader*1.0)/150.0);
            #else
            #ifdef Q_OS_WIN
            if (QPalette::Active!=styleOpt.palette.currentColorGroup()) {
                styleOpt.palette.setColor(QPalette::Highlight, styleOpt.palette.color(QPalette::Window).darker(110));
            }
            #endif
            QApplication::style()->drawPrimitive(QStyle::PE_PanelItemViewItem, &styleOpt, p, 0);
            #endif
        }
    }

    int textFlags = Qt::AlignTop | Qt::AlignVCenter;
    #ifdef Q_OS_MAC
    p->setPen(selected && option->state&State_Active
              ? OSXStyle::self()->viewPalette().highlightedText().color() : OSXStyle::self()->viewPalette().foreground().color());
    #else
    p->setPen(selected && option->state&State_Active
              ? QApplication::palette().highlightedText().color() : QApplication::palette().foreground().color());
    #endif

    drawIcon(v3Opt->icon, iconRect, p, v3Opt->iconSize,
             selected && option->state&State_Active);

    QString txt=text;
    txt.replace("&", "");
    txt=p->fontMetrics().elidedText(txt, elideMode(), textRect.width());
    p->drawText(textRect.translated(0, -1), textFlags, txt);
    p->restore();
}