static int should_filter_query(ns_msg msg, struct in_addr dns_addr) {
  ns_rr rr;
  int rrnum, rrmax;
  void *r;
  // TODO cache result for each dns server
  int dns_is_chn = 0;
  int dns_is_foreign = 0;
  if (chnroute_file && (dns_servers_len > 1)) {
    dns_is_chn = test_ip_in_list(dns_addr, &chnroute_list);
    dns_is_foreign = !dns_is_chn;
  }
  rrmax = ns_msg_count(msg, ns_s_an);
  if (rrmax == 0) {
    if (compression) {
      // Wait for foreign dns
      if (dns_is_chn) {
        return 1;
      } else {
        return 0;
      }
    }
    return -1;
  }
  for (rrnum = 0; rrnum < rrmax; rrnum++) {
    if (local_ns_parserr(&msg, ns_s_an, rrnum, &rr)) {
      ERR("local_ns_parserr");
      return 0;
    }
    u_int type;
    const u_char *rd;
    type = ns_rr_type(rr);
    rd = ns_rr_rdata(rr);
    if (type == ns_t_a) {
      if (verbose)
        printf("%s, ", inet_ntoa(*(struct in_addr *)rd));
      if (!compression) {
        r = bsearch(rd, ip_list.ips, ip_list.entries, sizeof(struct in_addr),
                    cmp_in_addr);
        if (r) {
          return 1;
        }
      }
      if (test_ip_in_list(*(struct in_addr *)rd, &chnroute_list)) {
        // result is chn
        if (dns_is_foreign) {
          if (bidirectional) {
            // filter DNS result from foreign dns if result is inside chn
            return 1;
          }
        }
      } else {
        // result is foreign
        if (dns_is_chn) {
          // filter DNS result from chn dns if result is outside chn
          return 1;
        }
      }
    } else if (type == ns_t_aaaa) {
      if (dns_is_chn) {
        // filter DNS result from chn dns if dns is inside chn
        return 1;
      }
    } else if (type == type == ns_t_ptr) {
      // if we've got a PTR result, pass
      return 0;
    }
  }
  if (rrmax == 1) {
    if (compression) {
      return 0;
    } else {
      return -1;
    }
  }
  return 0;
}