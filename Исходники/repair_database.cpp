    Status MMAPV1Engine::repairDatabase( OperationContext* txn,
                                         const std::string& dbName,
                                         bool preserveClonedFilesOnFailure,
                                         bool backupOriginalFiles ) {
        unique_ptr<RepairFileDeleter> repairFileDeleter;

        // Must be done before and after repair
        getDur().syncDataAndTruncateJournal(txn);

        intmax_t totalSize = dbSize( dbName );
        intmax_t freeSize = File::freeSpace(storageGlobalParams.repairpath);

        if ( freeSize > -1 && freeSize < totalSize ) {
            return Status( ErrorCodes::OutOfDiskSpace,
                           str::stream() << "Cannot repair database " << dbName
                           << " having size: " << totalSize
                           << " (bytes) because free disk space is: " << freeSize << " (bytes)" );
        }

        txn->checkForInterrupt();

        Path reservedPath =
            uniqueReservedPath( ( preserveClonedFilesOnFailure || backupOriginalFiles ) ?
                                "backup" : "_tmp" );
        bool created = false;
        MONGO_ASSERT_ON_EXCEPTION( created = boost::filesystem::create_directory( reservedPath ) );
        invariant( created );
        string reservedPathString = reservedPath.string();

        if ( !preserveClonedFilesOnFailure )
            repairFileDeleter.reset( new RepairFileDeleter( txn,
                                                            dbName,
                                                            reservedPathString,
                                                            reservedPath ) );

        {
            Database* originalDatabase = dbHolder().openDb(txn, dbName);
            if (originalDatabase == NULL) {
                return Status(ErrorCodes::NamespaceNotFound, "database does not exist to repair");
            }

            unique_ptr<MMAPV1DatabaseCatalogEntry> dbEntry;
            unique_ptr<Database> tempDatabase;

            // Must call this before MMAPV1DatabaseCatalogEntry's destructor closes the DB files
            ON_BLOCK_EXIT(&dur::DurableInterface::syncDataAndTruncateJournal, &getDur(), txn);

            {
                dbEntry.reset(new MMAPV1DatabaseCatalogEntry(txn,
                                                             dbName,
                                                             reservedPathString,
                                                             storageGlobalParams.directoryperdb,
                                                             true));
                tempDatabase.reset( new Database(txn, dbName, dbEntry.get()));
            }

            map<string,CollectionOptions> namespacesToCopy;
            {
                string ns = dbName + ".system.namespaces";
                OldClientContext ctx(txn,  ns );
                Collection* coll = originalDatabase->getCollection( ns );
                if ( coll ) {
                    auto cursor = coll->getCursor(txn);
                    while (auto record = cursor->next()) {
                        BSONObj obj = record->data.releaseToBson();

                        string ns = obj["name"].String();

                        NamespaceString nss( ns );
                        if ( nss.isSystem() ) {
                            if ( nss.isSystemDotIndexes() )
                                continue;
                            if ( nss.coll() == "system.namespaces" )
                                continue;
                        }

                        if ( !nss.isNormal() )
                            continue;

                        CollectionOptions options;
                        if ( obj["options"].isABSONObj() ) {
                            Status status = options.parse( obj["options"].Obj() );
                            if ( !status.isOK() )
                                return status;
                        }
                        namespacesToCopy[ns] = options;
                    }
                }
            }

            for ( map<string,CollectionOptions>::const_iterator i = namespacesToCopy.begin();
                  i != namespacesToCopy.end();
                  ++i ) {
                string ns = i->first;
                CollectionOptions options = i->second;

                Collection* tempCollection = NULL;
                {
                    WriteUnitOfWork wunit(txn);
                    tempCollection = tempDatabase->createCollection(txn, ns, options, false);
                    wunit.commit();
                }

                OldClientContext readContext(txn, ns, originalDatabase);
                Collection* originalCollection = originalDatabase->getCollection( ns );
                invariant( originalCollection );

                // data

                // TODO SERVER-14812 add a mode that drops duplicates rather than failing
                MultiIndexBlock indexer(txn, tempCollection );
                {
                    vector<BSONObj> indexes;
                    IndexCatalog::IndexIterator ii =
                        originalCollection->getIndexCatalog()->getIndexIterator( txn, false );
                    while ( ii.more() ) {
                        IndexDescriptor* desc = ii.next();
                        indexes.push_back( desc->infoObj() );
                    }

                    Status status = indexer.init( indexes );
                    if (!status.isOK()) {
                        return status;
                    }
                }

                auto cursor = originalCollection->getCursor(txn);
                while (auto record = cursor->next()) {
                    BSONObj doc = record->data.releaseToBson();

                    WriteUnitOfWork wunit(txn);
                    StatusWith<RecordId> result = tempCollection->insertDocument(txn,
                                                                                 doc,
                                                                                 &indexer,
                                                                                 false);
                    if ( !result.isOK() )
                        return result.getStatus();

                    wunit.commit();
                    txn->checkForInterrupt();
                }
                
                Status status = indexer.doneInserting();
                if (!status.isOK())
                    return status;

                {
                    WriteUnitOfWork wunit(txn);
                    indexer.commit();
                    wunit.commit();
                }

            }

            getDur().syncDataAndTruncateJournal(txn);

            // need both in case journaling is disabled
            MongoFile::flushAll(true);

            txn->checkForInterrupt();
        }

        // at this point if we abort, we don't want to delete new files
        // as they might be the only copies

        if ( repairFileDeleter.get() )
            repairFileDeleter->success();

        // Close the database so we can rename/delete the original data files
        dbHolder().close(txn, dbName);

        if ( backupOriginalFiles ) {
            _renameForBackup( dbName, reservedPath );
        }
        else {
            // first make new directory before deleting data
            Path newDir = Path(storageGlobalParams.dbpath) / dbName;
            MONGO_ASSERT_ON_EXCEPTION(boost::filesystem::create_directory(newDir));

            // this deletes old files
            _deleteDataFiles( dbName );

            if ( !boost::filesystem::exists(newDir) ) {
                // we deleted because of directoryperdb
                // re-create
                MONGO_ASSERT_ON_EXCEPTION(boost::filesystem::create_directory(newDir));
            }
        }

        _replaceWithRecovered( dbName, reservedPathString.c_str() );

        if (!backupOriginalFiles) {
            MONGO_ASSERT_ON_EXCEPTION(boost::filesystem::remove_all(reservedPath));
        }

        // Reopen the database so it's discoverable
        dbHolder().openDb(txn, dbName);

        return Status::OK();
    }