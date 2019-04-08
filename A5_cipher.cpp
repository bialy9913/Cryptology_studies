#include<iostream>
#include<string>

using namespace std;


void set_LFSR(bool *r, int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		r[i] = 0;	
	}
}

void shift_tab(bool *r, int rozmiar) {
	for (int i = rozmiar -1; i >=1; i--) {
		r[i] = r[i - 1];
	}
}

void set_during_228_cycles(bool *r1, bool *r2, bool *r3, bool *key_stream) {
	bool tmp, r1_true = false, r2_true = false, r3_true = false, wynik;

	for (int i = 0; i < 228; i++) {

		if ((r1[8] == 0 && r2[10] == 0 && r3[10] == 1) || (r1[8] == 1 && r2[10] == 1 && r3[10] == 0)) {
			r1_true = true;
			r2_true = true;
		}

		else if ((r1[8] == 0 && r3[10] == 0 && r2[10] == 1) || (r1[8] == 1 && r3[10] == 1 && r2[10] == 0)) {
			r1_true = true;
			r3_true = true;
		}

		else if ((r2[10] == 0 && r3[10] == 0 && r1[8] == 1) || (r2[10] == 1 && r3[10] == 1 && r1[8] == 0)) {
			r3_true = true;
			r2_true = true;
		}

		else if ((r1[8] == 0 && r2[10] == 0 && r3[10] == 0) || (r1[8] == 1 && r2[10] == 1 && r3[10] == 1)) {
			r1_true = true;
			r2_true = true;
			r3_true = true;
		}

		wynik = r1[18] ^ r2[21] ^ r3[22];
		key_stream[i] = wynik;

		if (r1_true == true) {
			tmp = r1[18] ^ r1[17] ^ r1[16] ^ r1[13];
			shift_tab(r1, 19);
			r1[0] = tmp;
		}

		if (r2_true == true) {
			tmp = r2[21] ^ r2[20];
			shift_tab(r2, 22);
			r2[0] = tmp;
		}

		if (r3_true == true) {
			tmp = r3[22] ^ r3[21] ^ r3[20] ^ r3[7];
			shift_tab(r3, 23);
			r3[0] = tmp;
		}

		r1_true = false;
		r2_true = false;
		r3_true = false;

		cout << "LFSR1: " << endl;
		for (int i = 18; i >= 0; i--) {
			if (i == 0 || i == 1 || i == 2) {
				cout << r1[i];
			}
			else {
				if (i % 4 == 3) cout << " ";
				cout << r1[i];
			}
		}
		cout << endl << endl;

		cout << "LFSR2: " << endl;
		for (int i = 20; i >= 0; i--) {
			if (i == 0 || i == 1) {
				cout << r2[i];
			}
			else {
				if (i % 4 == 2) cout << " ";
				cout << r2[i];
			}
		}
		cout << endl << endl;

		cout << "LFSR3: " << endl;
		for (int i = 22; i >= 0; i--) {
			if (i == 0 || i == 1 || i == 2) {
				cout << r3[i];
			}
			else {
				if (i % 4 == 3) cout << " ";
				cout << r3[i];
			}
		}
		cout << endl << endl;

		wynik = r1[18] ^ r2[21] ^ r3[22];
		cout << "Key stream: " << endl;
		cout << key_stream[i];
		cout << endl << endl;

		system("pause");
		//system("cls");
	}
}


int main() {
	bool stream_key[228];
	bool r1[19] = {
		1,0,0,1,
		1,0,1,0,
		1,0,0,0,
		1,0,1,1,
		1,0,1
	};
	bool r2[22] = {
		1,0,1,0,
		1,1,0,1,
		0,1,0,0,
		0,0,0,1,
		0,0,1,0,
		1,1
	};
	bool r3[23]={
		1,1,1,1,
		0,1,0,1,
		0,1,0,0,
		1,1,1,0,
		1,1,0,1,
		0,0,0
	};
	cout << "LFSR1: " << endl;
	for (int i = 18; i >= 0; i--) {
		if (i == 0 || i == 1 || i == 2) {
			cout << r1[i];
		}
		else {
			if (i % 4 == 3) cout << " ";
			cout << r1[i];
		}
	}
	cout << endl << endl;

	cout << "LFSR2: " << endl;
	for (int i = 20; i >= 0; i--) {
		if (i == 0 || i == 1) {
			cout << r2[i];
		}
		else {
			if (i % 4 == 2) cout << " ";
			cout << r2[i];
		}
		
	}
	cout << endl << endl;

	cout << "LFSR3: " << endl;
	for (int i = 22; i >= 0; i--) {
		if (i == 0 || i == 1 || i == 2) {
			cout << r3[i];
		}
		else {
			if (i % 4 == 3) cout << " ";
			cout << r3[i];
		}
	}
	cout << endl << endl;
	system("pause");
	//system("cls");
	set_during_228_cycles(r1, r2, r3, stream_key);
	return 0;
}