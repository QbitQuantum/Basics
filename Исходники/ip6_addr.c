/**
 * Check whether "cp" is a valid ascii representation
 * of an IPv6 address and convert to a binary address.
 * Returns 1 if the address is valid, 0 if not.
 *
 * @param cp IPv6 address in ascii representation (e.g. "FF01::1")
 * @param addr pointer to which to save the ip address in network order
 * @return 1 if cp could be converted to addr, 0 on failure
 */
int
ip6addr_aton(const char *cp, ip6_addr_t *addr)
{
  u32_t addr_index, zero_blocks, current_block_index, current_block_value;
  const char *s;

  /* Count the number of colons, to count the number of blocks in a "::" sequence
     zero_blocks may be 1 even if there are no :: sequences */
  zero_blocks = 8;
  for (s = cp; *s != 0; s++) {
    if (*s == ':') {
      zero_blocks--;
    } else if (!isxdigit(*s)) {
      break;
    }
  }

  /* parse each block */
  addr_index = 0;
  current_block_index = 0;
  current_block_value = 0;
  for (s = cp; *s != 0; s++) {
    if (*s == ':') {
      if (addr) {
        if (current_block_index & 0x1) {
          addr->addr[addr_index++] |= current_block_value;
        }
        else {
          addr->addr[addr_index] = current_block_value << 16;
        }
      }
      current_block_index++;
      current_block_value = 0;
      if (current_block_index > 7) {
        /* address too long! */
        return 0;
      }
      if (s[1] == ':') {
        if (s[2] == ':') {
          /* invalid format: three successive colons */
          return 0;
        }
        s++;
        /* "::" found, set zeros */
        while (zero_blocks > 0) {
          zero_blocks--;
          if (current_block_index & 0x1) {
            addr_index++;
          } else {
            if (addr) {
              addr->addr[addr_index] = 0;
            }
          }
          current_block_index++;
          if (current_block_index > 7) {
            /* address too long! */
            return 0;
          }
        }
      }
    } else if (isxdigit(*s)) {
      /* add current digit */
      current_block_value = (current_block_value << 4) +
          (isdigit(*s) ? *s - '0' :
          10 + (islower(*s) ? *s - 'a' : *s - 'A'));
    } else {
      /* unexpected digit, space? CRLF? */
      break;
    }
  }

  if (addr) {
    if (current_block_index & 0x1) {
      addr->addr[addr_index++] |= current_block_value;
    }
    else {
      addr->addr[addr_index] = current_block_value << 16;
    }
  }

  /* convert to network byte order. */
  if (addr) {
    for (addr_index = 0; addr_index < 4; addr_index++) {
      addr->addr[addr_index] = htonl(addr->addr[addr_index]);
    }
  }

  if (current_block_index != 7) {
    return 0;
  }

  return 1;
}