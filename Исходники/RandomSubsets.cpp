Set<int> randomSubsetOf(Set<int>& s){
  bool tag=bool(randomInteger(0,1));
  if(s.isEmpty()){
    Set<int> emptySet;
    return emptySet;
  }
  if(tag){
    int element=s.first();
    s.remove(element);
    Set<int>    result=randomSubsetOf(s);
    result.add(element);
    return result;
  }
  if(!tag){
    int element=s.first();
    s.remove(element);
    return randomSubsetOf(s);
  }
}