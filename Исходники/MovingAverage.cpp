/******************************************************************************
In the readData() we are simply inputting the "xintput.txt" file in a vector. 
we create a object for Scanner class and use a While loop to continuously scan
for text in the file until it has nothing else in it. While the scanner is 
reading in the values this data is now pushed back into a vector called TheData.
We now have a vector that consist of 100 values of stock and it now received.


****/
void MovingAverage::readData(std::string fileName)
{
Scanner inScanner;
double value ;
inScanner.openFile(fileName);
std::cout << "Now receiving Stocks" << std::endl;

  while(inScanner.hasNext())
  {
    value = inScanner.nextDouble(); 
    theData.push_back(value);  
  }
  
 
}