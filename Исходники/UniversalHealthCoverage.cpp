/* Determines any covered cities in hospital location and removes them from the cities set.
 * Returns the removed/covered cities.
 */
Set<string> getCoveredCities(Set<string>& cities, Set<string> location) {
    Set<string> coveredCities;
    
    foreach(string city in cities) {
        if (location.contains(city)) {
            coveredCities.add(city);
            cities.remove(city);
        }
    }
    
    return coveredCities;
}