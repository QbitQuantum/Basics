        virtual bool run(const string& dbname, BSONObj& cmdObj, int x, string& errmsg, BSONObjBuilder& result, bool y) {
            static DBDirectClient db;

            if ( cmdObj["sort"].eoo() )
                return runNoDirectClient( dbname , cmdObj , x, errmsg , result, y );

            string ns = dbname + '.' + cmdObj.firstElement().valuestr();

            BSONObj origQuery = cmdObj.getObjectField("query"); // defaults to {}
            Query q (origQuery);
            BSONElement sort = cmdObj["sort"];
            if (!sort.eoo())
                q.sort(sort.embeddedObjectUserCheck());

            bool upsert = cmdObj["upsert"].trueValue();

            BSONObj fieldsHolder (cmdObj.getObjectField("fields"));
            const BSONObj* fields = (fieldsHolder.isEmpty() ? NULL : &fieldsHolder);

            Projection projection;
            if (fields) {
                projection.init(fieldsHolder);
                if (!projection.includeID())
                    fields = NULL; // do projection in post-processing
            }

            BSONObj out = db.findOne(ns, q, fields);
            if (out.isEmpty()) {
                if (!upsert) {
                    result.appendNull("value");
                    return true;
                }

                BSONElement update = cmdObj["update"];
                uassert(13329, "upsert mode requires update field", !update.eoo());
                uassert(13330, "upsert mode requires query field", !origQuery.isEmpty());
                db.update(ns, origQuery, update.embeddedObjectUserCheck(), true);

                BSONObj gle = db.getLastErrorDetailed(dbname);
                result.append("lastErrorObject", gle);
                if (gle["err"].type() == String) {
                    errmsg = gle["err"].String();
                    return false;
                }

                if (cmdObj["new"].trueValue()) {
                    BSONElement _id = gle["upserted"];
                    if (_id.eoo())
                        _id = origQuery["_id"];

                    out = db.findOne(ns, QUERY("_id" << _id), fields);
                }

            }
            else {

                if (cmdObj["remove"].trueValue()) {
                    uassert(12515, "can't remove and update", cmdObj["update"].eoo());
                    db.remove(ns, QUERY("_id" << out["_id"]), 1);

                    BSONObj gle = db.getLastErrorDetailed(dbname);
                    result.append("lastErrorObject", gle);
                    if (gle["err"].type() == String) {
                        errmsg = gle["err"].String();
                        return false;
                    }

                }
                else {   // update

                    BSONElement queryId = origQuery["_id"];
                    if (queryId.eoo() || getGtLtOp(queryId) != BSONObj::Equality) {
                        // need to include original query for $ positional operator

                        BSONObjBuilder b;
                        b.append(out["_id"]);
                        BSONObjIterator it(origQuery);
                        while (it.more()) {
                            BSONElement e = it.next();
                            if (strcmp(e.fieldName(), "_id"))
                                b.append(e);
                        }
                        q = Query(b.obj());
                    }

                    if (q.isComplex()) // update doesn't work with complex queries
                        q = Query(q.getFilter().getOwned());

                    BSONElement update = cmdObj["update"];
                    uassert(12516, "must specify remove or update", !update.eoo());
                    db.update(ns, q, update.embeddedObjectUserCheck());

                    BSONObj gle = db.getLastErrorDetailed(dbname);
                    result.append("lastErrorObject", gle);
                    if (gle["err"].type() == String) {
                        errmsg = gle["err"].String();
                        return false;
                    }

                    if (cmdObj["new"].trueValue())
                        out = db.findOne(ns, QUERY("_id" << out["_id"]), fields);
                }
            }

            if (!fieldsHolder.isEmpty() && !fields){
                // we need to run projection but haven't yet
                out = projection.transform(out);
            }

            result.append("value", out);

            return true;
        }