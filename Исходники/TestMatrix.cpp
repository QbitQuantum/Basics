void TestMatrix::testTranspose ()
{
  bool success = true;
  int row, col;
  
  // Try 3x3 matrix
  Matrix before (3);
  int counter = 0;
  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++) {
      before.set (row, col, ++counter);
    }
  }

  Matrix after = before.transpose ();
  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++) {
      if (before.get (row, col) != after.get (col, row)) {
        success = false;
        break;
      }
    }
  }
  
  QVERIFY (success);
}