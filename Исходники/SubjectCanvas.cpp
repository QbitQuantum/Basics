void SubjectCanvas::open() {
  BooL ok;
  QString s = MyInputDialog::getText(TR("Subject dialog"), TR("subject : "),
				     fromUnicode(name), ok);
  
  if (ok) {
    name = toUnicode(s);
    modified();
  }
}