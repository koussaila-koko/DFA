#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_key_schedule.h"
#include "../head/DES_tables.h"

//  caluler F(Ri XOR Ki)= P(S(E(Ri) XOR Ki)) etape par etape 

long DES(long clair, long K) 
{
	long Ki[16] = {0}; //tableau de 16 sous cles
	DES_key_schedule(Ki, K);
	
	//Permutation initiale IP
	long clairIP = permutation( clair,IP, 64, 64);
	long L = (clairIP & 0xFFFFFFFF00000000L) >> 32;
	long R = clairIP & 0x00000000FFFFFFFFL;
	
	//16 tours de Feistel
	long LiPlus1, RiPlus1;
	for (int i = 0; i < 16; i++) {
		LiPlus1 = R;
		
     //calculer F(R, Ki[i]
	long T = permutation(R, E, 32, 48) ^ Ki[i];
	long res = 0x0L;
	for (int i = 0 ; i < 8 ; i++){
		long B = (T >> (48 - 6 - i*6)) & 0x3FL;
		int r = 2 * ((B & 0x20) >> 5) + (B & 0x1);
		int c = (B & 0x1E) >> 1;
		res = res | (Sbox[i][r][c] << (32 - 4 - i*4));
	}
	//RiPlus1 =L ^ F(R, Ki[i]);
		RiPlus1 =L ^permutation(res,P,  32, 32); 
		L = LiPlus1;
		R = RiPlus1;	
	}
	
	return permutation(  (R << 32) | L,IPinv,  64, 64);

}











































