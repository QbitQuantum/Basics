THREAD_SIGNATURE TestCustom59::threadTestCustom59(void * pC)
{
	testCustom59_s * const lC = (testCustom59_s *)pC;
	ISession * const lSession = MVTApp::startSession(lC->mTest.mStoreCtx);
	lC->mThreadId = (long int)getThreadId();
	bool lFreeRun = false;
	long lFreeStep;
	long volatile * lStepPtr = &lC->mTest.mStep;
	while (*lStepPtr < lC->mNumSteps)
	{
		RC lRC = RC_OK;
		Value lV[2];
		SETVALUE(lV[0], lC->mTest.mPropIds[0], "pomme poire banane", OP_SET);
		SETVALUE_C(lV[1], lC->mTest.mPropIds[1], (int)lC->mThreadId, OP_ADD, STORE_LAST_ELEMENT);
		lV[0].meta = lV[1].meta = META_PROP_FTINDEX;
		long const lStepIndex = *lStepPtr;
		TestCustom59::eSteps const lStep = lC->mSteps[lStepIndex];
		if (TestCustom59::kSLastSynchroStep < lStep)
		{
			lC->mTest.mOutputLock.lock();
			lC->mTest.logLineHeader(lC->mThreadIndex);
			lC->mTest.getLogger().out() << "step #" << std::dec << lStepIndex << ":";
			lC->mTest.getLogger().out() << lC->mTest.stepName(lStep);
			lC->mTest.getLogger().out() << std::endl;
			lC->mTest.mOutputLock.unlock();
		}
		switch (lStep)
		{
			case TestCustom59::kSWaiting: if (!lFreeRun) lC->mTest.nextStep(lStepIndex); break;
			case TestCustom59::kSSleepAndGo:
			{
				MVTestsPortability::threadSleep(1000);
				if (!lFreeRun)
				{
					lFreeStep = lC->mTest.detachStepping(lC->mDetachedStepping);
					lStepPtr = &lFreeStep;
					lFreeRun = true;
				}
				lFreeStep++;
				break;
			}
			case TestCustom59::kSSleep: MVTestsPortability::threadSleep(1000); lC->mTest.nextStep(lFreeRun, lFreeStep); break;
			case TestCustom59::kSStartTx: lSession->startTransaction(); lC->mTest.nextStep(lFreeRun, lFreeStep); break;
			case TestCustom59::kSCommitTx: lRC = lSession->commit(); lC->mTest.nextStep(lFreeRun, lFreeStep); break;
			case TestCustom59::kSRead1: if (NULL == lSession->getPIN(lC->mTest.mPID1)) lC->mDeadlocked = true; lC->mTest.nextStep(lFreeRun, lFreeStep); break;
			case TestCustom59::kSRead2: if (NULL == lSession->getPIN(lC->mTest.mPID2)) lC->mDeadlocked = true; lC->mTest.nextStep(lFreeRun, lFreeStep); break;
			case TestCustom59::kSRead3: if (NULL == lSession->getPIN(lC->mTest.mPID3)) lC->mDeadlocked = true; lC->mTest.nextStep(lFreeRun, lFreeStep); break;
			case TestCustom59::kSWrite1: lRC = lSession->modifyPIN(lC->mTest.mPID1, lV, 2); lC->mTest.nextStep(lFreeRun, lFreeStep); break;
			case TestCustom59::kSWrite2: lRC = lSession->modifyPIN(lC->mTest.mPID2, lV, 2); lC->mTest.nextStep(lFreeRun, lFreeStep); break;
			case TestCustom59::kSWrite3: lRC = lSession->modifyPIN(lC->mTest.mPID3, lV, 2); lC->mTest.nextStep(lFreeRun, lFreeStep); break;
			case TestCustom59::kSQuickCheckFTIndexingIsolation:
			{
				IStmt * lQWord = lSession->createStmt();
				unsigned char lVar = lQWord->addVariable();
				lQWord->setConditionFT(lVar, "poire");
				ICursor * lRWord = NULL;
				lQWord->execute(&lRWord);
				if (lRWord)
				{
					IPIN * lNext;
					while (NULL != (lNext = lRWord->next()))
					{
						if (lC->mTest.mPID1 == lNext->getPID() || lC->mTest.mPID2 == lNext->getPID() || lC->mTest.mPID3 == lNext->getPID())
						{
							lC->mTest.mOutputLock.lock();
							lC->mTest.logLineHeader(lC->mThreadIndex);
							lC->mTest.getLogger().out() << "WARNING: FT found pin " << std::hex << lNext->getPID().pid << std::endl;
							lC->mTest.mOutputLock.unlock();
						}	
						lNext->destroy();
					}
					lRWord->destroy();
				}
				else
				{
					lC->mTest.logLineHeader(lC->mThreadIndex);
					lC->mTest.getLogger().out() << "WARNING: Couldn't obtain a query result!?" << std::endl;
				}
				lQWord->destroy();
				lC->mTest.nextStep(lFreeRun, lFreeStep);
				break;
			}
			default: assert(false); break;
		}

		if (RC_DEADLOCK == lRC)
			lC->mDeadlocked = true;
		else if (RC_OK != lRC)
		{
			lC->mTest.mOutputLock.lock();
			lC->mTest.logLineHeader(lC->mThreadIndex);
			lC->mTest.getLogger().out() << "Failure " << std::dec << lRC << std::endl;
			lC->mTest.mOutputLock.unlock();
		}

		if (lC->mDeadlocked)
		{
			lSession->rollback(); // Review: This will not be needed later on.

			lC->mTest.mOutputLock.lock();
			lC->mTest.logLineHeader(lC->mThreadIndex);
			lC->mTest.getLogger().out() << "DEADLOCKED" << std::endl;
			lC->mTest.mOutputLock.unlock();

			lC->mTest.detachStepping(lC->mDetachedStepping);
			lFreeStep = lC->mNumSteps;
			lStepPtr = &lFreeStep;
			lFreeRun = true;
		}
	}
	lC->mTest.detachStepping(lC->mDetachedStepping);
	lC->mTest.mOutputLock.lock();
	lC->mTest.logLineHeader(lC->mThreadIndex);
	lC->mTest.getLogger().out() << "done" << std::endl;
	lC->mTest.mOutputLock.unlock();
	lSession->terminate();
	return 0;
}