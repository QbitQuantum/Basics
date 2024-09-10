int main(){
  cout << "Hello World\n";
  HashTable<int>* HT = new HashTable<int>(0);
  HT->insert("taco", 3);
  HT->insert("banana", 4);
  HT->insert("taco", 5);
  cout << HT->find("taco") << "\n";
  cout << HT->find("banana") << "\n";
  HT->remove("banana");
  cout << HT->find("banana") << "\n";
  delete HT;
}