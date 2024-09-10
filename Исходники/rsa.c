rsa_priv::rsa_priv (const bigint &n1, const bigint &n2)
  : rsa_pub (n1 * n2), p (n1), q (n2)
{
  bigint p1 (n1-1);
  bigint q1 (n2-1);
  phin = p1 * q1;
  d = mod (invert (e, phin), phin);

  /* Precompute for CRT */
  dp = mod (d, p1);
  dq = mod (d, q1);
  pinvq = mod (invert (p, q), q);

  // warn << "p " << p.getstr () << "\n";
  // warn << "q " << q.getstr () << "\n";
  // warn << "e " << e.getstr << "\n";
  // warn << "d " << d.getstr << "\n";

  init ();
}