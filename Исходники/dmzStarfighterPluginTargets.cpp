void
dmz::StarfighterPluginTargets::_new_ori (
      const Float64 DeltaTime,
      const Vector &Dir,
      TargetStruct &obj,
      Matrix &ori) {

   Vector hvec (Dir);

   hvec.set_y (0.0);
   hvec.normalize_in_place ();

   Float64 heading = Forward.get_angle (hvec);

   Vector hcross = Forward.cross (hvec).normalize ();

   if (hcross.get_y () < 0.0) { heading = TwoPi64 - heading; }

   if (heading > Pi64) { heading = heading - TwoPi64; }
   else if (heading < -Pi64) { heading = heading + TwoPi64; }

   Float64 pitch = Dir.get_angle (hvec);
   Vector pcross = Dir.cross (hvec).normalize ();
   Vector ncross = hvec.cross (pcross);

   if (ncross.get_y () < 0.0) { pitch = TwoPi64 - pitch; }

   obj.heading = _rotate (DeltaTime, obj.heading, heading);

   obj.pitch = _rotate (DeltaTime, obj.pitch, pitch);

   if (is_zero64 (pitch - obj.pitch) && is_zero64 (heading - obj.heading)) {

      obj.onTarget = true;
   }

   Matrix hm (Up, obj.heading);

   Matrix pm (Right, obj.pitch);

   ori = hm * pm;
}