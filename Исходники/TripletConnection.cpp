void TripletConnection::propagate_backward()
{
	if (stdp_active) { 
		SpikeContainer::const_iterator spikes_end = dst->get_spikes_immediate()->end();
		// loop over all spikes
		for (SpikeContainer::const_iterator spike = dst->get_spikes_immediate()->begin() ; // spike = post_spike
				spike != spikes_end ; 
				++spike ) {
			// Since we need the local id of the postsynaptic neuron that spiked 
			// multiple times, we translate it here:
			NeuronID translated_spike = dst->global2rank(*spike); 

			// loop over all presynaptic partners
			for (const NeuronID * c = bkw->get_row_begin(*spike) ; c != bkw->get_row_end(*spike) ; ++c ) {

				#ifdef CODE_ACTIVATE_PREFETCHING_INTRINSICS
				// prefetches next memory cells to reduce number of last-level cache misses
				_mm_prefetch((const char *)bkw_data[c-bkw_ind+2],  _MM_HINT_NTA);
				#endif

				// computes plasticity update
				AurynWeight * weight = bkw->get_data(c); 
				*weight += dw_post(*c,translated_spike);

				// clips too large weights
				if (*weight>get_max_weight()) *weight=get_max_weight();
			}
		}
	}
}