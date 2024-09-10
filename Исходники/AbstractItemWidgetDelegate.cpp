    bool _isShowing( const QWidget * widget__ ,const QRect  & rRect_ ) {
        const auto * widget_ = qobject_cast<const AbstractItemWidget *>(widget__);
        if (0 == widget_) { return false; }

        /*
            增加边界
            为"setPos"之类的动画服务
            此类动画幅度不要超过5
            否则可能出现逻辑错误
        */
        const auto && gValue_ = widget_->mapToGlobal(QPoint(-5, -5));
        const auto && size_ = widget_->size() + QSize(10, 10);

        return rRect_.intersects( QRect(gValue_,size_) );

    }