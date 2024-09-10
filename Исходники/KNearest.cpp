/******************************************************
 * Mutator function for member variable theQuery.
 * 
 * Parameter:
 *   theQuery - a vector<double> to set as theQuery
**/
void KNearest::setQuery(string fileName)
{
  Scanner scan;
  ReadData readData;

  scan.openFile(fileName);
  this->theQuery = readData.readQuery(scan);

  scan.close();
} // void setQuery(vector<double> theQuery)