#include "header.h"
#include "font.h"


//* == -- -   - 	 -			  -   -= 	Create Font	 =  -   - 			- 	 -  -- -  == */
bool CFfont::MakeFont()
{
	if (!isAll || (!isFont && !isGlow))
	{
		timeg = 0;
		return true;
	}
	
	int sTy = Ty, a;

	if (bRect)
	{
		Ux = rect_sx;	Uy = rect_sy;
		timeg = 0;	Ty = MinTex;
		while( rect_sx > Ty  ||  rect_sy > Ty )
			Ty *= 2;
		Sy = sx = Ty;
		/*chk*/
		if (Ty > MaxTex )
		{
			format(s,S, "%d", Ty );
			WrnMsg( s, "Texture size too big" );
		}
	}
	else  // ! bRect
	{
		//  clear --
		//size_t size = MaxTex * MaxTex;
		//memset(tFont, 0, size);
		//memset(tGlow, 0, size);
		//memset(tAlpha, 0, size);
	
		/*crt fnt*/
		DeleteObject( hf );	 hf = 0;

		DWORD qla[5] = {NONANTIALIASED_QUALITY, ANTIALIASED_QUALITY, PROOF_QUALITY, CLEARTYPE_QUALITY, CLEARTYPE_NATURAL_QUALITY};
		hf = CreateFontA( sy, 0, 0, 0, (fbold == 0) ? FW_NORMAL : FW_BOLD, 0, 0, 0,
			DEFAULT_CHARSET, //EASTEUROPE_CHARSET, ANSI_CHARSET
			OUT_TT_PRECIS, CLIP_TT_ALWAYS,  qla[ql], DEFAULT_PITCH, fontName );
		if (hf == 0 )
			WrnMsg( "create font fail", "MakeFont" );
			
		int i, j, k, yy;

		Sy =  max( 1, sy + ay + by );
		if (Sy > MaxSY )
			WrnMsg( "Texture size too big.", "MakeFont" );

		/*Codes:*/
		ForEachChar
			if (h[n].ch)
				h[n].s = h[n].ch;
			else
				h[n].s = n + z1;

		/*[Width]*/
		static ABCFLOAT A[256];
		SelectObject( dc, hf );
		GetCharABCWidthsFloat( dc, 0, 255, A );
		ssn = 0;	ss = 0;
		
		ForEachChar
		{
			h[n].h[0] = i = A[h[n].s].abcfA;
			h[n].h[1] = j = A[h[n].s].abcfB;
			h[n].h[2] = k = A[h[n].s].abcfC;
			if (i < 0 )  i = - i;
			if (k < 0 )  k = - k;
			w = j + max( k,  ax + bx );
			h[n].wi = w  + h[n].ss;
			if (w > ss )
			{
				ssn = n;	ss = w;
			}
		}

		/*fixed width > */
		if (fix )
		{
			int s0 = 0;
			ForEachChar
				if (h[n].wi > s0 )
					s0 = h[n].wi;	//max width
			ForEachChar
			{
				h[n].of = ( s0 - h[n].wi ) / 2;
				h[n].ps = 1;
				h[n].wi = s0 + ax + bx;
			}
			ss = s0;
		}
		/*variable width > */
		else
			ForEachChar
			{
				h[n].of = 0;
				h[n].ps = h[n].pp;
				/*enter*/
				if (h[n].ch == 13 )
					h[n].wi = - bx;
			}

		// width (smooth) groups
		if (!fix )
		{
			ZeroMem( grw );
			int g;
			ForEachChar
			{
				g = h[n].gr;	
				if (g > 0 && g <= MaxGroups )
					if (h[n].wi > grw[g] )
						grw[g] = h[n].wi + grwi[g];
			}

			//mx wi gr
			/*of*/
			for (g = 1;	g <= MaxGroups;	g++)
				if (grw[g] > 0 )
				ForEachChar
					if (h[n].gr == g )
					{
						h[n].of = ( grw[g] - h[n].wi ) / 2;
						h[n].ps = 1;
						h[n].wi = grw[g];
					}
		}