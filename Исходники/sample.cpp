// The SpawnParticles function is responsible for generating new 
// particles in your world.  You will call this function as you 
// you traverse your model's hierarchy.  When you reach a point
// in the hierarchy from where particles should be emitted, 
// call this function!
//
// SpawnParticles takes the camera transformation matrix as a 
// parameter.  More on this later.
void SampleModel::spawnParticles(Mat4<float> cameraTransform) {
	/****************************************************************
	**
	**	THIS FUNCTION WILL ADD A NEW PARTICLE TO OUR WORLD
	**
	**	Suppose we want particles to spawn from a the model's arm.
	**	We need to find the location of the model's arm in world
	**  coordinates so that we can set the initial position of new
	**  particles.	As discussed on the Animator project page,
	**  all particle positions should be in world coordinates.
	**
	**  At this point in execution, the MODELVIEW matrix contains the
	**  camera transforms multiplied by some model transforms.  In other words,
	**
	**  MODELVIEW = CameraTransforms * ModelTransforms
	**
	**	We are interested only in ModelTransforms, which is the
	**  transformation that will convert a point from the current, local
	**  coordinate system to the world coordinate system.
	**
	**	To do this, we're going to "undo" the camera transforms from the
	**  current MODELVIEW matrix.  The camera transform is passed in as
	**  a parameter to this function (remember when we saved it
	**  near the top of the model's draw method?).  We can "undo" the
	**  camera transforms by pre-multiplying the current MODELVIEW matrix
	**  with the inverse of the camera matrix.  In other words,
	**
	**  ModelTransforms = InverseCameraTransforms * MODELVIEW
	**
	********************************************************************/
	
	ParticleSystem *ps = ModelerApplication::Instance()->GetParticleSystem();
	
	//Get the current MODELVIEW matrix.
	//	... "Undo" the camera transforms from the MODELVIEW matrix
	//	... by multiplying Inverse(CameraTransforms) * CurrentModelViewMatrix.
	//	... Store the result of this in a local variable called WorldMatrix.
	//	...
	Mat4f ModelMatrix = getModelViewMatrix();
	Mat4f WorldMatrix = cameraTransform.inverse() * ModelMatrix;
	
	/*****************************************************************
	**
	**	At this point, we have the transformation that will convert a point
	**  in the local coordinate system to a point in the world coordinate
	**  system.
	**
	**  We need to find the actual point in world coordinates
	**  where particle should be spawned.  This is simply
	**  "the origin of the local coordinate system" transformed by
	**  the WorldMatrix.
	**
	******************************************************************/
	Vec4f Loc = WorldMatrix * Vec4f(0.0, 0.0, 0.0, 1.0);
	
	Vec4f VelL = WorldMatrix * Vec4f(0.0, 0.0, -0.5, 1.0);
	Vec4f Vel = VelL - Loc;
	Vec3f velocity(Vel[0], Vel[1], Vel[2]);

	velocity.normalize();

	/*****************************************************************
	**
	**	Now that we have the particle's initial position, we
	**  can finally add it to our system!
	**
	***************************************************************/
	ps->setParticleStart(Vec3f(Loc[0], Loc[1], Loc[2]), velocity);
}