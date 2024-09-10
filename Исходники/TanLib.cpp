// Tango allows layers from 0 = top to 22
void wtan_Graph_Level(const char *l)
{
   if (l == NULL) return;

   if (!isdigit(l[0]) && l[0] != '-')
   {
      // here are layer names
      if      (!STRCMPI(l,"TOPLAYER"))  cur_layer = 0;
      else if (!STRCMPI(l,"BOTTOMLAYER")) cur_layer = 1;
      else if (!STRCMPI(l,"POWERLAYER")) cur_layer = 2;
      else if (!STRCMPI(l,"GROUNDLAYER")) cur_layer = 3;
      else if (!STRCMPI(l,"MID1LAYER")) cur_layer = 4;
      else if (!STRCMPI(l,"MID2LAYER")) cur_layer = 5;
      else if (!STRCMPI(l,"MID3LAYER")) cur_layer = 6;
      else if (!STRCMPI(l,"MID4LAYER")) cur_layer = 7;
      else if (!STRCMPI(l,"TOPSILKLAYER")) cur_layer = 8;
      else if (!STRCMPI(l,"BOTTOMSILKLAYER")) cur_layer = 9;
      else if (!STRCMPI(l,"TOPSOLDERLAYER")) cur_layer = 10;
      else if (!STRCMPI(l,"BOTTOMSOLDERLAYER")) cur_layer = 11;
      else if (!STRCMPI(l,"TOPASSLAYER")) cur_layer = 12;
      else if (!STRCMPI(l,"BOTTOMASSLAYER")) cur_layer = 13;
      else if (!STRCMPI(l,"BOARDLAYER")) cur_layer = 14;
      else if (!STRCMPI(l,"CONNECTLAYER")) cur_layer = 15;
      else if (!STRCMPI(l,"DRILLLAYER")) cur_layer = 16;
      else if (!STRCMPI(l,"KEEPOUTLAYER")) cur_layer = 17;
      else if (!STRCMPI(l,"TITLELAYER")) cur_layer = 18;
      else if (!STRCMPI(l,"MID5LAYER")) cur_layer = 19;
      else if (!STRCMPI(l,"MID6LAYER")) cur_layer = 20;
      else if (!STRCMPI(l,"MID7LAYER")) cur_layer = 21;
      else if (!STRCMPI(l,"MID8LAYER")) cur_layer = 22;
      else if (!STRCMPI(l,"ALL")) cur_layer = -1; // this is for all pins
   }
   else
   {
      cur_layer = atoi(l);
      if (cur_layer < 0)   cur_layer = 0;
      if (cur_layer > 22)  cur_layer = 22;
   }
}