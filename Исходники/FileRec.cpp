/**********************************************************
 *convert FileRec to bson, then write to db
 * 
***********************************************************/
void FileRec::writeToDB(mongo::DBClientConnection &conn) {
    BSONObjBuilder record; //build BSONObj
    record.append("filename", this->filename);
    record.append("Tempname", this->tempname);
    record.append("curhash", this->recentHash);
    record.append("ovhash", this->origHash);
    record.append("length", this->length);
    record.append("nversions", this->versionCount);
    /* love you */ long long time = this->modifytime.tv_nsec;
    record.append("Mtnsec", time);
    time = this->modifytime.tv_sec;
    record.append("mtsec", time);
    record.append("currentversion", this->refNum);

    mongo::BSONArrayBuilder bArr; //arrays to store multiple objects inside main object
    mongo::BSONArrayBuilder Comments;
    for (vector<string>::iterator it = blockhashes.begin(); it != blockhashes.end(); ++it) {
        bArr.append(*it);
    }

    for (vector<comment>::iterator it = comments.begin(); it != comments.end(); ++it) {
        BSONObjBuilder comment;
        comment.append("version", it->version); //
        comment.append("comment", it->comment);
        Comments.append(comment.obj());
    }

    if (!versions.empty()) { //if there are id's in the versions collection
        mongo::BSONArrayBuilder Version; //store the id's in an BSONarray
        for (vector<string>::iterator it = versions.begin(); it != versions.end(); ++it) {
            BSONObjBuilder version;
            version.append("id", (*it));
            Version.append(version.obj());
        }
        record.append("versionrec", Version.arr());
    }
    record.append("FileBlkHashes", bArr.arr()); //adding arrays to main record
    record.append("comments", Comments.arr());

    BSONObj result = record.obj();
    auto_ptr<mongo::DBClientCursor> cursor = conn.query("fileRecords.Filerec", MONGO_QUERY("filename" << filename));
    if (cursor->more()) {//already file rec in db so update
        conn.update("fileRecords.Filerec", MONGO_QUERY("filename" << filename), result);
    } else {
        conn.insert("fileRecords.Filerec", result); //must be new record 
    }
    string e = conn.getLastError();
    if (!e.empty()) {
        cout << "something failed failed: " << e << std::endl;
        sleep(1);
        exit(1);
    }
    else{
        cout << "record " << this->refNum << " successfully written to database" << endl;
    }
}