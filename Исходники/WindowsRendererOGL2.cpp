		void WindowsRendererOGL2::SetViewLookAt(
			const Arithmetic::Vector3 &p_Position,
			const Arithmetic::Vector3 &p_Point,
			const Arithmetic::Vector3 &p_WorldUp )
		{
			// Calculate the view vectors
			Arithmetic::Vector3 ViewDir;
			Arithmetic::Vector3 ViewRight;
			Arithmetic::Vector3 ViewUp;

			ViewDir.Copy( p_Point - p_Position );
			ViewDir.Normalise( );

			ViewRight.Copy( ViewDir.Cross( p_WorldUp ) );
			ViewRight.Normalise( );

			ViewUp.Copy( ViewRight.Cross( ViewDir ) );
			ViewUp.Normalise( );

			Arithmetic::Matrix3x3 Mat3;
			Mat3.SetRows( ViewRight, ViewUp, -ViewDir );

			Arithmetic::Vector3 Position;
			Position.Copy( -( Mat3*p_Position ) );

			// Call SetView3D to handle the rest
			SetView3D( ViewRight, ViewUp, -ViewDir, Position );
		}