/**
 * Opens the database, and upgrades it if necessary.
 *
 * @param context the Context to use for opening the database
 * @param databaseFile Name of the file to be initialized.
 */
void HttpAuthDatabase::InitDatabase(
    /* [in] */ IContext* context,
    /* [in] */ String databaseFile)
{
    // try {
        context->OpenOrCreateDatabase(databaseFile, 0, NULL, (ISQLiteDatabase**)&mDatabase);
    // } catch (SQLiteException e) {
    //     // try again by deleting the old db and create a new one
    //     if (context.deleteDatabase(databaseFile)) {
    //         mDatabase = context.openOrCreateDatabase(databaseFile, 0, null);
    //     }
    // }

    if (mDatabase == NULL) {
        // Not much we can do to recover at this point
//        Log.e(LOGTAG, "Unable to open or create " + databaseFile);
        return;
    }

    Int32 version;
    mDatabase->GetVersion(&version);
    if (version != DATABASE_VERSION) {
        mDatabase->BeginTransactionNonExclusive();
        // try {
            CreateTable();
            mDatabase->SetTransactionSuccessful();
        // } finally {
        //     mDatabase.endTransaction();
        // }
    }
}