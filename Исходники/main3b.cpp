int main() {
  try {
    pis("zacatek");
    Queue<int> q;
    q.add(1); q.add(2); q.add(3); 
    pis("q1");
    Queue<int> q1 = q; 
    Queue<int> q2;
    q2=q;
    pis("q1konec");
    q.remove(); q.remove();
    for (int i=10; i<=35; i++)
      q.add(i);
    while (!q.empty()) {
        cout << q.front() << ' ';
        q.remove();
    }
    cout << endl;
    while (!q1.empty()) {
        cout << q1.front() << ' ';
        q1.remove();
    }
    cout << endl;
    while (!q2.empty()) {
        cout << q2.front() << ' ';
        q2.remove();
    }
    cout << endl;
  }
  catch (const char* s) {
    cout << "chyba: " << s << endl;
  }
  //system("PAUSE");
  return 0;
}