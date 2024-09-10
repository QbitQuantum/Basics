int Db::stat(void *sp, db_malloc_fcn_type db_malloc_fcn, u_int32_t flags)
{
	int err;
	DB *db = unwrap(this);

	if (!db) {
		DB_ERROR("Db::stat", EINVAL, error_policy());
		return (EINVAL);
	}
	if ((err = db->stat(db, sp, db_malloc_fcn, flags)) != 0) {
		DB_ERROR("Db::stat", err, error_policy());
		return (err);
	}
	return (0);
}