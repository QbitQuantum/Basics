int main() {
  Libc x;
  x.seta("abc");
  x.setb("bca");
  x.setc("cab");

  cout << x.geta() << x.getb() << x.getc() << endl;

  return 0;
}