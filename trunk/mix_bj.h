/*
	Robert Jenkins' 96 bit Mix Function
	Source: http://www.concentric.net/~Ttwang/tech/inthash.htm; http://www.burtleburtle.net/bob/hash/doobs.html
	Source code: http://www.burtleburtle.net/bob/c/lookup3.c
*/
inline unsigned long rot(unsigned long x, unsigned long k) {
	return ((x<<k) | (x>>(32-k)));
}
unsigned long mix_1ed(register unsigned long a, register unsigned long b, register unsigned long c) {
	a -= c;  a ^= rot(c, 4);  c += b;
	b -= a;  b ^= rot(a, 6);  a += c;
	c -= b;  c ^= rot(b, 8);  b += a; 
	a -= c;  a ^= rot(c,16);  c += b;
	b -= a;  b ^= rot(a,19);  a += c;
	c -= b;  c ^= rot(b, 4);  b += a;
	c ^= b; c -= rot(b,14);
	a ^= c; a -= rot(c,11);
	b ^= a; b -= rot(a,25);
	c ^= b; c -= rot(b,16);
	a ^= c; a -= rot(c,4);
	b ^= a; b -= rot(a,14);
	c ^= b; c -= rot(b,24);
	return c;
}