/* SPDX-License-Identifier: Apache-2.0
 * Copyright(c) 2023 Cisco Systems, Inc.
 */

#include <vppinfra/format.h>
#include <vppinfra/test/test.h>
#include <vppinfra/crypto/poly1305.h>

static const u8 text1[375] = {
  0x41, 0x6e, 0x79, 0x20, 0x73, 0x75, 0x62, 0x6d, 0x69, 0x73, 0x73, 0x69, 0x6f,
  0x6e, 0x20, 0x74, 0x6f, 0x20, 0x74, 0x68, 0x65, 0x20, 0x49, 0x45, 0x54, 0x46,
  0x20, 0x69, 0x6e, 0x74, 0x65, 0x6e, 0x64, 0x65, 0x64, 0x20, 0x62, 0x79, 0x20,
  0x74, 0x68, 0x65, 0x20, 0x43, 0x6f, 0x6e, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74,
  0x6f, 0x72, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63,
  0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x61, 0x73, 0x20, 0x61, 0x6c, 0x6c, 0x20,
  0x6f, 0x72, 0x20, 0x70, 0x61, 0x72, 0x74, 0x20, 0x6f, 0x66, 0x20, 0x61, 0x6e,
  0x20, 0x49, 0x45, 0x54, 0x46, 0x20, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x6e, 0x65,
  0x74, 0x2d, 0x44, 0x72, 0x61, 0x66, 0x74, 0x20, 0x6f, 0x72, 0x20, 0x52, 0x46,
  0x43, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x61, 0x6e, 0x79, 0x20, 0x73, 0x74, 0x61,
  0x74, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x6d, 0x61, 0x64, 0x65, 0x20, 0x77,
  0x69, 0x74, 0x68, 0x69, 0x6e, 0x20, 0x74, 0x68, 0x65, 0x20, 0x63, 0x6f, 0x6e,
  0x74, 0x65, 0x78, 0x74, 0x20, 0x6f, 0x66, 0x20, 0x61, 0x6e, 0x20, 0x49, 0x45,
  0x54, 0x46, 0x20, 0x61, 0x63, 0x74, 0x69, 0x76, 0x69, 0x74, 0x79, 0x20, 0x69,
  0x73, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x69, 0x64, 0x65, 0x72, 0x65, 0x64, 0x20,
  0x61, 0x6e, 0x20, 0x22, 0x49, 0x45, 0x54, 0x46, 0x20, 0x43, 0x6f, 0x6e, 0x74,
  0x72, 0x69, 0x62, 0x75, 0x74, 0x69, 0x6f, 0x6e, 0x22, 0x2e, 0x20, 0x53, 0x75,
  0x63, 0x68, 0x20, 0x73, 0x74, 0x61, 0x74, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x73,
  0x20, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65, 0x20, 0x6f, 0x72, 0x61, 0x6c,
  0x20, 0x73, 0x74, 0x61, 0x74, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x73, 0x20, 0x69,
  0x6e, 0x20, 0x49, 0x45, 0x54, 0x46, 0x20, 0x73, 0x65, 0x73, 0x73, 0x69, 0x6f,
  0x6e, 0x73, 0x2c, 0x20, 0x61, 0x73, 0x20, 0x77, 0x65, 0x6c, 0x6c, 0x20, 0x61,
  0x73, 0x20, 0x77, 0x72, 0x69, 0x74, 0x74, 0x65, 0x6e, 0x20, 0x61, 0x6e, 0x64,
  0x20, 0x65, 0x6c, 0x65, 0x63, 0x74, 0x72, 0x6f, 0x6e, 0x69, 0x63, 0x20, 0x63,
  0x6f, 0x6d, 0x6d, 0x75, 0x6e, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x73,
  0x20, 0x6d, 0x61, 0x64, 0x65, 0x20, 0x61, 0x74, 0x20, 0x61, 0x6e, 0x79, 0x20,
  0x74, 0x69, 0x6d, 0x65, 0x20, 0x6f, 0x72, 0x20, 0x70, 0x6c, 0x61, 0x63, 0x65,
  0x2c, 0x20, 0x77, 0x68, 0x69, 0x63, 0x68, 0x20, 0x61, 0x72, 0x65, 0x20, 0x61,
  0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x65, 0x64, 0x20, 0x74, 0x6f
};

const static struct
{
  char *name;
  u32 len;
  const u8 key[32];
  const u8 *msg;
  const u8 out[16];
} test_cases[] = {
  {
    .name = "test1",
    .len = 34,
    .out = { 0xa8, 0x06, 0x1d, 0xc1, 0x30, 0x51, 0x36, 0xc6, 0xc2, 0x2b, 0x8b,
	     0xaf, 0x0c, 0x01, 0x27, 0xa9 },
    .key = { 0x85, 0xd6, 0xbe, 0x78, 0x57, 0x55, 0x6d, 0x33, 0x7f, 0x44, 0x52,
	     0xfe, 0x42, 0xd5, 0x06, 0xa8, 0x01, 0x03, 0x80, 0x8a, 0xfb, 0x0d,
	     0xb2, 0xfd, 0x4a, 0xbf, 0xf6, 0xaf, 0x41, 0x49, 0xf5, 0x1b },
    .msg = (u8[34]){ 0x43, 0x72, 0x79, 0x70, 0x74, 0x6f, 0x67, 0x72, 0x61,
		     0x70, 0x68, 0x69, 0x63, 0x20, 0x46, 0x6f, 0x72, 0x75,
		     0x6d, 0x20, 0x52, 0x65, 0x73, 0x65, 0x61, 0x72, 0x63,
		     0x68, 0x20, 0x47, 0x72, 0x6f, 0x75, 0x70 },
  },
  {
    .name = "RFC8439 A3 TV1",
    .len = 64,
    .out = {},
    .key = {},
    .msg = (u8[64]){},
  },
  {
    .name = "RFC8439 A3 TV2",
    .len = sizeof (text1),
    .out = { 0x36, 0xe5, 0xf6, 0xb5, 0xc5, 0xe0, 0x60, 0x70, 0xf0, 0xef, 0xca,
	     0x96, 0x22, 0x7a, 0x86, 0x3e },
    .key = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	     0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0xe5, 0xf6, 0xb5, 0xc5, 0xe0,
	     0x60, 0x70, 0xf0, 0xef, 0xca, 0x96, 0x22, 0x7a, 0x86, 0x3e },
    .msg = text1,
  },
  {
    .name = "RFC8439 A3 TV3",
    .len = sizeof (text1),
    .out = { 0xf3, 0x47, 0x7e, 0x7c, 0xd9, 0x54, 0x17, 0xaf, 0x89, 0xa6, 0xb8,
	     0x79, 0x4c, 0x31, 0x0c, 0xf0

    },
    .key = { 0x36, 0xe5, 0xf6, 0xb5, 0xc5, 0xe0, 0x60, 0x70, 0xf0, 0xef, 0xca,
	     0x96, 0x22, 0x7a, 0x86, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },

    .msg = text1,
  },
  {
    .name = "RFC8439 A3 TV4",
    .len = 127,
    .key = { 0x1c, 0x92, 0x40, 0xa5, 0xeb, 0x55, 0xd3, 0x8a, 0xf3, 0x33, 0x88,
	     0x86, 0x04, 0xf6, 0xb5, 0xf0, 0x47, 0x39, 0x17, 0xc1, 0x40, 0x2b,
	     0x80, 0x09, 0x9d, 0xca, 0x5c, 0xbc, 0x20, 0x70, 0x75, 0xc0 },
    .msg =
      (u8[127]){
	0x27, 0x54, 0x77, 0x61, 0x73, 0x20, 0x62, 0x72, 0x69, 0x6c, 0x6c, 0x69,
	0x67, 0x2c, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x74, 0x68, 0x65, 0x20, 0x73,
	0x6c, 0x69, 0x74, 0x68, 0x79, 0x20, 0x74, 0x6f, 0x76, 0x65, 0x73, 0x0a,
	0x44, 0x69, 0x64, 0x20, 0x67, 0x79, 0x72, 0x65, 0x20, 0x61, 0x6e, 0x64,
	0x20, 0x67, 0x69, 0x6d, 0x62, 0x6c, 0x65, 0x20, 0x69, 0x6e, 0x20, 0x74,
	0x68, 0x65, 0x20, 0x77, 0x61, 0x62, 0x65, 0x3a, 0x0a, 0x41, 0x6c, 0x6c,
	0x20, 0x6d, 0x69, 0x6d, 0x73, 0x79, 0x20, 0x77, 0x65, 0x72, 0x65, 0x20,
	0x74, 0x68, 0x65, 0x20, 0x62, 0x6f, 0x72, 0x6f, 0x67, 0x6f, 0x76, 0x65,
	0x73, 0x2c, 0x0a, 0x41, 0x6e, 0x64, 0x20, 0x74, 0x68, 0x65, 0x20, 0x6d,
	0x6f, 0x6d, 0x65, 0x20, 0x72, 0x61, 0x74, 0x68, 0x73, 0x20, 0x6f, 0x75,
	0x74, 0x67, 0x72, 0x61, 0x62, 0x65, 0x2e },
    .out = { 0x45, 0x41, 0x66, 0x9a, 0x7e, 0xaa, 0xee, 0x61, 0xe7, 0x08, 0xdc,
	     0x7c, 0xbc, 0xc5, 0xeb, 0x62 },
  },
  {
    /* Test Vector #5:
     * If one uses 130-bit partial reduction, does the code handle the case
     * where partially reduced final result is not fully reduced? */
    .name = "RFC8439 A3 TV5",
    .len = 16,
    .key = { 2 },
    .msg = (u8[16]){ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
    .out = { 3 },
  },
  {
    /* Test Vector #6:
     * What happens if addition of s overflows modulo 2^128? */
    .name = "RFC8439 A3 TV6",
    .len = 16,
    .key = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	     0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
    .msg = (u8[16]){ 2 },
    .out = { 3 },
  },
  {
    /* Test Vector #7:
     * What happens if data limb is all ones and there is carry from lower
     * limb? */
    .name = "RFC8439 A3 TV7",
    .len = 48,
    .key = { 1 },
    .msg =
      (u8[48]){ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    .out = { 5 },
  },
  {
    /* Test Vector #8:
     * What happens if final result from polynomial part is exactly 2^130-5? */
    .name = "RFC8439 A3 TV8",
    .len = 48,
    .key = { 1 },
    .msg =
      (u8[48]){ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfe, 0xfe, 0xfe,
		0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
		0xfe, 0xfe, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
    .out = { 0 },
  },
  {
    /* Test Vector #9:
     * What happens if final result from polynomial part is exactly 2^130-6? */
    .name = "RFC8439 A3 TV9",
    .len = 16,
    .key = { 2 },
    .msg = (u8[16]){ 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
    .out = { 0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0xff, 0xff },
  },
  {
    /* Test Vector #10:
     * What happens if 5*H+L-type reduction produces 131-bit intermediate
     * result? */
    .name = "RFC8439 A3 TV10",
    .len = 64,
    .key = { [0] = 1, [8] = 4 },
    .msg =
      (u8[64]){ 0xE3, 0x35, 0x94, 0xD7, 0x50, 0x5E, 0x43, 0xB9, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x94, 0xD7, 0x50,
		0x5E, 0x43, 0x79, 0xCD, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00 },
    .out = { 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00,
	     0x00, 0x00, 0x00, 0x00, 0x00 },
  },
  {
    /* Test Vector #11:
     * What happens if 5*H+L-type reduction produces 131-bit final result? */
    .name = "RFC8439 A3 TV11",
    .len = 48,
    .key = { [0] = 1, [8] = 4 },
    .msg =
      (u8[48]){ 0xE3, 0x35, 0x94, 0xD7, 0x50, 0x5E, 0x43, 0xB9, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x94, 0xD7, 0x50,
		0x5E, 0x43, 0x79, 0xCD, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    .out = { 0x13 },
  }
};

static clib_error_t *
test_clib_poly1305 (clib_error_t *err)
{
  u8 out[16] = {};

  FOREACH_ARRAY_ELT (tc, test_cases)
    {
      clib_poly1305 (tc->key, tc->msg, tc->len, out);
      if (memcmp (out, tc->out, 16) != 0)
	err = clib_error_return (
	  err,
	  "\ntest:     %s"
	  "\nkey:      %U"
	  "\ndata:     %U"
	  "\nexp out:  %U"
	  "\ncalc out: %U\n",
	  tc->name, format_hexdump, tc->key, 32, format_hexdump, tc->msg,
	  tc->len, format_hexdump, tc->out, 16, format_hexdump, out, 16);
    }
  return err;
}

void __test_perf_fn
perftest_64byte (test_perf_t *tp)
{
  u32 n = tp->n_ops;
  u8 *m = test_mem_alloc_and_fill_inc_u8 (n * 64, 0, 0);
  u8 *k = test_mem_alloc_and_fill_inc_u8 (n * 32, 0, 0);
  u8 *t = test_mem_alloc (n * 16);

  test_perf_event_enable (tp);
  for (int i = 0; i < n; i++, t += 16, k += 32, m += 64)
    clib_poly1305 (k, m, 64, t);
  test_perf_event_disable (tp);
}

void __test_perf_fn
perftest_byte (test_perf_t *tp)
{
  u32 n = tp->n_ops;

  u8 *m = test_mem_alloc_and_fill_inc_u8 (n, 0, 0);
  u8 *k = test_mem_alloc_and_fill_inc_u8 (32, 0, 0);
  u8 *t = test_mem_alloc (16);

  test_perf_event_enable (tp);
  clib_poly1305 (k, m, n, t);
  test_perf_event_disable (tp);
}

REGISTER_TEST (clib_poly1305) = {
  .name = "clib_poly1305",
  .fn = test_clib_poly1305,
  .perf_tests = PERF_TESTS (
    { .name = "fixed size (64 bytes)", .n_ops = 1024, .fn = perftest_64byte },
    { .name = "variable size (per byte)",
      .n_ops = 16384,
      .fn = perftest_byte }),
};