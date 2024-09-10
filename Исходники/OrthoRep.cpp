// The check function below tests if the current OrthoRep instance really
// represents a correct orthogonal representation, i.e., it tests if
//    * the associated graph is embedded.
//    * the external face of the embedding is set
//    * the sum of the angles at each vertex is 4
//    * if corresponding bend strings are consistent, that is, if e has
//      adj. entries adjSrc and adjTgt, then the bend string of adjTgt
//      is the string obtained from bend string of adjSrc by reversing the
//      sequence and flipping the bits
//    * the shape of each face is rectagonal, i.e., if
//        #zeros(f) - #ones(f) - 2|f| + sum of angles at vertices in f
//      is 4 if f is an internal face or -4 if f is the external face.
bool OrthoRep::check(String &error)
{
	const Graph &G = (Graph&) *m_pE;

	// is the associated graph embedded ?
	if (G.representsCombEmbedding() == false) {
		error = "Graph is not embedded!";
		return false;
	}

	// sum of angles at each vertex equals 4 ?
	node v;
	forall_nodes(v,G)
	{
		int sumAngles = 0;
		adjEntry adj;
		forall_adj(adj,v)
			sumAngles += angle(adj);
		if(sumAngles != 4) {
			error.sprintf("Angle sum at vertex %d is %d.",
				v->index(), sumAngles);
			return false;
		}
	}