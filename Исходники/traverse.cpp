		void Tree<ElementContainer>::TraversePacket(Context<size,flags> &c,const Selector<size> &selector) const
		{
			bool split=1;

			enum { reflected=!(flags&(isct::fPrimary|isct::fShadow)) };

			bool selectorsFiltered=size<=(reflected?4:isComplex?64:16);
			if(!Selector<size>::full)
				for(int n=0;n<size/4;n++)
					if(selector.Mask4(n)!=0x0f0f0f0f) {
						selectorsFiltered=0;
						break;
					}

			if((Selector<size>::full||selectorsFiltered)
					&& size <= (reflected?4 : isComplex? 64 : 16)) {
				const Vec3q &dir=c.Dir(0);
				bool signsFiltered=1;
				int msk=_mm_movemask_ps(_mm_shuffle_ps(_mm_shuffle_ps(dir.x.m,dir.y.m,0),dir.z.m,0+(2<<2)))&7;

				if(filterSigns) {					
					for(int n=0;n<size;n++) if(GetVecSign(c.Dir(n))!=msk) {
						signsFiltered=0;
						break;
					}
				}

				if(signsFiltered) {
					bool primary = (flags & (isct::fPrimary|isct::fShadow)) && gVals[1];

					if((flags & isct::fShadow) &&!isComplex) {
						floatq dot=1.0f;
						for(int q=1;q<size;q++) dot=Min(dot,c.Dir(0)|c.Dir(q));
						if(ForAny(dot<0.9998f)) primary=0;
					}
					if(separateFirstElement) elements[0].Collide(c,0);
					if(primary) TraversePrimary(c);
					else TraversePacket0(c);

				//	if(primary && (flags & isct::fShadow)) c.stats.Skip();
					split=0;
				}
			}

			if(split) {
				for(int q=0;q<4;q++) {
					Context<size/4,flags> subC(c.Split(q));
					if(flags & isct::fShadow) subC.shadowCache=c.shadowCache;
					TraversePacket(subC,selector.SubSelector(q));
					if(flags & isct::fShadow) c.shadowCache=subC.shadowCache;
				}
			}
		}