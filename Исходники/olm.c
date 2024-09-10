static void deleteNodeFromCountry(LCountry* country, OsmId id) {
    beginTransaction(country->db);
    if(deleteFromDbById(country->db, country->deleteNodeTagsStatement, id) &&
       deleteFromDbById(country->db, country->deleteNodeStatement, id)) {
        commitTransaction(country->db);
    } else {
        rollbackTransaction(country->db);
    }
}