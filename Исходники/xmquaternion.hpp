			inline this_type XM_CALLCONV inversed() const
			{
				this_type ret;
				ret.v = XMQuaternionInverse(this->v);
				return ret;
			}