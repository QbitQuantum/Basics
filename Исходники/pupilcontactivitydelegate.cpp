void PupilContActivityDelegate::setModelData ( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
    switch ( index.column() ) {
    case 2: {
        QComboBox *combo = qobject_cast<QComboBox *> ( editor );
        if ( !combo ) {

            QItemDelegate::setModelData ( editor, model, index );
            return;
        }
        model -> setData ( index, combo -> currentIndex() );
    }
    break;
    case 3: {
        QComboBox *combo = qobject_cast<QComboBox *> ( editor );
        if ( !combo ) {

            QItemDelegate::setModelData ( editor, model, index );
            return;
        }
        model -> setData ( index, combo -> currentIndex() );
    }
    break;
    case 4: {
        QTimeEdit *time = qobject_cast<QTimeEdit *> ( editor );
        if ( !time ) {
            QItemDelegate::setModelData ( editor, model, index );
        }
        model -> setData ( index, time->time().toString("hh:mm") );
    }
    break;
    case 5: {
        QDateEdit *cal = qobject_cast<QDateEdit *> ( editor );
        if ( !cal ) {
            QItemDelegate::setModelData ( editor, model, index );
            return;
        }
        model -> setData ( index, cal->date().toString("yyyy-MM-dd") );
    }
    break;
    case 6: {
        QDateEdit *cal1 = qobject_cast<QDateEdit *> ( editor );
        if ( !cal1 ) {
            QItemDelegate::setModelData ( editor, model, index );
            return;
        }
        model -> setData ( index, cal1->date().toString("yyyy-MM-dd") );
    }

    break;
    default: {
        QItemDelegate::setModelData ( editor, model, index );
        return;

    }
    break;
    }
}