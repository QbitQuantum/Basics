static int
startElement_METRIC(void *data, const char *el, const char **attr)
{
   xmldata_t *xmldata = (xmldata_t *)data;
   ganglia_slope_t slope = GANGLIA_SLOPE_UNSPECIFIED;
   struct xml_tag *xt;
   struct type_tag *tt;
   datum_t *hash_datum = NULL;
   datum_t *rdatum;
   datum_t hashkey, hashval;
   const char *name = NULL;
   const char *metricval = NULL;
   const char *type = NULL;
   int do_summary;
   int i, edge, carbon_ret;
   hash_t *summary;
   Metric_t *metric;

   if (!xmldata->host_alive ) return 0;

   /* Get name for hash key, and val/type for summaries. */
   for(i = 0; attr[i]; i+=2)
      {
         xt = in_xml_list(attr[i], strlen(attr[i]));
         if (!xt) continue;

         switch (xt->tag)
            {
               case NAME_TAG:
                  name = attr[i+1];
                  hashkey.data = (void*) name;
                  hashkey.size =  strlen(name) + 1;
                  break;
               case VAL_TAG:
                  metricval = attr[i+1];
                  break;
               case TYPE_TAG:
                  type = attr[i+1];
                  break;
               case SLOPE_TAG:
                  slope = cstr_to_slope(attr[i+1]);
               default:
                  break;
            }
      }

   metric = &(xmldata->metric);
   memset((void*) metric, 0, sizeof(*metric));

   /* Summarize all numeric metrics */
   do_summary = 0;
   tt = in_type_list(type, strlen(type));
   if (!tt) return 0;

   if (tt->type==INT || tt->type==UINT || tt->type==FLOAT)
      do_summary = 1;

   /* Only keep metric details if we are the authority on this cluster. */
   if (authority_mode(xmldata))
      {
         /* Save the data to a round robin database if the data source is alive
          */
         fillmetric(attr, metric, type);
	 if (metric->dmax && metric->tn > metric->dmax)
            return 0;

         if (do_summary && !xmldata->ds->dead && !xmldata->rval)
            {
                  debug_msg("Updating host %s, metric %s", 
                                  xmldata->hostname, name);
                  if ( gmetad_config.write_rrds == 1 )
                     xmldata->rval = write_data_to_rrd(xmldata->sourcename,
                        xmldata->hostname, name, metricval, NULL,
                        xmldata->ds->step, xmldata->source.localtime, slope);
		  if (gmetad_config.carbon_server) // if the user has specified a carbon server, send the metric to carbon as well
                     carbon_ret=write_data_to_carbon(xmldata->sourcename, xmldata->hostname, name, metricval,xmldata->source.localtime);
            }
         metric->id = METRIC_NODE;
         metric->report_start = metric_report_start;
         metric->report_end = metric_report_end;


         edge = metric->stringslen;
         metric->name = addstring(metric->strings, &edge, name);
         metric->stringslen = edge;

         /* Set local idea of T0. */
         metric->t0 = xmldata->now;
         metric->t0.tv_sec -= metric->tn;

         /* Trim metric structure to the correct length. */
         hashval.size = sizeof(*metric) - GMETAD_FRAMESIZE + metric->stringslen;
         hashval.data = (void*) metric;

         /* Update full metric in cluster host table. */
         rdatum = hash_insert(&hashkey, &hashval, xmldata->host.metrics);
         if (!rdatum)
            {
               err_msg("Could not insert %s metric", name);
            }
      }

   /* Always update summary for numeric metrics. */
   if (do_summary)
      {
         summary = xmldata->source.metric_summary;
         hash_datum = hash_lookup(&hashkey, summary);
         if (!hash_datum)
            {
               if (!authority_mode(xmldata))
                  {
                     metric = &(xmldata->metric);
                     memset((void*) metric, 0, sizeof(*metric));
                     fillmetric(attr, metric, type);
                  }
               /* else we have already filled in the metric above. */
            }
         else
            {
               memcpy(&xmldata->metric, hash_datum->data, hash_datum->size);
               datum_free(hash_datum);
               metric = &(xmldata->metric);

               switch (tt->type)
                  {
                     case INT:
                     case UINT:
                     case FLOAT:
                        metric->val.d += (double)
                                strtod(metricval, (char**) NULL);
                        break;
                     default:
                        break;
                  }
            }

         metric->num++;
         metric->t0 = xmldata->now; /* tell cleanup thread we are using this */

         /* Trim metric structure to the correct length. Tricky. */
         hashval.size = sizeof(*metric) - GMETAD_FRAMESIZE + metric->stringslen;
         hashval.data = (void*) metric;

         /* Update metric in summary table. */
         rdatum = hash_insert(&hashkey, &hashval, summary);
         if (!rdatum) err_msg("Could not insert %s metric", name);
      }
   return 0;
}