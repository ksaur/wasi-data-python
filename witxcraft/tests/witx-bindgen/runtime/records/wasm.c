#include <assert.h>
#include <imports.h>
#include <exports.h>

void exports_test_imports() {
  {
    uint8_t a;
    uint16_t b;
    imports_multiple_results(&a, &b);
    assert(a == 4);
    assert(b == 5);
  }

  imports_tuple2_u8_u32_t input;
  input.f0 = 1;
  input.f1 = 2;
  uint32_t a;
  uint8_t b;
  imports_swap_tuple(&input, &a, &b);
  assert(a == 2);
  assert(b == 1);

  assert(imports_roundtrip_flags1(IMPORTS_F1_A) == IMPORTS_F1_A);
  assert(imports_roundtrip_flags1(0) == 0);
  assert(imports_roundtrip_flags1(IMPORTS_F1_B) == IMPORTS_F1_B);
  assert(imports_roundtrip_flags1(IMPORTS_F1_A | IMPORTS_F1_B) == (IMPORTS_F1_A | IMPORTS_F1_B));

  assert(imports_roundtrip_flags2(IMPORTS_F2_C) == IMPORTS_F2_C);
  assert(imports_roundtrip_flags2(0) == 0);
  assert(imports_roundtrip_flags2(IMPORTS_F2_D) == IMPORTS_F2_D);
  assert(imports_roundtrip_flags2(IMPORTS_F2_C | IMPORTS_F2_E) == (IMPORTS_F2_C | IMPORTS_F2_E));

  imports_flag8_t flag8;
  imports_flag16_t flag16;
  imports_flag32_t flag32;
  imports_flag64_t flag64;
  imports_roundtrip_flags3(IMPORTS_FLAG8_B0, IMPORTS_FLAG16_B1, IMPORTS_FLAG32_B2, IMPORTS_FLAG64_B3,
      &flag8, &flag16, &flag32, &flag64);
  assert(flag8 == IMPORTS_FLAG8_B0);
  assert(flag16 == IMPORTS_FLAG16_B1);
  assert(flag32 == IMPORTS_FLAG32_B2);
  assert(flag64 == IMPORTS_FLAG64_B3);

  {
    imports_r1_t a, b;
    a.a = 8;
    a.b = 0;
    imports_roundtrip_record1(&a, &b);
    assert(b.a == 8);
    assert(b.b == 0);
  }

  {
    imports_r1_t a, b;
    a.a = 0;
    a.b = IMPORTS_F1_A | IMPORTS_F1_B;
    imports_roundtrip_record1(&a, &b);
    assert(b.a == 0);
    assert(b.b == (IMPORTS_F1_A | IMPORTS_F1_B));
  }

  imports_tuple0_t t0;
  imports_tuple0(&t0);

  imports_tuple1_u8_t t1;
  t1.f0 = 1;
  uint8_t ret;
  imports_tuple1(&t1, &ret);
  assert(ret == 1);
}

void exports_multiple_results(uint8_t *ret0, uint16_t *ret1) {
  *ret0 = 100;
  *ret1 = 200;
}

void exports_swap_tuple(exports_tuple2_u8_u32_t *a, uint32_t *ret0, uint8_t *ret1) {
  *ret0 = a->f1;
  *ret1 = a->f0;
}

exports_f1_t exports_roundtrip_flags1(exports_f1_t a) {
  return a;
}

exports_f2_t exports_roundtrip_flags2(exports_f2_t a) {
  return a;
}

void exports_roundtrip_flags3(exports_f8_t a, exports_f16_t b, exports_f32_t c, exports_f64_t d, exports_f8_t *ret0, exports_f16_t *ret1, exports_f32_t *ret2, exports_f64_t *ret3) {
  *ret0 = a;
  *ret1 = b;
  *ret2 = c;
  *ret3 = d;
}

void exports_roundtrip_record1(exports_r1_t *a, exports_r1_t *ret0) {
  *ret0 = *a;
}

void exports_tuple0(exports_tuple0_t *a) {
}

void exports_tuple1(exports_tuple1_u8_t *a, uint8_t *ret0) {
  *ret0 = a->f0;
}
