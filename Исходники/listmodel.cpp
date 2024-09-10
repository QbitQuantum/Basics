ListModel::ListModel(RubyValue rubyModel, QObject *parent) :
    QAbstractListModel(parent),
    mRubyModel(rubyModel)
{
    auto columns = rubyModel.send("columns").to<QList<QByteArray>>();
    for (int i = 0; i < columns.size(); ++i) {
        auto role = Qt::UserRole + i;
        mColumnNames[role] = columns[i];
        mColumnIDs[role] = rb_intern(columns[i]);
    }
    rubyModel.send("qt_models").send("push", RubyValue::fromQObject(this, false));
}