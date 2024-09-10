AutoPtr<IInterface> ActivityChooserModel::PersistHistoryAsyncTask::DoInBackground(
    /* [in] */ ArrayOf<IInterface*>* args)
{
    AutoPtr<IObjectContainer> historicalRecords = IObjectContainer::Probe((*args)[0]);
    assert(historicalRecords != NULL);
    String historyFileName;
    AutoPtr<ICharSequence> csq = ICharSequence::Probe((*args)[1]);
    csq->ToString(&historyFileName);
    AutoPtr<IFileOutputStream> fos;
    AutoPtr<IObjectEnumerator> em;
    Boolean hasNext;
    AutoPtr<IBoolean> param;

    // try {
    ECode ec = mHost->mContext->OpenFileOutput(historyFileName, IContext::MODE_PRIVATE, (IFileOutputStream**)&fos);
    if(FAILED(ec))
    {
        return NULL;
    }
    // } catch (FileNotFoundException fnfe) {
        // Log.e(LOG_TAG, "Error writing historical recrod file: " + hostoryFileName, fnfe);
        // return null;
    // }

    assert("TODO" && 0);
    AutoPtr<IXmlSerializer> serializer;// = Xml::NewSerializer();

    // try {
        if (FAILED(serializer->SetOutput(fos, String(NULL)))) {
            goto finally;
        }
        CBoolean::New(TRUE, (IBoolean**)&param);
        if (FAILED(serializer->StartDocument(String("UTF-8"), param))) {
            goto finally;
        }
        if (FAILED(serializer->WriteStartTag(String(NULL), TAG_HISTORICAL_RECORDS))) {
            goto finally;
        }

        historicalRecords->GetObjectEnumerator((IObjectEnumerator**)&em);
        while (em->MoveNext(&hasNext), hasNext) {
            AutoPtr<IInterface> cur;
            em->Current((IInterface**)&cur);
            AutoPtr<IHistoricalRecord> recordTmp = IHistoricalRecord::Probe(cur);
            AutoPtr<HistoricalRecord> record = (HistoricalRecord*)recordTmp.Get();
            historicalRecords->Remove(cur);
            if (FAILED(serializer->WriteStartTag(String(NULL), TAG_HISTORICAL_RECORD))) {
                goto finally;
            }
            String str;
            record->mActivity->FlattenToString(&str);
            if (FAILED(serializer->WriteAttribute(String(NULL), ATTRIBUTE_ACTIVITY, str))) {
                goto finally;
            }
            String time, weight;
            time = StringUtils::Int64ToString(record->mTime);
            weight = StringUtils::FloatToString(record->mWeight);
            if (FAILED(serializer->WriteAttribute(String(NULL), ATTRIBUTE_TIME, time))) {
                goto finally;
            }
            if (FAILED(serializer->WriteAttribute(String(NULL), ATTRIBUTE_WEIGHT, weight))) {
                goto finally;
            }
            if (FAILED(serializer->WriteEndTag(String(NULL), TAG_HISTORICAL_RECORD))) {
                goto finally;
            }
            // if (DEBUG) {
            //     Log.i(LOG_TAG, "Wrote " + record.toString());
            // }
        }

        if (FAILED(serializer->WriteEndTag(String(NULL), TAG_HISTORICAL_RECORDS))) {
            goto finally;
        }
        if (FAILED(serializer->EndDocument())) {
            goto finally;
        }

    //     if (DEBUG) {
    //         Log.i(LOG_TAG, "Wrote " + recordCount + " historical records.");
    //     }
    // } catch (IllegalArgumentException iae) {
    //     Log.e(LOG_TAG, "Error writing historical recrod file: " + mHistoryFileName, iae);
    // } catch (IllegalStateException ise) {
    //     Log.e(LOG_TAG, "Error writing historical recrod file: " + mHistoryFileName, ise);
    // } catch (IOException ioe) {
    //     Log.e(LOG_TAG, "Error writing historical recrod file: " + mHistoryFileName, ioe);
    // } finally {
    finally:
        mHost->mCanReadHistoricalData = TRUE;
        if (fos != NULL) {
            // try {
                fos->Close();
            // } catch (IOException e) {
                /* ignore */
            // }
        }
    // }
    return NULL;
}