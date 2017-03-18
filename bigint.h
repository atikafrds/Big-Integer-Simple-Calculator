#include <string>
#include <math.h>
#include <iostream>
#ifndef BigInt_H
#define BigInt_H
using namespace std;

class BigInt {
	private:
		string number;
	public:
		BigInt (); // ctor
		BigInt (string); // ctor
		BigInt (int); // ctor
		BigInt (const BigInt&); // cctor
		int toInt (const char); // fungsi konversi karakter ke integer
		char toChar (const int); // fungsi konversi integer ke karakter
		BigInt& operator= (const BigInt&); // operator =
		BigInt& operator+= (const BigInt&); // operator +=
		const BigInt operator+ (const BigInt&) const; // operator +
		BigInt& operator-= (const BigInt&); // operator -=
		const BigInt operator- (const BigInt&) const; // operator -
		BigInt& operator*= (const BigInt&); // operator *=
		const BigInt operator* (const BigInt&) const; // operator *
		int countFrontZero(BigInt); // fungsi untuk menghitung jumlah 0 di depan bilangan asli
		bool IsZero(BigInt); // fungsi is zero
		bool IsNeg(BigInt); // fungsi is negative
		bool IsEqual (BigInt, BigInt); // fungsi is equal
		bool IsBigger (BigInt, BigInt); // fungsi is bigger
		void PrintNumber(); // prosedur mencetak bilangan ke layar
};

#endif
