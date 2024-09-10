int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    cout << "Error: usage: " << argv[0] << " <input jpeg filename>" << endl;
    return -1;
  }
  
  Image img;
  if (img.load(argv[1]) != 0) return -1;
  
  bool save_output = true;
  img.analyze(save_output);
  
  img.compress("output/image640.jpg");
  
  return 0;
}