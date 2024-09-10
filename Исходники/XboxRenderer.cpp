		void XboxRenderer::SetViewLookAt(
				const Arithmetic::Vector3 &p_Position,
				const Arithmetic::Vector3 &p_Point,
				const Arithmetic::Vector3 &p_WorldUp )
		{
			// Calculate the view vectors
			Arithmetic::Vector3 ViewDir;
			Arithmetic::Vector3 ViewRight;
			Arithmetic::Vector3 ViewUp;

			ViewDir = p_Point - p_Position;
			ViewDir.Normalise( );
			ViewUp =  p_WorldUp - p_WorldUp.Dot( ViewDir )*ViewDir;
			ViewUp.Normalise( );
			ViewRight = ViewDir.Cross( ViewUp );

			// Call SetView3D to handle setting the view matrix
			return SetView3D( ViewRight, ViewUp, ViewDir, p_Position );
		}