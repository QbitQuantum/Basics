void ProjectDatabaseRecord::updatePathData(ProjectDatabase database,
                                           const openstudio::path& originalBase,
                                           const openstudio::path& newBase)
{
  bool didStartTransaction = database.startTransaction();

  ProjectDatabaseRecord record = getProjectDatabaseRecord(database);
  record.getImpl<detail::ProjectDatabaseRecord_Impl>()->updatePathData(originalBase,newBase);

  if (didStartTransaction) {
    bool test = database.commitTransaction();
    OS_ASSERT(test);
  }
}