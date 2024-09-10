/**********************************************************
 *similar to writetodb in FileRec
 * 
***********************************************************/
void VersionRec::writeToDB(mongo::DBClientConnection& conn) {

    BSONObjBuilder record;

    if (this->versionid.empty()) { //if no id has been read in because it is a new version
        record.genOID();//create one
    } else {
        mongo::OID theoid(this->versionid); //use current id
        record.append("_id", theoid);
    }
    //convert to BSON
    record.append("Tempname", this->tmpname);
    record.append("filehash", this->filehash);
    record.append("length", this->length);
    record.append("Version", this->versionnumber);
    /* love you */ long long time = this->modifytime.tv_nsec;
    record.append("Mtnsec", time);
    time = this->modifytime.tv_sec;
    record.append("mtsec", time);

    mongo::BSONArrayBuilder Version;
    for (vector<VersionDiffBlock>::iterator it = changes.begin(); it != changes.end(); ++it) {
        BSONObjBuilder version;
        version.append("Blknum", (*it).blockNo);
        version.append("hash", (*it).blockHash);
        Version.append(version.obj());
    }
    record.append("Blktable", Version.arr());

    BSONObj result = record.obj();
    if (this->versionid.empty()) {
        mongo::BSONElement thing;
        result.getObjectID(thing);
        mongo::OID anoid = thing.OID();
        this->versionid = anoid.toString();
    }

    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.FileVersion", MONGO_QUERY("_id" << mongo::OID(this->versionid)));
    if (cursor->more()) {//already a version with same id, update
        conn.update("fileRecords.FileVersion", MONGO_QUERY("_id" << mongo::OID(this->versionid)), result);
    } else { //new version
        conn.insert("fileRecords.FileVersion", result);
    }

    string e = conn.getLastError();
    if (!e.empty()) {
        cout << "something failed failed: " << e << std::endl;
        sleep(1);
        exit(1);
    }
    else{
        cout << "Version " << this->versionnumber << " successfully written to database" << endl;
    }
}