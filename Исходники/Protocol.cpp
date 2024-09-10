ConstString Protocol::getSenderSpecifier() {
    Route r = getRoute();
    // We pull the sender name from the route.
    ConstString from = r.getFromName();
    // But we need to add any qualifiers looking in the carrier
    // name.  Ideally, we wouldn't need to bundle that in with
    // the sender name, but we do it for now in the name of
    // backwards compatibility.
    ConstString carrier = r.getCarrierName();
    size_t start = carrier.find("+");
    if (start!=String::npos) {
        from += " (";
        for (size_t i=start+1; i<(size_t)carrier.length(); i++) {
            char ch = carrier[i];
            if (ch=='+') {
                from += ") (";
            } else if (ch=='.') {
                from += " ";
            } else {
                from += ch;
            }
        }
        from += ")";
    }
    return from;
}