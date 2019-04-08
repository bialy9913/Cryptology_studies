#include<iostream>
#include<time.h>
#include<windows.h>
#include<string>
#include<math.h>

using namespace std;

int losuj_liczbe() {
	srand(time(NULL));
	return rand() %199 +2;
}

int losuj_liczbe_zakres(int koc) {
	srand(time(NULL));
	return rand() % (koc-1) + 2;
}

int licz_modulo(int a, int b) {
	int r = a % b;
	if (r < 0)
	{
		r += b;
	}
	return r;
}

int losuj_liczbe_pierwsza(int n) {
	int i, p,g;
	bool t=false;
	p = n;

	while (t!=true)
	{
		t = true;
		g = sqrt(p);
		for (i = 2; i <= g; i++)
			if (p % i == 0)
			{
				t = false;
				break;
			}
		p++;
	}
	return p-1;
}

int modulo_dla_duzych(int liczba,int potega,int modulo) {
	int wynik = 1;
	for (int i = 1; i <= potega; i++) {
		wynik *= liczba;
		wynik = wynik % modulo;
	}
	return wynik;
}

int losuj_e(int n) {
	int tmp, p=2,i=2;
	bool wzglednie = false;
	while (wzglednie != true) {
		tmp = losuj_liczbe_zakres(n); 
			wzglednie = true;
			while (p < tmp) {
				p = losuj_liczbe_pierwsza(i);
				if (tmp%p == 0 && n%p == 0) {
					wzglednie = false;
					i = 2;
					p = 2;
					break;
				}
				if (p > i) i = p + 1; //eliminating unnecessary checks for  i=5 and i=4
				else i++;
			}
	}
	return tmp;
}

void szyfruj(int * tablica, int *out, int e, int n) {
	int tmp;
	for (int i = 0; i < 10; i++) {
		tmp = modulo_dla_duzych(tablica[i], e, n);
		out[i] = tmp;
	}
}

void deszyfruj(int *zaszyfrowane, int *zdeszyfrowane, int d, int n) {
	for (int i = 0; i < 10; i++) {
		zdeszyfrowane[i] = modulo_dla_duzych(zaszyfrowane[i], d, n);
	}
}

int maksimum_z_tab(int *tab) {
	int maks = tab[0];
	for (int i = 1; i < 10; i++) {
		if (tab[i] > maks) maks = tab[i];
	}
	return maks;
}

void wyswietl(int *tab) {
	for (int i = 0; i < 10; i++) {
		cout << tab[i] << "  ";
	}
}

int odwrotnosc_modulo(int a, int n)
{
	int a0, n0, p0, p1, q, r, t;

	p0 = 0; p1 = 1; a0 = a; n0 = n;
	q = n0 / a0;
	r = n0 % a0;
	while (r > 0)
	{
		t = p0 - q * p1;
		if (t >= 0)
			t = t % n;
		else
			t = n - ((-t) % n);
		p0 = p1; p1 = t;
		n0 = a0; a0 = r;
		q = n0 / a0;
		r = n0 % a0;
	}
	return p1;
}

void convert_to_32_bits(int count, bool *tab) {
	int tmp = count;
	int cnt = 0, cnt_rev = 31, how_much_add = 0, cnt1 = 0;
	bool tmp_tab[32];
	while (tmp != 0) {
		tmp_tab[cnt] = tmp % 2;		//converting to binary system
		cnt++;
		tmp /= 2;
	}
	if (cnt < 32) {
		how_much_add = 32 - cnt;
		cnt--;
		while (cnt1 != how_much_add) {
			tab[cnt1] = 0;
			cnt1++;
		}
		cnt_rev = cnt;
		for (int i = cnt1; i < 32; i++) {
			tab[i] = tmp_tab[cnt_rev];
			cnt_rev--;
		}
	}
	else if (cnt == 32) {
		for (int i = 0; i < 31; i++) {
			tab[i] = tmp_tab[cnt_rev];
			cnt_rev--;
		}
	}
}

int pierwsza_jedynka(bool *tab) {
	int pierwsza = 0,i=0;
	while (i!=32) {
		if (tab[i] = 1) {
			pierwsza = i;
			break;
		}
	}
	return pierwsza;
}

int main(){
	int zaszyfrowane[10],zdeszyfrowane[10],p,q,n,e,d,fi,liczba_los,maks,rozrzut=0;
	bool tab_p[32], tab_q[32];
	int tablica[10]{
		688,232,687,966,668,3,1050,1499,99,856
	};
	maks = maksimum_z_tab(tablica);

	
	do {
		liczba_los = losuj_liczbe();
		p = losuj_liczbe_pierwsza(liczba_los);
		Sleep(1422);
		liczba_los = losuj_liczbe();
		q = losuj_liczbe_pierwsza(liczba_los);
		Sleep(112);

		convert_to_32_bits(p, tab_p);
		convert_to_32_bits(q, tab_q);

		if (p < q) {
			rozrzut = pierwsza_jedynka(tab_q) - pierwsza_jedynka(tab_p);
		}
		else if (p > q) {
			rozrzut = pierwsza_jedynka(tab_p) - pierwsza_jedynka(tab_q);
		}
		if (p == q) n = 0;
		else n = p * q;
	} while (n < maks && rozrzut <= 2);
	fi = (p - 1)*(q - 1);
	e = losuj_e(fi);
	szyfruj(tablica, zaszyfrowane, e, n);
	d=odwrotnosc_modulo(e, fi);
	deszyfruj(zaszyfrowane, zdeszyfrowane, d, n);
	cout << "p: " << p << " q: " << q << " e: " << e <<" d: "<<d<< " n: " << n << " fi: " << fi << endl;
	cout << "Dane wejsciowe: " << "  ";
	wyswietl(tablica);
	cout <<endl<< "Zaszyfrowane: " << "\t";
	wyswietl(zaszyfrowane);
	cout << endl << "Odszyfrowane: " << "\t";
	wyswietl(zdeszyfrowane);
	cout << endl;
	system("pause");
	return 0;
}