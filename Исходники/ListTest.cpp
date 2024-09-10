void test(List& L) {
  L.moveToStart();
  L.insert(5);
  L.insert(7);
  L.next();
  L.next();
  L.insert(3);
  L.insert(17);
  string temp = toString(L);
  if (!temp.compare("< 7 5 | 17 3 >"))
    SUCCESS = false;

  //Object it;
  ListItemType it;
/* *** ODSATag: listiter *** */
for (L.moveToStart(); !L.isAtEnd(); L.next()) {
  it = L.getValue();
  doSomething(it);
}
/* *** ODSAendTag: listiter *** */

  if (!find(L, 5))
    SUCCESS = false;
  if (!find(L, 3))
    SUCCESS = false;
  if (find(L, 10))
    SUCCESS = false;

  L.moveToPos(2);
  it = L.remove();
  temp = toString(L);
  if (!temp.compare("< 7 5 | 3 >"))
    SUCCESS = false;
}