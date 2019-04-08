#include<iostream>
#include<string>
#include<time.h>
#include<vector>

using namespace std;

void left_shift(bool *key,int poczatek,int rozmiar,int how_much_shifts) {	
	for (int j = 0; j < how_much_shifts; j++) {
		for (int i = poczatek; i < rozmiar; i++) {
			key[i] = key[i + 1];
		}
		key[rozmiar - 1] = 0;
	}
}


void generate_left_right_28__key(bool *key,int how_much_shifts) {
	left_shift(key, 0, 28, how_much_shifts);
	left_shift(key, 28,56, how_much_shifts);
}

void generate_48_key(bool *key,bool *key_48,int *PC_2) {
	for (int i = 0; i < 48; i++) {
		key_48[i] = key[PC_2[i]-1];
	}
}

void generate_56_key(bool *key, bool *key_56, int *PC_1) {
	for (int i = 0; i < 56; i++) {
		key_56[i] = key[PC_1[i]];
	}
}

void bits_32_permutacja(bool *tmp_32_bits_right_data,int *P_box) {
	for (int i = 0; i < 32; i++) {
		tmp_32_bits_right_data[i] = tmp_32_bits_right_data[P_box[i] - 1];
	}
}

void convert(int count,bool *tab) {
	int tmp = count;
	int cnt = 0,cnt_rev=3, how_much_add = 0,cnt1=0;
	bool tmp_tab[4];
	while (tmp != 0) {
		tmp_tab[cnt] = tmp % 2;
		cnt++;
		tmp /= 2;
	}
	if (cnt < 4) {
		how_much_add = 4 - cnt;
		cnt--;
		while (cnt1!=how_much_add) {
			tab[cnt1] = 0;
			cnt1++;
		}
		cnt_rev = cnt;
		for (int i = cnt1; i < 4; i++) {
			tab[i] = tmp_tab[cnt_rev];
			cnt_rev--;
		}
	}
	else if(cnt==4) {
		for (int i = 0; i < 4; i++) {
			tab[i] = tmp_tab[cnt_rev];
			cnt_rev--;
		}
	}
}

void generate_32_bits(bool *key_48,int *S5,bool*given_bits) {
	bool tmp[6];
	bool tab1[4];
	int cnt2 = 0, cnt3 = 0;
	int row, column;
	int where,number;
	for (int i = 0; i < 8; i++) { 
		for (int j = 0; j < 6; j++) {  
			tmp[j] = key_48[cnt2];
			cnt2++;
		}
		row = tmp[0] * 2 + tmp[5] * 1;
		column= tmp[1] * 8 + tmp[2] * 4 + tmp[3] * 2+ tmp[4] * 1;
		where = row * 16 + column;
		number = S5[where];	
		convert(number, tab1);
		for (int k = 0; k < 4; k++) {
			given_bits[cnt3] = tab1[k];
			cnt3++;
		}
	}
}

void extend_32_to_48(bool *tab,bool *extended_tab,int *tab_int) {
	for (int i = 0; i < 48;i++) {
		extended_tab[i] = tab[tab_int[i] - 1];
	}
}

void key_xor_right_data(bool *key_48,bool *right_data,bool *xored_data) {
	for (int i = 0; i < 48; i++) {
		xored_data[i] = key_48[i] ^ right_data[i];
	}
}

void display_tab(bool *tab,int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		if (i % 4 == 0) cout << " ";
		cout << tab[i];
	}
	cout << endl;
}

int main() {
	bool key_48[48]{
		0,1,0,0,0,0,1,0,
		0,0,1,1,1,0,1,1,
		1,1,1,1,0,1,1,1,
		0,1,0,0,1,1,1,1,
		1,1,1,1,1,0,1,0,
		1,1,1,1,0,0,0,0
	};
	bool tmp_32_bits_right_data[32]{
		1,0,1,1,0,1,1,0,		
		0,0,0,0,1,1,1,0,
		1,0,1,1,0,1,0,0,
		1,0,1,1,1,0,1,1
	};
	bool tab[4];
	bool key_56[56];
	bool xored_data[48];	
	bool key[64] = {
		0,1,0,0,
		1,1,1,0,
		0,0,1,0,
		1,1,1,1,
		0,1,0,0,
		1,1,0,1,
		0,1,1,1,
		1,1,0,0,
		0,0,0,1,
		1,1,1,0,
		1,0,1,1,
		1,0,0,0,
		1,0,0,0,
		1,0,1,1,
		0,0,1,1,
		1,0,1,0
	};

	int number_of_shifts[16]{
		1,1,2,2,
		2,2,2,2,
		1,2,2,2,
		2,2,2,1
	};

	int PC_1[56]{
		57,49,41,33,25,17,9,
		1,58,50,42,34,26,18,
		10,2,59,51,43,35,27,
		19,11,3,60,52,44,36,
		63,55,47,39,31,23,15,
		7,62,54,46,38,30,22,
		14,6,61,53,45,37,29,
		21,13,5,28,20,12,4
	};

	int PC_2[48]{
		14,17,11,24,1,5,3,28,
		15,6,21,10,23,19,12,4,
		26,8,16,7,27,20,13,2,
		41,52,31,37,47,55,30,40,
		51,45,33,48,44,49,39,56,
		34,53,46,42,50,36,29,32
	};

	int S5[64]{
		2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
		14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
		4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
		11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
	};

	int P_box[32]{
		16,7,20,21,
		29,12,28,17,
		1,15,23,26,
		5,18,31,10,
		2,8,24,14,
		32,27,3,9,
		19,13,30,6,
		22,11,4,25
	};

	int E[48]{
		32,1,2,3,4,5,
		4,5,6,7,8,9,
		8,9,10,11,12,13,
		12,13,14,15,16,17,
		16,17,18,19,20,21,
		20,21,22,23,24,25,
		24,25,26,27,28,29,
		28,29,30,31,32,1
	};

	bool extended_tab[48]; 


	extend_32_to_48(tmp_32_bits_right_data, extended_tab, E);

	key_xor_right_data(key_48, extended_tab, xored_data);

	generate_32_bits(xored_data, S5, tmp_32_bits_right_data);
	display_tab(tmp_32_bits_right_data, 32);
	system("pause");
	return 0;
}