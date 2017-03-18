#include "bigint.h"
#include <windows.h>
#include <math.h>
using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

// Prosedur untuk memulai penghitungan durasi operasi
void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
	cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

// Prosedur untuk mendapat waktu dari sistem
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

int main() {
	int n;
	string a, b;

	cout << endl;
	cout << "---------------------------------------------" << endl;
	cout << "  B I G  I N T E G E R  C A L C U L A T O R  " << endl;
	cout << "---------------------------------------------" << endl << endl;

	cout << "Masukkan n: ";
	cin >> n;
	cout << "Masukkan big integer A: ";
	BigInt A(n);
	cout << "Masukkan big integer B: ";
	BigInt B(n);

	cout << endl << "n = " << n << endl;
	cout << "BigInt A = ";
	A.PrintNumber();
	cout << "BigInt B = ";
	B.PrintNumber();
	cout << endl;

	StartCounter();
	BigInt C = A + B;
	double dur_plus = GetCounter();
	cout << "A + B = ";
	C.PrintNumber();
	cout << "Durasi Operasi Penjumlahan: " << dur_plus << " microseconds" << endl;
	cout << "Jumlah Operasi Penjumlahan: " << n << " kali" << endl << endl;

	StartCounter();
	BigInt D = A - B;
	double dur_sub = GetCounter();
	cout << "A - B = ";
	D.PrintNumber();
	cout << "Durasi Operasi Pengurangan: " << dur_sub << " microseconds" << endl;
	cout << "Jumlah Operasi Pengurangan: " << n << " kali" << endl << endl;

	StartCounter();
	BigInt E = A * B;
	double dur_mul = GetCounter();
	cout << "A * B = ";
	E.PrintNumber();
	cout << "Durasi Operasi Perkalian: " << dur_mul << " microseconds" << endl;
	cout << "Jumlah Operasi Perkalian: " << (int) pow(n,(log2(3))) << " kali" << endl << endl;

	return 0;
}
