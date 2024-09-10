void
test_invert () {
  tree t1= test_tree ();
  for (int i=0; i<42; i++) {
    modification m1= test_modification (i);
    tree t2= clean_apply (t1, m1);
    modification m2= invert (m1, t1);
    tree t3= clean_apply (t2, m2);
    modification m3= invert (m2, t2);
    if (m1 != m3 || t1 != t3) {
      cout << "t1= " << t1 << "\n";
      cout << "m1= " << m1 << "\n";
      cout << "t2= " << t2 << "\n";
      cout << "m2= " << m2 << "\n";
      cout << "t3= " << t3 << "\n";
      FAILED ("inconsistency");
    }
 }
}