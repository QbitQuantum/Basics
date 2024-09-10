int main(){
 List<int> l;
 for (int i = 0; i < 10; i++){
    l.append(i);
 }
 l.pprint();
 l.remove(5);
 l.pprint();
 l.remove(9);
 l.pprint();
 return 0;
}