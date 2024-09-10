void main(int argc,String *argv) {

  ArgParser a=ArgParser(argc,argv);
  bool useold=a.argexists("-o","use a previous calculation of the map");
  String iname=a.getarg();
  String bname=a.getarg();
  a.done();

  Map2d<float> *image=Map2d<float>::readfile(iname);
  Map2d<bool> total=*Map2d<bool>::readbinfile(bname)->binscaleto(image->width,image->height);
	
  Map2d<int> rm;
  if (!useold) {
	  rm=total.getregionmap(true);
	  rm.writefile("map.bmp");
  	writeinttofile("map.bmp.dat",rm.largest());
	} else {
	  int i=readintfromfile("map.bmp.dat");
	  if (i>255)
	    error("Cannot re-read map: greyscale resolution too low!");
  	rm=*Map2d<int>::readfile("map.bmp",i);
 }
	
	List<Region> cs=rm.collectregions();
	
	List<Blob> bs;
	for (int i=1;i<=cs.len;i++) {
	  bs.add(Blob(cs.p2num(i)));
//	  for (;i<=cs.len && myrnd()<0.9;i++)
//  	  bs.p2num(bs.len)->add(cs.p2num(i));
  }
	
/*	RGBmp *out=new RGBmp(image->width,image->height);
	
	for (int i=1;i<=bs.len;i++)
	  out->line(bs.p2num(i)->line(),myRGB::red);
	
	out->writefile("out.bmp");*/
		
  findlines(bs,rm);

}