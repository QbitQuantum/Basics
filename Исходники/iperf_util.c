const char *
get_optional_features(void)
{
    static char features[1024];
    unsigned int numfeatures = 0;

    snprintf(features, sizeof(features), "Optional features available: ");

#if defined(HAVE_CPU_AFFINITY)
    if (numfeatures > 0) {
	strncat(features, ", ", 
		sizeof(features) - strlen(features) - 1);
    }
    strncat(features, "CPU affinity setting", 
	sizeof(features) - strlen(features) - 1);
    numfeatures++;
#endif /* HAVE_CPU_AFFINITY */
    
#if defined(HAVE_FLOWLABEL)
    if (numfeatures > 0) {
	strncat(features, ", ", 
		sizeof(features) - strlen(features) - 1);
    }
    strncat(features, "IPv6 flow label", 
	sizeof(features) - strlen(features) - 1);
    numfeatures++;
#endif /* HAVE_FLOWLABEL */
    
#if defined(HAVE_SCTP)
    if (numfeatures > 0) {
	strncat(features, ", ", 
		sizeof(features) - strlen(features) - 1);
    }
    strncat(features, "SCTP", 
	sizeof(features) - strlen(features) - 1);
    numfeatures++;
#endif /* HAVE_SCTP */
    
#if defined(HAVE_TCP_CONGESTION)
    if (numfeatures > 0) {
	strncat(features, ", ", 
		sizeof(features) - strlen(features) - 1);
    }
    strncat(features, "TCP congestion algorithm setting", 
	sizeof(features) - strlen(features) - 1);
    numfeatures++;
#endif /* HAVE_TCP_CONGESTION */
    
#if defined(HAVE_SENDFILE)
    if (numfeatures > 0) {
	strncat(features, ", ",
		sizeof(features) - strlen(features) - 1);
    }
    strncat(features, "sendfile / zerocopy",
	sizeof(features) - strlen(features) - 1);
    numfeatures++;
#endif /* HAVE_SENDFILE */

    if (numfeatures == 0) {
	strncat(features, "None", 
		sizeof(features) - strlen(features) - 1);
    }

    return features;
}