void AvatarJobManager::addJob(const Contact &contact)
{
	QMutexLocker(&mutex());

	if (!contact)
		return;

	Jobs.insert(contact);
	scheduleJob();
}