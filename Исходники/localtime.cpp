//
//  Compare two objects. Note that we can't compare the
//  rules, since two different rules might be equivalent.
//
int LocalTime::compare(const LocalTime& that) const {
    int rc = 0;
    int32_t ot = this->getOffset();
    int32_t thatot = that.getOffset();
    bool dt = this->getDst();
    bool thatdt = that.getDst();
    if (ot < thatot) {
        rc = -1;
    } else if (ot > thatot) {
        rc = 1;
    } else if (dt && (!thatdt)) {
        rc = -1;
    } else if ((!dt) && thatdt) {
        rc = 1;
    } else {
        rc = this->DateTime::compare(that);
    }
    return rc;
}