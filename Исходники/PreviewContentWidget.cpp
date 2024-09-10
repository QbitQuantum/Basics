    void PreviewContentWidget::renderTextBubble(QPainter &p)
    {
        const auto &bubblePath = getTextBubble();
        if (bubblePath.isEmpty())
        {
            return;
        }

        p.save();
        
        int theme_id = Ui::get_qt_theme_settings()->themeIdForContact(aimId_);
        
        QBrush b;
        p.fillPath(
            bubblePath,
            Ui::MessageStyle::getBodyBrush(isOutgoing(), isSelected(), theme_id)
        );

        p.restore();
    }