int trichro_back_buffer(int xchroma, int ychroma, int rayon, int largeurchroma)//calcul et couleurs dans les 10eme de sec.
{
clear_bitmap(bmp_buffer_trichro);
int coord[4];
for (hcl=0.0; hcl<360.0; hcl+=0.4)
{
     xcl = cos(hcl*PI/180.0)*(rayon+16);
	 ycl = sin(hcl*PI/180.0)*(rayon+16);

	 hsv_to_rgb(hcl, 1.0, 1.0, &rcl, &gcl, &bcl);

	 coord[0]=xchroma;
     coord[1]=ychroma;
     coord[2]=(int)(xchroma+xcl);
     coord[3]=(int)(ychroma+ycl);
//	 ol::Line(ol::Vec2D(xchroma,ychroma),ol::Vec2D(xchroma+xcl,ychroma+ycl)).Draw(Rgba(rcl,gcl,bcl));
 polygon(bmp_buffer_trichro, 2, coord, makecol(rcl,gcl,bcl));
}

//ol::Circle MasqueNoir(ol::Vec2D(xchroma,ychroma),rayon-16);
//MasqueNoir.Draw(CouleurFond);
circlefill(bmp_buffer_trichro,  xchroma,ychroma, rayon-16, makecol(0,0,0));

for(angle = 0 ; angle <(PI*360) / 180  ; angle+=0.1)//radians
{
   vx = cos(angle)*rayon;
   vy = sin(angle)*rayon;
   if(mouse_x>xtrichro_window+vx-16  && mouse_x< xtrichro_window+vx+16 && mouse_y>ytrichro_window+vy-16 && mouse_y<ytrichro_window+vy+16
      && mouse_button==1 && window_focus_id==902)

   {
   angle_snap=angle;//angle rotation roue couleur
   position_curseur_hue_x= xtrichro_window+vx;//affichage
   position_curseur_hue_y=ytrichro_window+vy ;//affichage
   cref=getpixel(bmp_buffer_trichro,(int)(xchroma+vx),(int)(ychroma+vy));
    r_pick=getr(cref);
    v_pick=getg(cref);
    b_pick=getb(cref);
   stock_etat_picker_dans_dockcolor(dock_color_selected);
    //angle=((PI*360) / (180*127))*midi_levels[497];
    midi_levels[497]=(int)(angle_snap/((PI*360) / (180*127)));
    if(midi_send_out[497]==1){index_send_midi_out[497]=1;}
    mouse_released=1;
   }

}


//attaque midi
if (miditable[0][497]==istyp && miditable[1][497]==ischan && miditable[2][497]==ispitch)
{
  angle_snap=((PI*360) / (180*127))*midi_levels[497];
  vx = cos(angle_snap)*125;
  vy = sin(angle_snap)*125;
  position_curseur_hue_x= xtrichro_window+vx;
  position_curseur_hue_y=ytrichro_window+vy ;
  cref=getpixel(bmp_buffer_trichro,(int)(xchroma+vx),(int)(ychroma+vy));
  r_pick=getr(cref);
  v_pick=getg(cref);
  b_pick=getb(cref);
  stock_etat_picker_dans_dockcolor(dock_color_selected);
}
//triangle
	V3D_f v1 =
	{
		xchroma+vxd, ychroma+vyd, 0,
		0., 0.,
		makecol(0, 0, 0) // black vertex
	};
	V3D_f v2 =
	{
		xchroma+vxw, ychroma+vyw, 0,
		0., 0.,
		makecol(255, 255, 255) // white vertex
	};
	V3D_f v3 =
	{
		xchroma+vxh, ychroma+vyh, 0,
		0., 0.,
		makecol(r_pick, v_pick, b_pick) // color vertex
	};


	triangle3d_f(bmp_buffer_trichro, POLYTYPE_GCOL, NULL, &v1, &v2, &v3);


//definir si on est dans l aire du triangle
//(angle (Pa-1 Pa-2) * angle (Pa-2 Pa-3) * angle (Pa-3 Pa-1)) resultat pos ou neg
float angle1, angle2,angle3;
angle1=CounterClockWise(mouse_x,mouse_y,xtrichro_window+vxd, ytrichro_window+vyd,xtrichro_window+vxh, ytrichro_window+vyh) ; //Pa1-Pa2
angle2=CounterClockWise(mouse_x,mouse_y,xtrichro_window+vxh, ytrichro_window+vyh,xtrichro_window+vxw, ytrichro_window+vyw);//Pa2 - Pa3
angle3=CounterClockWise(mouse_x,mouse_y,xtrichro_window+vxw, ytrichro_window+vyw, xtrichro_window+vxd, ytrichro_window+vyd);//Pa3-Pa1

if((angle1*angle2*angle3) <=0 ) //dans le triangle formé par la souris et les 3 points du triangle
{


if(mouse_b&1 && mouse_x>xtrichro_window+vxd && mouse_x<xtrichro_window+vxw && mouse_y>ytrichro_window+vyd && mouse_y<ytrichro_window+vyh && window_focus_id==902)
{
picker_x=mouse_x-xtrichro_window;
picker_y=mouse_y-ytrichro_window;
stock_etat_picker_dans_dockcolor(dock_color_selected);
}

}


if(getpixel(bmp_buffer_trichro,(int)(xchroma+picker_x),(int)(ychroma+picker_y))!=0)
{colorpicker=getpixel(bmp_buffer_trichro,(int)(xchroma+picker_x),(int)(ychroma+picker_y));}

my_red=getr(colorpicker);
my_green=getg(colorpicker);
my_blue=getb(colorpicker);

if (index_quadri==1)
{
   float hue, saturation, value;
   rgb_to_hsv(my_red, my_green, my_blue, &hue, &saturation, &value);
   //saturation: plus il y en a , moins de jaune il y a
   my_yellow=(int)(255-(255*saturation));
}
return(0);
}