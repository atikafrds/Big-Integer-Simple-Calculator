#include "BigInt.h"

BigInt::BigInt () {
	number = "";
}

BigInt::BigInt (string a) {
	number = "";
	number += a;
}

BigInt::BigInt (int n) {
	number = "";
	// asumsi masukan selalu kurang dari sama dengan n
	string temp = "";
	cin >> temp;
	if (temp.length() < n) {
		cout << "digit kurang dr n\n";
		long l = temp.length();
		for (int i = 1; i <= (l - n); i++) {
			temp = "0" + temp;
		}
	}
	number += temp;
}

BigInt::BigInt (const BigInt& b) {
	number = "";
	number += b.number;
}

int BigInt::toInt (const char c) {
	int x;
	switch (c) {
		case '1' : {
			x = 1;
			break; }
		case '2' : {
			x = 2;
			break; }
		case '3' : {
			x = 3;
			break; }
		case '4' : {
			x = 4;
			break; }
		case '5' : {
			x = 5;
			break; }
		case '6' : {
			x = 6;
			break; }
		case '7' : {
			x = 7;
			break; }
		case '8' : {
			x = 8;
			break; }
		case '9' : {
			x = 9;
			break; }
		default:
			x = 0;
		}
	return x;
}

char BigInt::toChar (const int x) {
	char c;
	switch (x) {
		case 1 : {
			c = '1';
			break; }
		case 2 : {
			c = '2';
			break; }
		case 3 : {
			c = '3';
			break; }
		case 4 : {
			c = '4';
			break; }
		case 5 : {
			c = '5';
			break; }
		case 6 : {
			c = '6';
			break; }
		case 7 : {
			c = '7';
			break; }
		case 8 : {
			c = '8';
			break; }
		case 9 : {
			c = '9';
			break; }
		default:
			c = '0';
		}
	return c;
}

BigInt& BigInt::operator= (const BigInt& b) {
	(*this).number.clear();
	for (int i = 0; i < b.number.length(); i++) {
		number += b.number[i];
	}
	return *this;
}

BigInt& BigInt::operator+= (const BigInt& b) {
	if (!IsNeg(*this)) {
		if (!IsNeg(b)) { // this positif dan b positif
			BigInt bTemp (b); // copy b ke temporary var
			long length1 = number.length();
			long length2 = bTemp.number.length();
			// menyamakan jumlah digit
			if (length1 < length2) {
				for (int i = 0; i < (length2 - length1); i++) {
					number = "0" + number;
				}
			} else if (length1 > length2) {
				for (int i = 0; i < (length1 - length2); i++) {
					bTemp.number = "0" + bTemp.number;
				}
			}
			int simpan = 0;
			int temp;
			// melakukan penjumlahan dari digit paling belakang
			for (int i = (number.length() - 1); i >= 0; i--) {
				temp = toInt(number[i]) + toInt(bTemp.number[i]) + simpan;
				number[i] = toChar(temp % 10);
				simpan = temp / 10;
			}
			number = toChar(simpan) + number;
			BigInt last;
			for (int i = countFrontZero(*this); i < number.length(); i++) {
				last.number += number[i];
			}
			(*this) = last;
			return *this;
		} else { // this positif dan b negatif
			BigInt bPos;
			// copy b ke temporary var
			for (int i = countFrontZero(b) + 1; i < b.number.length(); i++) {
				bPos.number += b.number[i];
			}
			// mengubah operasi a+(-b) menjadi a-b
			return ((*this) -= bPos);
		}
	} else {
		if (!IsNeg(b)) { // this negatif dan b positif
			// mengubah operasi menjadi pengurangan untuk memudahkan
			// hukum komutatif penjumlahan
			BigInt aPos;
			// menyimpan nilai (-1) * this ke dalam variabel
			for (int i = countFrontZero(*this) + 1; i < number.length(); i++) {
				aPos.number += number[i];
			}
			// copy b ke temporary var
			BigInt bTemp;
			for (int i = countFrontZero(b) + 1; i < b.number.length(); i++) {
				bTemp.number += b.number[i];
			}
			// operasi yang mulanya (-a)+b menjadi b-a
			bTemp -= aPos;
			*this = bTemp;
			return *this;
		} else { // this negatif dan b negatif
			// menyimpan nilai (-1) * this ke dalam variabel
			BigInt aPos;
			for (int i = countFrontZero(*this) + 1; i < number.length(); i++) {
				aPos.number += number[i];
			}
			// menyimpan nilai (-1) * b ke dalam variabel
			BigInt bPos;
			for (int i = countFrontZero(b) + 1; i < b.number.length(); i++) {
				bPos.number += b.number[i];
			}
			// mengubah operasi (-a)+(-b) menjadi -(a+b)
			aPos += bPos;
			number = "-" + aPos.number;
			return *this;
		}
	}
}

const BigInt BigInt::operator+ (const BigInt& B) const {
	return (BigInt(*this) += B);
}

BigInt& BigInt::operator-= (const BigInt& b) {
	if (!IsNeg(*this)) {
		if (!IsNeg(b)) { // this positif dan b positif
			if (IsEqual(*this, b)) {
                // pengurangan dua bilangan yang sama akan menghasilkan 0
				number = "";
				number += "0";
				return *this;
			} else if (IsBigger((*this), b)) {
				BigInt bTemp (b);
				long length1 = number.length();
				long length2 = bTemp.number.length();
				// menyamakan jumlah digit
				if (length1 < length2) {
					for (int i = 0; i < (length2 - length1); i++) {
						number = "0" + number;
					}
				} else if (length1 > length2) {
					for (int i = 0; i < (length1 - length2); i++) {
						bTemp.number = "0" + bTemp.number;
					}
				}
				int temp;
				int l = number.length();
				// melakukan pengurangan dari digit paling belakang
				for (int i = (l - 1); i >= 0; i--) {
					if (toInt(number[i]) < toInt(bTemp.number[i])) {
						bool found = false;
						int j = i - 1;
						while ((j >= 0) && (!found)) {
							if (toInt(number[j]) != 0) {
								found = true;
								number[j] = toChar(toInt(number[j]) - 1);
							} else {
								number[j] = toChar(9);
								j--;
							}
						}
						temp = toInt(number[i]) + 10 - toInt(bTemp.number[i]);
						number[i] = toChar(temp);
					} else {
						temp = toInt(number[i]) - toInt(bTemp.number[i]);
						number[i] = toChar(temp);
					}
				}
				int i = countFrontZero(*this);
				int len = number.length();
				BigInt intTemp;
				for (int j = i; j < len; j++) {
					intTemp.number += number[j];
				}
				*this = intTemp;
				return *this;
			} else { // this lebih kecil dari b
				BigInt aTemp (*this);
				BigInt bTemp (b);
                // mengubah operasi a-b menjadi -(b-a)
				bTemp -= aTemp;
				number = "-" + bTemp.number;
				return *this;
			}
		} else { // this positif dan b negatif
			BigInt bPos;
			for (int i = countFrontZero(b) + 1; i < b.number.length(); i++) {
				bPos.number += b.number[i];
			}
			// mengubah operasi a-(-b) menjadi a+b
			return ((*this) += bPos);
		}
	} else { // this negatif
		if (!IsNeg(b)) { // this negatif dan b positif
			BigInt aPos;
			for (int i = countFrontZero(*this) + 1; i < number.length(); i++) {
				aPos.number += number[i];
			}
			BigInt bPos;
			for (int i = countFrontZero(b); i < b.number.length(); i++) {
				bPos.number += b.number[i];
			}
            // mengubah operasi (-a)-b menjadi -(a+b)
			aPos += bPos;
			number = "";
			number += "-" + aPos.number;
			return *this;
		} else { // this negatif dan b negatif
			BigInt aPos;
			for (int i = countFrontZero(*this) + 1; i < number.length(); i++) {
				aPos.number += number[i];
			}
			BigInt bPos;
			for (int i = countFrontZero(b) + 1; i < b.number.length(); i++) {
				bPos.number += b.number[i];
			}
			bPos -= aPos;
			*this = bPos;
			return *this;
		}
	}
}

const BigInt BigInt::operator- (const BigInt& B) const {
	return (BigInt(*this) -= B);
}

BigInt& BigInt::operator*= (const BigInt& B1) {
	BigInt B (B1);
	if (IsZero(*this) || IsZero(B1)) {
		number = "";
		number += "0";
		return *this;
	} else {
		long length1 = number.length();
		long length2 = B.number.length();
		if (length1 < length2) {
			for (int i = 0; i < (length2 - length1); i++) {
				number = "0" + number;
			}
		} else if (length1 > length2) {
			for (int i = 0; i < (length1 - length2); i++) {
				B.number = "0" + B.number;
			}
		}
		if ((number.length() == 1) && (B.number.length() == 1)) {
			int temp = toInt(number[0]) * toInt(B.number[0]);
			if (temp > 9) {
				char x = toChar(temp/10);
				char y = toChar(temp%10);
				number = "";
				number = number + x + y;
			} else {
				number = "";
				number += toChar(temp);
			}
			return *this;
		} else {
			BigInt a, b, c, d;
			int s;
			s = number.length() / 2;
			for (int i = 0; i < s; i++) {
				a.number += number[i];
			}
			for (int i = s; i < number.length(); i++) {
				b.number += number[i];
			}
			for (int i = 0; i < s; i++) {
				c.number += B.number[i];
			}
			for (int i = s; i < B.number.length(); i++) {
				d.number += B.number[i];
			}
			BigInt p = (a * c);
			BigInt q = (b * d);
			BigInt r = ((a + b) * (c + d));
			BigInt t = ((r - p) - q);
			for (int i = 0; i < 2 * b.number.length(); i++) {
				p.number += "0";
			}
			for (int i = 0; i < b.number.length(); i++) {
				t.number += "0";
			}
			*this = (p + t) + q;
			BigInt last;
			for (int i = countFrontZero(*this); i < number.length(); i++) {
				last.number += number[i];
			}
			*this = last;
			return *this;
		}
	}
}

const BigInt BigInt::operator* (const BigInt& B) const {
	return BigInt(*this) *= B;
}

/* Mengembalikan jumlah bilangan 0 yang ada sebelum bilangan asli */
int BigInt::countFrontZero(BigInt b) {
	int count = 0;
	bool stop = false;
	int i;
	if (IsNeg(b)) {
		i = 1; // asumsi semua bilangan negatif tanda '-' terletak pada string indeks ke-0
	} else {
		i = 0;
	}
	while ((i < b.number.length()) && (!stop)) {
		if (b.number[i] == '0') {
			count++;
		} else {
			stop = true;
		}
		i++;
	}
	return count;
}

/* Mengembalikan apakah b adalah bilangan 0 */
bool BigInt::IsZero(BigInt b) {
	if (IsNeg(b)) {
		return false;
	} else {
		bool zero = true;
		int i = 0;
		while ((i < b.number.length()) && (zero)) {
			if (b.number[i] != '0') {
				zero = false;
			}
			i++;
		}
		return zero;
	}
}

/* Mengembalikan apakah bilangan b negatif */
bool BigInt::IsNeg(BigInt b) {
	if (b.number[0] == '-') {
		return true;
	} else {
		return false;
	}
}

/* Mengembalikan apakah integer a dan b adalah bilangan yang sama */
bool BigInt::IsEqual (BigInt a, BigInt b) {
	if ((a.number.length() - countFrontZero(a)) == (b.number.length() - countFrontZero(b))) {
		int i, j;
		if (IsNeg(a)) {
			i = countFrontZero(a) + 1;
		} else {
			i = countFrontZero(a);
		}
		if (IsNeg(b)) {
			j = countFrontZero(b) + 1;
		} else {
			j = countFrontZero(b);
		}
		bool same = true;
		while (same && (i < a.number.length()) && (j < b.number.length())) {
			if (a.number[i] != b.number[j]) {
				same = false;
			}
			i++;
			j++;
		}
		return same;
	} else {
		return false;
	}
}

/* MENGEMBALIKAN APAKAH A LEBIH BESAR DARI B */
bool BigInt::IsBigger (BigInt a, BigInt b) {
	if (IsNeg(a)) {
		if (IsNeg(b)) {
			if ((a.number.length() - countFrontZero(a)) > (b.number.length() - countFrontZero(b))) {
				return false;
			} else if ((a.number.length() - countFrontZero(a)) < (b.number.length() - countFrontZero(b))) {
				return true;
			} else {
				bool bigger;
				bool stop = false;
				int i = countFrontZero(a) + 1; // kenapa plus 1 karena tanda '-' nya diskip juga
				while ((i < a.number.length()) && (!stop)) {
					if (a.number[i] != b.number[i]) {
						stop = true;
					} else {
						i++;
					}
				}
				if (stop) {
					if (a.number[i] > b.number[i]) {
						bigger = false;
					} else {
						bigger = true;
					}
					return bigger;
				} else {
					return false;
				}
			}
		} else {
			return false;
		}
	} else { // a positif
		if (IsNeg(b)) {
			return true;
		} else { // b positif
			if ((a.number.length() - countFrontZero(a)) > (b.number.length() - countFrontZero(b))) {
				return true;
			} else if ((a.number.length() - countFrontZero(a)) < (b.number.length() - countFrontZero(b))) {
				return false;
			} else {
				bool bigger;
				bool stop = false;
				int i = countFrontZero(a);
				while ((i < a.number.length()) && (!stop)) {
					if (a.number[i] != b.number[i]) {
						stop = true;
					} else {
						i++;
					}
				}
				if (stop) {
					if (a.number[i] > b.number[i]) {
						bigger = true;
					} else {
						bigger = false;
					}
					return bigger;
				} else {
					return false;
				}
			}
		}
	}
}

/* Prosedur untuk mencetak big int ke layar */
void BigInt::PrintNumber() {
	if (IsZero(*this)) {
		cout << "0";
	} else if (IsNeg(number)) {
		cout << number[0];
		int i = 1;
		while (number[i] == '0') {
			i++;
		}
		for (int j = i; j < number.length(); j++) {
			cout << number[j];
		}
	} else {
		int i = 0;
		while (number[i] == '0') {
			i++;
		}
		for (int j = i; j < number.length(); j++) {
			cout << number[j];
		}
	}
	cout << endl;
}
