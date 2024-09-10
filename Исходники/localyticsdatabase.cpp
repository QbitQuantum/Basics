bool LocalyticsDatabase::deleteUploadedData()
{
    // Delete all headers and staged events.
    QString t(QLatin1String("delete_upload_data"));
    bool success = beginTransaction(t);

    QSqlQuery q(_databaseConnection);
    success &= q.exec(QLatin1String("DELETE FROM events WHERE upload_header IS NOT NULL"));
    success &= q.exec(QLatin1String("DELETE FROM upload_headers"));

    if (success) {
        releaseTransaction(t);
    } else {
        rollbackTransaction(t);
    }
    return success;
}