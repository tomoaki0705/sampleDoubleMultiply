#include <iostream>
#include <stdint.h>

//#pragma GCC optimize ("-ffp-contract=off")

union float64_union_t {
	double d;
	uint64_t u;
};

int main(int argc, char**argv)
{
	using namespace std;

	float64_union_t s;
	float64_union_t c;
	float64_union_t a;
	float64_union_t b;

	s.u = 0x3feffffff965afe6;
	c.u = 0x3f248e846144bf02;
	a.u = 0x400cceca85a75732;
	b.u = 0x3f42818b81589e0e;

	cout << "s:" << s.d << endl;
	cout << "c:" << c.d << endl;
	cout << "a:" << a.d << endl;
	cout << "b:" << b.d << endl;

	float64_union_t t0;
	float64_union_t t1;

	t0.d = s.d*b.d;
	t1.d = c.d*a.d;

	cout << "s*b: " << t0.d << endl;
	cout << "c*a: " << t1.d << endl;

	cout << "s*b: 0x" << hex << t0.u << dec << endl;
	cout << "c*a: 0x" << hex << t1.u << dec << endl;

	float64_union_t t2;

	t2.d = t0.d - t1.d;
	cout << "diff: "   << hex << t2.d << dec << endl;
	cout << "diff: 0x" << hex << t2.u << dec << endl;

	float64_union_t dd;
	dd.d = __builtin_fma(c.d, a.d, -t0.d);
	cout << "diff: "   << hex << dd.d << dec << endl;
	cout << "diff: 0x" << hex << dd.u << dec << endl;

	t2.d = s.d * b.d - c.d * a.d;
	cout << "diff: "   << hex << t2.d << dec << endl;
	cout << "diff: 0x" << hex << t2.u << dec << endl;

//	4 5 0   0x400cceca85a459fe      0x3f42818b574ceca1      0.000156835     1
//	4 5 1   0x40062cd191c81ec0      0x3f3c7d8b20b823f2      0.000156835     1
//	4 5 2   0xc01a5ac3223c0827      0xbf50ee19b31a4055      0.000156835     1
//	4 5 3   0xc00c75557ade72ea      0xbf424813e59e3fca      0.000156835     1
//	4 5 4   0xc00646f28863f8cb      0xbf3c9f1d41818dd9      0.000156835     1
//	4 5 5   0x401a79c39b157f27      0x3f5102042d61deec      0.000156835     1

	return 0;
}
