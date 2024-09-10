/* Test the 256-bit form */
static void
avx2_test_palignr256 (__m256i t1, __m256i t2, unsigned int imm, __m256i * r)
{
  switch (imm)
    {
    case 0:
      *r = _mm256_alignr_epi8 (t1, t2, 0);
      break;
    case 1:
      *r = _mm256_alignr_epi8 (t1, t2, 1);
      break;
    case 2:
      *r = _mm256_alignr_epi8 (t1, t2, 2);
      break;
    case 3:
      *r = _mm256_alignr_epi8 (t1, t2, 3);
      break;
    case 4:
      *r = _mm256_alignr_epi8 (t1, t2, 4);
      break;
    case 5:
      *r = _mm256_alignr_epi8 (t1, t2, 5);
      break;
    case 6:
      *r = _mm256_alignr_epi8 (t1, t2, 6);
      break;
    case 7:
      *r = _mm256_alignr_epi8 (t1, t2, 7);
      break;
    case 8:
      *r = _mm256_alignr_epi8 (t1, t2, 8);
      break;
    case 9:
      *r = _mm256_alignr_epi8 (t1, t2, 9);
      break;
    case 10:
      *r = _mm256_alignr_epi8 (t1, t2, 10);
      break;
    case 11:
      *r = _mm256_alignr_epi8 (t1, t2, 11);
      break;
    case 12:
      *r = _mm256_alignr_epi8 (t1, t2, 12);
      break;
    case 13:
      *r = _mm256_alignr_epi8 (t1, t2, 13);
      break;
    case 14:
      *r = _mm256_alignr_epi8 (t1, t2, 14);
      break;
    case 15:
      *r = _mm256_alignr_epi8 (t1, t2, 15);
      break;
    case 16:
      *r = _mm256_alignr_epi8 (t1, t2, 16);
      break;
    case 17:
      *r = _mm256_alignr_epi8 (t1, t2, 17);
      break;
    case 18:
      *r = _mm256_alignr_epi8 (t1, t2, 18);
      break;
    case 19:
      *r = _mm256_alignr_epi8 (t1, t2, 19);
      break;
    case 20:
      *r = _mm256_alignr_epi8 (t1, t2, 20);
      break;
    case 21:
      *r = _mm256_alignr_epi8 (t1, t2, 21);
      break;
    case 22:
      *r = _mm256_alignr_epi8 (t1, t2, 22);
      break;
    case 23:
      *r = _mm256_alignr_epi8 (t1, t2, 23);
      break;
    case 24:
      *r = _mm256_alignr_epi8 (t1, t2, 24);
      break;
    case 25:
      *r = _mm256_alignr_epi8 (t1, t2, 25);
      break;
    case 26:
      *r = _mm256_alignr_epi8 (t1, t2, 26);
      break;
    case 27:
      *r = _mm256_alignr_epi8 (t1, t2, 27);
      break;
    case 28:
      *r = _mm256_alignr_epi8 (t1, t2, 28);
      break;
    case 29:
      *r = _mm256_alignr_epi8 (t1, t2, 29);
      break;
    case 30:
      *r = _mm256_alignr_epi8 (t1, t2, 30);
      break;
    case 31:
      *r = _mm256_alignr_epi8 (t1, t2, 31);
      break;
    default:
      *r = _mm256_alignr_epi8 (t1, t2, 32);
      break;
    }
}