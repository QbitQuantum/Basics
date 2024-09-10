static int
assignToVideoContext(HGLRC hRC)
{
    // Traverse existing Video Contexts to see if we can share gfx resources with any of them
    video_contexts_t::iterator it = video_contexts.begin();
    int i = 0;
	int iempty = -1;
    for ( ; it != video_contexts.end(); it ++, i++) 
    {
		if (!it->empty()) {
			// Try to share resource lists with first Context in the group
			if (wglShareLists(it->front(), hRC) == TRUE) {
				// Succeeded, so add the new Rendering Context to this Video Context
				it->push_back(hRC);
				// We're done, this is the Video Context we were looking for
				return 1 + i;
			}
		}
		else if (iempty < 0) {
			iempty = i; // remember this Video Context as available
		}
    }
    // Could not share with any Video Context, so create and add new Video Context (or reuse an empty one)
	if (iempty < 0) {
		video_context_t vctx;
		vctx.push_back(hRC);
		video_contexts.push_back(vctx);
	    return 1 + i; // add 1 to reserve 0 = unassigned
	}
	else {
		video_contexts[iempty].push_back(hRC);
		return 1 + iempty;
	}
}