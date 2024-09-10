bool bucket_del(struct client *cli, const char *user, const char *bucket)
{
	char *hdr, timestr[64];
	enum errcode err = InternalError;
	int rc;
	struct db_bucket_ent ent;
	DB_ENV *dbenv = tdbrep.tdb.env;
	DB_TXN *txn = NULL;
	DB *buckets = tdbrep.tdb.buckets;
	DB *acls = tdbrep.tdb.acls;
	DB *objs = tdbrep.tdb.objs;
	DBC *cur = NULL;
	DBT key, val;
	char structbuf[sizeof(struct db_acl_key) + 32];
	struct db_acl_key *acl_key = (struct db_acl_key *) &structbuf;
	struct db_obj_key *obj_key = (struct db_obj_key *) &structbuf;

	if (!user)
		return cli_err(cli, AccessDenied);

	/* open transaction */
	rc = dbenv->txn_begin(dbenv, NULL, &txn, 0);
	if (rc) {
		dbenv->err(dbenv, rc, "DB_ENV->txn_begin");
		goto err_none;
	}

	/* search for (bucket, *) in object database, to see if
	 * any objects associated with this bucket exist
	 */
	rc = objs->cursor(objs, txn, &cur, 0);
	if (rc) {
		objs->err(objs, rc, "objs->cursor");
		goto err_out;
	}

	memset(&structbuf, 0, sizeof(structbuf));
	strncpy(obj_key->bucket, bucket, sizeof(obj_key->bucket));
	obj_key->key[0] = 0;

	memset(&key, 0, sizeof(key));
	memset(&val, 0, sizeof(val));

	key.data = obj_key;
	key.size = sizeof(*obj_key) + strlen(obj_key->key) + 1;

	val.flags = DB_DBT_MALLOC;

	rc = cur->get(cur, &key, &val, DB_SET_RANGE);

	if (rc == 0) {
		struct db_obj_key *newkey = key.data;

		if (!strcmp(newkey->bucket, bucket)) {
			free(newkey);
			cur->close(cur);
			err = BucketNotEmpty;
			goto err_out;
		}

		free(newkey);
	} else if (rc != DB_NOTFOUND)
		objs->err(objs, rc, "bucket_del empty check");

	rc = cur->close(cur);
	if (rc) {
		objs->err(objs, rc, "objs->cursor_close");
		goto err_out;
	}

	memset(&key, 0, sizeof(key));
	key.data = (char *) bucket;
	key.size = strlen(bucket) + 1;

	memset(&val, 0, sizeof(val));
	val.data = &ent;
	val.ulen = sizeof(struct db_bucket_ent);
	val.flags = DB_DBT_USERMEM;

	/* verify the bucket exists */
	rc = buckets->get(buckets, txn, &key, &val, 0);
	if (rc) {
		if (rc == DB_NOTFOUND)
			err = NoSuchBucket;
		else
			buckets->err(buckets, rc, "buckets->get");
		goto err_out;
	}

	/* verify that it is the owner who wishes to delete bucket */
	if (strncmp(user, ent.owner, sizeof(ent.owner))) {
		err = AccessDenied;
		goto err_out;
	}

	/* delete bucket */
	rc = buckets->del(buckets, txn, &key, 0);
	if (rc) {
		buckets->err(buckets, rc, "bucket del");
		goto err_out;
	}

	/* delete bucket ACLs */
	memset(&structbuf, 0, sizeof(structbuf));
	strncpy(acl_key->bucket, bucket, sizeof(acl_key->bucket));
	acl_key->key[0] = 0;

	memset(&key, 0, sizeof(key));
	key.data = acl_key;
	key.size = sizeof(*acl_key) + strlen(acl_key->key) + 1;

	rc = acls->del(acls, txn, &key, 0);
	if (rc && rc != DB_NOTFOUND) {
		acls->err(acls, rc, "acl del");
		goto err_out;
	}

	/* commit */
	rc = txn->commit(txn, 0);
	if (rc) {
		dbenv->err(dbenv, rc, "DB_ENV->txn_commit");
		return cli_err(cli, InternalError);
	}

	if (asprintf(&hdr,
"HTTP/%d.%d 204 x\r\n"
"Content-Length: 0\r\n"
"Date: %s\r\n"
"Server: " PACKAGE_STRING "\r\n"
"\r\n",
		     cli->req.major,
		     cli->req.minor,
		     hutil_time2str(timestr, sizeof(timestr), time(NULL))) < 0)
		return cli_err(cli, InternalError);

	rc = atcp_writeq(&cli->wst, hdr, strlen(hdr), atcp_cb_free, hdr);
	if (rc) {
		free(hdr);
		return true;
	}

	return atcp_write_start(&cli->wst);

err_out:
	rc = txn->abort(txn);
	if (rc)
		dbenv->err(dbenv, rc, "DB_ENV->txn_abort");
err_none:
	return cli_err(cli, err);
}