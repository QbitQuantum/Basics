		static GLdouble recurse(const dvector &vec,GLdouble buff[]){
			GLdouble a,b,c;
			c=boost::numeric::ublas::norm_2(vec); //Länge des Vektors
			
			if(vec.size()>2)
			{
				dvector vec2(2);
				vec2[0]=vec[0];vec2[1]=vec[2];
				a=recurse(vec2,buff+1); //Länge des Vektors auf die size()-1-Ebene projeziert (und sein Winkel auf dieser Ebene)
			}
			else a=vec[0];

			b=vec[1];//Höhe
			*buff= a ? ATAN(b/a):90;
			if(a<0)*buff+=180;//2. & 3. Quadranten gibts nur im 2dim Raum, bei höherdim. Räumen wird das auf eine 180°-Rotation auf der darunter-liegenden "Ebene" zurï¿½ckgefï¿½hrt
			else if(b<0)*buff+=360;
			return c;
		}