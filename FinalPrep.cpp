#include <iostream>
#include <string>
#include <new>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

bool die(const string & msg) { cout << "Fatal error:: " << msg << endl; exit(EXIT_FAILURE); }

bool three(const unsigned arr[], const unsigned els);

void ir(const unsigned n) { if (n < 0 || n > 10) { die("invalid n value"); } };

unsigned * cull(unsigned & elsRet, const unsigned arr[], const unsigned els, unsigned ptr(unsigned n));

unsigned fun(unsigned n) {
	return ( n /2 );
}

class repStr {
private: 
	unsigned _n;
	string _s;
public:
	repStr(unsigned n, string s) : _n(n), _s(s) {
		ir(n);
	};

	unsigned getN() const { return _n; };
	string getS() const { return _s; };

	repStr setN(unsigned n) { ir(n); _n = n; return *this; }
	repStr setS(string s) { _s = s; return *this; }

	unsigned size() const { return (_s.length() * _n); }

	friend ostream & operator<<(ostream &out, const repStr & v) {
		for (unsigned i = 0; i < v._n; i++) {
			cout << v._s;
		}
		cout << endl;
		return out;
	}

	repStr operator+(const repStr & rhs) {
		repStr nv(_n > rhs._n ? _n : rhs._n, _s + rhs._s);
		return nv;
	}

};

repStr sum(const repStr arr[], const unsigned els);

class repStr2 : public repStr {
private: string _pre, _suff;
public:
	repStr2(unsigned n, string s, string pre, string suff) : repStr(n, s), _pre(pre), _suff(suff) {};

	string getPre() const { return _pre; };
	string getSuff() const { return _suff; };

	repStr setPre(string pre) { _pre = pre; return *this; }
	repStr setSuff(string suff) { _suff = suff; return *this; }

	friend ostream & operator<<(ostream &out, const repStr2 & v) {
		cout << v._pre;
		for (unsigned i = 0; i < v.getN(); i++) {
			cout << v.getS();
		}
		cout << v._suff;
		cout << endl;
		return out;
	}

	unsigned size() const { 
		return (_pre.length() + (getS().length() * getN())+ _suff.length()); }
};

int main() {
	unsigned arr[] = { 1,2,3,3,3,4,5,6 };
	bool v = three(arr, 8);
	if (v == true) {
		cout << "lookin slick, 3 in a row\n";
	}
	else {
		cout << "no way jose\n";
	}

	repStr t(3, "blah");
	cout << t;

	repStr s(2, "flip");
	repStr z = t + s;
	cout << z;

	repStr arrT[] = { t, s, z };
	cout << sum(arrT, 3);
	
	repStr2 j(3, "blah", "aa", "zz");
	cout << j;
	cout << j.size() << endl;

	unsigned arrs[] = { 3,5,7,9,2,4,6,8 };
	unsigned elsRett = 0;
	unsigned * p;
	p = cull(elsRett, arrs, 8, fun);
	
	for (unsigned i = 0; i < elsRett; i++) {
		cout << p[i] << " ";
	}
	cout << endl;

	delete[] p;
}

bool three(const unsigned arr[], const unsigned els) {
	unsigned y = 0;
	unsigned prev;
	for (unsigned i = 0; i < els; i++) {
		if (arr[i] == arr[i+1] && arr[i+1] == arr[i+2] ) {
			y++;
		}
		prev = arr[i];
	}
	if (y > 0) {
		return true;
	}
	else if (y <= 0) {
		return false;
	}
}

repStr sum(const repStr arr[], const unsigned els) {
	string n = "";
	unsigned max = 0;
	for (unsigned i = 0; i < els; i++) {
		n += arr[i].getS();
		if (arr[i].getN() > max) { max = arr[i].getN(); };
	}

	repStr ni(max, n);
	return ni;
}

unsigned * cull(unsigned & elsRet, const unsigned arr[], const unsigned els, unsigned f(unsigned n)) {
	for (unsigned i = 0; i < els; i++) {
		if (arr[i] > f(arr[i])) {
			elsRet++;
		}
	}

	unsigned * nv = nullptr;
	try {
		nv = new unsigned[elsRet];
	}
	catch (const bad_alloc &) {
		die("allocation failure");
	}
	unsigned j = 0;
	for (unsigned i = 0; i < els; i++) {
		if (arr[i] > f(arr[i])) {
			nv[j] = arr[i];
			j++;
		}
	}
	return nv;
}