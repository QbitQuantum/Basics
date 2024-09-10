void ::ARFCNManager::receiveBurst(const RxBurst& inBurst)
{
	LOG(DEBUG) << "receiveBurst: " << inBurst;
	uint32_t FN = inBurst.time().FN() % maxModulus;
	unsigned TN = inBurst.time().TN();

	mTableLock.lock();
	L1Decoder *proc = mDemuxTable[TN][FN];
	if (proc==NULL) {
		LOG(DEBUG) << "ARFNManager::receiveBurst in unconfigured TDMA position TN: " << TN << " FN: " << FN << ".";
		mTableLock.unlock();
		return;
	}
	proc->writeLowSide(inBurst);
	mTableLock.unlock();
}