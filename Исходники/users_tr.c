void make_users_control_graph(void)
{
pause_thread(THREAD_SCREEN);
// Set a negative number here.
// In case several windows are desired, give them different
// negative numbers and use scro[m].no to decide what to do
// in your mouse_on_users_graph routine.
check_ug_borders();  // required for move graph
scro[users_graph_scro].no=USERS_GRAPH_TYPE1;
// These are the coordinates of the border lines.
scro[users_graph_scro].x1=ug.xleft;
scro[users_graph_scro].x2=ug.xright;
scro[users_graph_scro].y1=ug.ytop;
scro[users_graph_scro].y2=ug.ybottom;
// Each border line is treated as a button.
// That is for the mouse to get hold of them so the window can be moved.
ugbutt[UG_LEFT].x1=ug.xleft;
ugbutt[UG_LEFT].x2=ug.xleft+2;
ugbutt[UG_LEFT].y1=ug.ytop;
ugbutt[UG_LEFT].y2=ug.ybottom;
ugbutt[UG_RIGHT].x1=ug.xright;
ugbutt[UG_RIGHT].x2=ug.xright-2;
ugbutt[UG_RIGHT].y1=ug.ytop;
ugbutt[UG_RIGHT].y2=ug.ybottom;
ugbutt[UG_TOP].x1=ug.xleft;
ugbutt[UG_TOP].x2=ug.xright;
ugbutt[UG_TOP].y1=ug.ytop;
ugbutt[UG_TOP].y2=ug.ytop+2;
ugbutt[UG_BOTTOM].x1=ug.xleft;
ugbutt[UG_BOTTOM].x2=ug.xright;
ugbutt[UG_BOTTOM].y1=ug.ybottom;
ugbutt[UG_BOTTOM].y2=ug.ybottom-2;
// Draw the border lines
graph_borders((void*)&ug,7);
ug_oldx=-10000;                   //from freq_control
settextcolor(7);
make_button(ug.xleft+27.5*text_width+2,ug.ybottom-1*text_height/2-1,
                                         ugbutt,UG_DECREASE_OFFS_HZ,25);
make_button(ug.xleft+29*text_width+2,ug.ybottom-1*text_height/2-1,
                                     ugbutt,UG_INCREASE_OFFS_HZ,24); 

make_button(ug.xleft+27.5*text_width+2,ug.ybottom-3*text_height/2-1,
                                         ugbutt,UG_DECREASE_OFFS_KHZ,25);
make_button(ug.xleft+29*text_width+2,ug.ybottom-3*text_height/2-1,
                                     ugbutt,UG_INCREASE_OFFS_KHZ,24); 

make_button(ug.xleft+27.5*text_width+2,ug.ybottom-5*text_height/2-1,
                                         ugbutt,UG_DECREASE_SERPORT_NMBR,25);
make_button(ug.xleft+29*text_width+2,ug.ybottom-5*text_height/2-1,
                                     ugbutt,UG_INCREASE_SERPORT_NMBR,24);

make_button(ug.xleft+57.5*text_width+2,ug.ytop+1.5*text_height/2-1,
                                         ugbutt,UG_DECREASE_TRANSCEIVER_NMBR,25);
make_button(ug.xleft+59*text_width+2,ug.ytop+1.5*text_height/2-1,
                                     ugbutt,UG_INCREASE_TRANSCEIVER_NMBR,24);
show_user_parms();
//draw separatorlines in usergraph
//vertical
lir_line(ug.xleft+30.5*text_width,ug.ytop+1.3*text_height,ug.xleft+30.5*text_width,ug.ybottom,7);
lir_line(ug.xleft+10*text_width,ug.ytop+0*text_height,ug.xleft+10*text_width,ug.ytop+1.3*text_height,7);
//horizontal
lir_line(ug.xleft,ug.ytop+1.3*text_height,ug.xright,ug.ytop+1.3*text_height,7);
//
resume_thread(THREAD_SCREEN);
}