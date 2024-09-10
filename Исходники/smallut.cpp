// Date is Y[-M[-D]]
static bool parsedate(vector<string>::const_iterator& it,
                      vector<string>::const_iterator end, DateInterval *dip)
{
    dip->y1 = dip->m1 = dip->d1 = dip->y2 = dip->m2 = dip->d2 = 0;
    if (it->length() > 4 || !it->length() ||
            it->find_first_not_of("0123456789") != string::npos) {
        return false;
    }
    if (it == end || sscanf(it++->c_str(), "%d", &dip->y1) != 1) {
        return false;
    }
    if (it == end || *it == "/") {
        return true;
    }
    if (*it++ != "-") {
        return false;
    }

    if (it->length() > 2 || !it->length() ||
            it->find_first_not_of("0123456789") != string::npos) {
        return false;
    }
    if (it == end || sscanf(it++->c_str(), "%d", &dip->m1) != 1) {
        return false;
    }
    if (it == end || *it == "/") {
        return true;
    }
    if (*it++ != "-") {
        return false;
    }

    if (it->length() > 2 || !it->length() ||
            it->find_first_not_of("0123456789") != string::npos) {
        return false;
    }
    if (it == end || sscanf(it++->c_str(), "%d", &dip->d1) != 1) {
        return false;
    }

    return true;
}