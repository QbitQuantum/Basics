/*
 * _Index_init: initialize a new Index object.
 *
 * callspec: Index.__init__(env, name)
 * parameters:
 *  env (Env): A Env object to use as the environment
 *  name (string): The name of the Index
 * returns: 0 if initialization succeeded, otherwise -1
 * exceptions:
 *  terane.outputs.store.backend.Error: failed to create/open the Index
 */
static int
_Index_init (terane_Index *self, PyObject *args, PyObject *kwds)
{
    char *tocname = NULL;
    DB_TXN *txn = NULL;
    DB_BTREE_STAT *stats = NULL;
    int dbret;
    
    /* __init__ has already been called, don't repeat initialization */
    if (self->env != NULL)
        return 0;
    /* parse constructor parameters */
    if (!PyArg_ParseTuple (args, "O!O!", 
        &terane_EnvType, &self->env, &PyString_Type, &self->name))
        goto error;
    Py_INCREF (self->env);
    Py_INCREF (self->name);

    /* allocate a buffer with the full index toc name */
    tocname = PyMem_Malloc (PyString_Size (self->name) + 5);
    if (tocname == NULL) {
        PyErr_NoMemory ();
        goto error;
    }
    sprintf (tocname, "%s.toc", PyString_AsString (self->name));

    /* wrap db creation in a transaction */
    dbret = self->env->env->txn_begin (self->env->env, NULL, &txn, 0);
    if (dbret != 0) {
        PyErr_Format (terane_Exc_Error, "Failed to create DB_TXN handle: %s",
            db_strerror (dbret));
        goto error;
    }

    /* create the DB handle for the metadata store */
    dbret = db_create (&self->metadata, self->env->env, 0);
    if (dbret != 0) {
        PyErr_Format (terane_Exc_Error, "Failed to create handle for metadata: %s",
            db_strerror (dbret));
        goto error;
    }
    /* set compare function */
    self->metadata->set_bt_compare (self->metadata, _terane_msgpack_DB_compare);
    /* open the metadata store */
    dbret = self->metadata->open (self->metadata, txn, tocname, "metadata",
        DB_BTREE, DB_CREATE | DB_THREAD | DB_MULTIVERSION, 0);
    if (dbret != 0) {
        PyErr_Format (terane_Exc_Error, "Failed to open metadata: %s",
            db_strerror (dbret));
        goto error;
    }

    /* create the DB handle for the schema store */
    dbret = db_create (&self->schema, self->env->env, 0);
    if (dbret != 0) {
        PyErr_Format (terane_Exc_Error, "Failed to create handle for schema: %s",
            db_strerror (dbret));
        goto error;
    }
    /* set compare function */
    self->schema->set_bt_compare (self->schema, _terane_msgpack_DB_compare);
    /* open the schema store */
    dbret = self->schema->open (self->schema, txn, tocname, "schema",
        DB_BTREE, DB_CREATE | DB_THREAD | DB_MULTIVERSION, 0);
    if (dbret != 0) {
        PyErr_Format (terane_Exc_Error, "Failed to open schema: %s",
            db_strerror (dbret));
        goto error;
    }
    /* get an initial count of fields */
    dbret = self->schema->stat (self->schema, txn, &stats, 0);
    if (dbret != 0) {
        if (stats)
            PyMem_Free (stats);
        PyErr_Format (terane_Exc_Error, "Failed to get field count: %s",
            db_strerror (dbret));
        goto error;
    }
    self->nfields = (unsigned long) stats->bt_nkeys;
    if (stats)
        PyMem_Free (stats);
    stats = NULL;

    /* create the DB handle for the segments store */
    dbret = db_create (&self->segments, self->env->env, 0);
    if (dbret != 0) {
        PyErr_Format (terane_Exc_Error, "Failed to create handle for segments: %s",
            db_strerror (dbret));
        goto error;
    }
    /* open the segments store */
    dbret = self->segments->open (self->segments, txn, tocname, "segments",
        DB_BTREE, DB_CREATE | DB_THREAD | DB_MULTIVERSION, 0);
    if (dbret != 0) {
        PyErr_Format (terane_Exc_Error, "Failed to open segments: %s",
            db_strerror (dbret));
        goto error;
    }

    /* commit new databases */
    dbret = txn->commit (txn, 0);
    if (dbret != 0) {
        PyErr_Format (terane_Exc_Error, "Failed to commit transaction: %s",
            db_strerror (dbret));
        goto error;
    }

    PyMem_Free (tocname);

    return 0;

/* if there is an error, then free any locally allocated memory and references */
error:
    if (txn != NULL)
        txn->abort (txn);
    if (tocname != NULL)
        PyMem_Free (tocname);
    if (self)
        _Index_dealloc ((terane_Index *) self);
    return -1;
}