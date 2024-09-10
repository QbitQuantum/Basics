		void DivArm ()
		{
			uint32_t tmp = R(0);
			R(0) = R(1);
			R(1) = tmp;
			Div();
		}