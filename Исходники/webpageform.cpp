//お気に入りを更新
void WebPageForm::Private::updateFavorite(const QString &url, const QString &title, bool add)
{
    bool exist = false;
    bool update = false;

    settings.beginGroup(QStringLiteral(FAV_USER));

    QHash<QString, QVariant> list = settings.value(QStringLiteral(FAV_USER_BOOKMARK)).toHash();
    foreach (const QString &key, list.keys()) {
        if(url == key){
            //見つかった
            exist = true;
            if(add){
                //追加（ただしすでにある）
            }else{
                //削除
                list.remove(url);
                update = true;
            }
            break;
        }
    }
    if(!exist){
        list.insert(url, title);
        update = true;
    }
    if(update)
        settings.setValue(QStringLiteral(FAV_USER_BOOKMARK), list);

    settings.endGroup();
    settings.sync();

    if(update)
        emit q->updateFavorite();
}