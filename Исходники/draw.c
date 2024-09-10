color calculate_Id(struct matrix *polygons, screen s, color c, int i){
  color Id, Idt;
  Id.red = 0;
  Id.green = 0;
  Id.blue = 0;
  //Idiffuse = Cp * Kd * (L^ (dot product) N^)
  int li;
  color cp;
  double xdot,ydot,zdot,cos_theta;
  for(li=0; li<light_index; li++){
    cp.red = lights[li][3];
    cp.green = lights[li][4];
    cp.blue = lights[li][5];

    xdot = lights_normalized[li][0]*surface_normal[0];
    ydot = lights_normalized[li][1]*surface_normal[1];
    zdot = lights_normalized[li][2]*surface_normal[2];
    cos_theta = xdot + ydot + zdot;
    //L_dot_N[li] = cos_theta;

    Idt.red = truncf(cp.red * kdr * cos_theta);
    Idt.green = truncf(cp.green * kdg * cos_theta);
    Idt.blue = truncf(cp.blue * kdb * cos_theta);

    if(Idt.red<0){
      Idt.red = 0;
    }else if(Idt.red>255){
      Idt.red = 255;
    }
    if(Idt.green<0){
      Idt.green = 0;
    }else if(Idt.green>255){
      Idt.green = 255;
    }
    if(Idt.blue<0){
      Idt.blue = 0;
    }else if(Idt.blue>255){
      Idt.blue = 255;
    }
    Id.red += Idt.red;
    Id.green += Idt.green;
    Id.blue += Idt.blue;
  }
  if(Id.red>255)
    Id.red=255;
  if(Id.green>255)
    Id.green=255;
  if(Id.blue>255)
    Id.blue=255;
  return Id;
}