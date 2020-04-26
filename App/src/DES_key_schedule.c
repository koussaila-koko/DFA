#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_tables.h"

long shiftMoitier(long Gauche_Droite){
		
	long tmp = Gauche_Droite >> 27;
	Gauche_Droite = Gauche_Droite << 1;
	Gauche_Droite = Gauche_Droite & 0x0FFFFFFFL;
	Gauche_Droite = Gauche_Droite | tmp;
return	Gauche_Droite;}

long shift(long T){
	 long Gauche = (T  >> 28) & 0xFFFFFFFL;
	 long Droite = T & 0xFFFFFFFL;;
	 return (shiftMoitier(Gauche)<< 28 | shiftMoitier(Droite)) & 0xFFFFFFFFFFFFFFL;
}

void DES_key_schedule(long Ki[], long K){
	 int v[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
	 long permuted_key = permutation( K,PC1,  64, 56);
	
	 for(int i = 0; i < 16; i++) {
		 if (v[i] == 1)
			 permuted_key = shift(permuted_key);
		 else
			 permuted_key = shift(shift(permuted_key));

		 Ki[i] = permutation( permuted_key, PC2,56, 48);
	}
}
