// RUN: %clang_cc1 -fno-rtti -fms-extensions -emit-llvm-only -triple i686-pc-win32 -fdump-record-layouts -fsyntax-only %s 2>&1 \
// RUN:            | FileCheck %s
// RUN: %clang_cc1 -fno-rtti -fms-extensions -emit-llvm-only -triple x86_64-pc-win32 -fdump-record-layouts -fsyntax-only %s 2>/dev/null \
// RUN:            | FileCheck %s -check-prefix CHECK-X64

extern "C" int printf(const char *fmt, ...);

struct B0 {
	int a;
	B0() : a(0xf00000B0) {}
	virtual void f() { printf("B0"); }
};

struct __declspec(align(16)) B1 {
	int a;
	B1() : a(0xf00000B1) {}
	virtual void f() { printf("B1"); }
};

struct __declspec(align(16)) Align16 {};
struct __declspec(align(32)) Align32 {};
struct VAlign16 : virtual Align16 {};
struct VAlign32 : virtual Align32 {};

struct A : virtual B0, virtual B1 {
	int a;
	A() : a(0xf000000A) {}
	virtual void f() { printf("A"); }
	virtual void g() { printf("A"); }
};
