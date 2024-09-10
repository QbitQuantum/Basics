		void WindowsRendererOGL3::SetViewLookAt(
			const Arithmetic::Vector3 &p_Position,
			const Arithmetic::Vector3 &p_Point,
			const Arithmetic::Vector3 &p_WorldUp )
		{
			// Calculate the view vectors
			Arithmetic::Vector3 ViewDir;
			Arithmetic::Vector3 ViewRight;
			Arithmetic::Vector3 ViewUp;

			// First, get the direction and normalise it
			ViewDir.Copy( p_Point - p_Position );
			ViewDir.Normalise( );

			// Next, use Gram-Schmidt orthogonalisation to get the Up vector
			// and normalise that
			ViewUp.Copy( p_WorldUp-p_WorldUp.Dot( ViewDir )*ViewDir );
			ViewUp.Normalise( );

			// As the previous two vectors are already normalised, there's no
			// need to normalise again.  Just use the cross product of the
			// direction and up vectors to generate the new orthogonal vector
			ViewRight.Copy( ViewDir.Cross( ViewUp ) );

			// Create the upper 3x3 matrix from the vectors (negating the
			// direction elements because the Z axis is pointing toward the
			// viewer)
			Arithmetic::Matrix3x3 Rot;
			Rot.SetRows( ViewRight, ViewUp, -ViewDir );

			// Create the position from the negative of the upper 3x3 matrix
			// multiplied by the desired position.
			Arithmetic::Vector3 Position;
			Position.Copy( -( Rot*p_Position ) );
			
			// Call SetView3D to handle the rest
			SetView3D( ViewRight, ViewUp, -ViewDir, Position );
		}