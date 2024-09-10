Mat getVanishingLine(Mat a, Mat b, Mat c, Mat d){ //find the 
  Mat l1 = a.cross(b);
  cout << "a cross b = " << l1 << endl;
  Mat l2 = d.cross(c);
  cout << "d cross c = " << l2 << endl;
  Mat l3 = a.cross(d);
  cout << "a cross d = " << l1 << endl;
  Mat l4 = b.cross(c);
  cout << "b cross c = " << l2 << endl;
  Mat v1 = l1.cross(l2);
  Mat v2 = l3.cross(l4);

  Mat l = v1.cross(v2);
  Mat H = (Mat_<double>(3,3) << 1, 0, 0, 0, 1, 0, l.at<double>(0, 0), l.at<double>(1, 0), l.at<double>(2, 0));
    return H;
  
  //Mat l1 = a.dot(b);
  //Mat l1 = a.dot(b);
}