void SetQuotaJob::setQuota(const QByteArray &resource, qint64 limit)
{
  Q_D( SetQuotaJob );

  d->setList[resource.toUpper()] = limit;
}