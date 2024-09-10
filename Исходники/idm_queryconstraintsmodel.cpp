QVariant QueryConstraintsModel::data(BaseConstraint *item, int column, int role) const
{
    switch (column)
    {
    case 0:
    {
        if (role == Qt::DisplayRole)
            if (item->isGroup())
                switch (static_cast<GroupConstraint *>(item)->type())
                {
                case LiquidDb::GroupConstraint::And:
                    return m_andTypeLabel;

                case LiquidDb::GroupConstraint::Or:
                    return m_orTypeLabel;
                }
            else
                return QString::fromLatin1("%1 %2 \"%3\"").
                       arg(toUnicode(static_cast<ValueConstraint *>(item)->property().name)).
                       arg(toUnicode(Constraint::operatorToString(static_cast<ValueConstraint*>(item)->op()))).
                       arg(toUnicode(static_cast<ValueConstraint *>(item)->value().value().asString()));

        break;
    }

    case 1:
    {
        if (item->isGroup())
            switch (role)
            {
            case Qt::DisplayRole:
                return toUnicode(LiquidDb::GroupConstraint::operatorToString(static_cast<GroupConstraint *>(item)->type()));

            case Qt::TextAlignmentRole:
                return Qt::AlignCenter;
            }

        break;
    }

    default:
        break;
    }

    return QVariant();
}