//##############################################################################
//##############################################################################
BerkeleyDBCXXDb::BerkeleyDBCXXDb(const std::string &name,
        boost::shared_ptr<BerkeleyDB> backend,
        const boost::shared_ptr<db::ConfigIface> db_config, boost::shared_ptr<BerkeleyDBCXXEnv> env)
    : name_(name), backend_(backend), env_(env), db_config_(db_config), log(BerkeleyDBCXXDbLogModule)
{
    RANGE_LOG_FUNCTION();
    inst_ = boost::make_shared<Db>(env_->getEnv(), 0);

    int rval = 0;
    DbTxn * txn;
    try { 
        rval = env_->getEnv()->txn_begin(NULL, &txn, DB_TXN_SYNC | DB_TXN_WAIT | DB_TXN_SNAPSHOT);
    }
    catch(DbException &e) {
        THROW_STACK(UnknownTransactionException(e.what()));
    }
    try { 
        inst_->open(txn, name.c_str(), name.c_str(), DB_HASH,
                DB_CREATE | DB_MULTIVERSION | DB_THREAD, 0);
    }
    catch(DbException &e) {
        txn->abort();
        THROW_STACK(DatabaseEnvironmentException(e.what()));
    }
    catch(std::exception &e) {
        txn->abort();
        THROW_STACK(DatabaseEnvironmentException(e.what()));
    }
    switch(rval) {
        case 0:
            break;
        case ENOMEM:
            THROW_STACK(DatabaseEnvironmentException("The maximum number of concurrent transactions has been reached."));
    }
    txn->commit(0);
}