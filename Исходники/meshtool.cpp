  double CalcTetBadnessGrad (const Point3d & p1, const Point3d & p2,
			     const Point3d & p3, const Point3d & p4, double h,
			     int pi, Vec<3> & grad)
  {
    double vol, l, ll, lll;
    double err;

    const Point3d *pp1, *pp2, *pp3, *pp4;

    pp1 = &p1;
    pp2 = &p2;
    pp3 = &p3;
    pp4 = &p4;
  
    switch (pi)
      {
      case 2:
	{
	  swap (pp1, pp2);
	  swap (pp3, pp4);
	  break;
	}
      case 3:
	{
	  swap (pp1, pp3);
	  swap (pp2, pp4);
	  break;
	}
      case 4:
	{
	  swap (pp1, pp4);
	  swap (pp3, pp2);
	  break;
	}
      }
  

    Vec3d v1 (*pp1, *pp2);
    Vec3d v2 (*pp1, *pp3);
    Vec3d v3 (*pp1, *pp4);

    Vec3d v4 (*pp2, *pp3);
    Vec3d v5 (*pp2, *pp4);
    Vec3d v6 (*pp3, *pp4);

    vol = -Determinant (v1, v2, v3) / 6;  

    Vec3d gradvol;
    Cross (v5, v4, gradvol);
    gradvol *= (-1.0/6.0);


    double ll1 = v1.Length2();
    double ll2 = v2.Length2();
    double ll3 = v3.Length2();
    double ll4 = v4.Length2();
    double ll5 = v5.Length2();
    double ll6 = v6.Length2();

    ll = ll1 + ll2 + ll3 + ll4 + ll5 + ll6;
    l = sqrt (ll);
    lll = l * ll;

    if (vol <= 1e-24 * lll)
      { 
	grad = Vec3d (0, 0, 0);
	return 1e24;
      }



    Vec3d gradll1 (*pp2, *pp1);
    Vec3d gradll2 (*pp3, *pp1);
    Vec3d gradll3 (*pp4, *pp1);
    gradll1 *= 2;
    gradll2 *= 2;
    gradll3 *= 2;

    Vec3d gradll (gradll1);
    gradll += gradll2;
    gradll += gradll3;

    /*
    Vec3d gradll;
    gradll = v1+v2+v3;
    gradll *= -2;
    */

    err = 0.0080187537 * lll / vol; 


    gradll *= (0.0080187537 * 1.5 * l / vol);
    Vec3d graderr(gradll);
    gradvol *= ( -0.0080187537 * lll / (vol * vol) );
    graderr += gradvol;
  
    if (h > 0)
      {
	/*
	Vec3d gradll1 (*pp2, *pp1);
	Vec3d gradll2 (*pp3, *pp1);
	Vec3d gradll3 (*pp4, *pp1);
	gradll1 *= 2;
	gradll2 *= 2;
	gradll3 *= 2;
	*/
	err += ll / (h*h) + 
	  h*h * ( 1 / ll1 + 1 / ll2 + 1 / ll3 + 
		  1 / ll4 + 1 / ll5 + 1 / ll6 ) - 12;

	graderr += (1/(h*h) - h*h/(ll1*ll1)) * gradll1;
	graderr += (1/(h*h) - h*h/(ll2*ll2)) * gradll2;
	graderr += (1/(h*h) - h*h/(ll3*ll3)) * gradll3;
	cout << "?";
      }


    double errpow;
    if (teterrpow == 2)
      {
        errpow = err*err;   
        grad = (2 * err) * graderr;
      }
    else
      {
        errpow = pow (err, teterrpow);
        grad = (teterrpow * errpow / err) * graderr;
      }
    return errpow;
  }