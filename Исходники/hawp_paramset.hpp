 /* Undocumented
  * Compute the continuous square root of \f$ \det Q \f$ after an update
  * of the \f$ Q \f$ parameter.
  */
 inline void resync() {sqrt_detQ_(Q_.determinant());}