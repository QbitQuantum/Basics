void directory_model::make_directory(QString local_name)
{
    string dirname = local_name.toStdString();

    _sys->mkdir(_path / dirname);  // TODO: ak sa mkdir nepodari, nevkladaj

    file_info item{dirname, true};
    auto insert_it = lower_bound(_files.begin(), _files.end(), item, file_compare);
    int row = distance(_files.begin(), insert_it);

    beginInsertRows(QModelIndex{}, row, row);
    _files.insert(insert_it, item);
    endInsertRows();

    emit current_index_changed(index(row));
}