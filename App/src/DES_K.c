#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_key_schedule.h"
#include "../head/DES_algo.h"
#include "../head/DES_tables.h"
long rechbitperdu(long mask){
		long pos[] = {14, 15, 19, 20, 51, 54, 58, 60};
	long res = 0x0L;
	for(int i = 0; i < 8; i++)
	{	res = res | ( ((mask >> i) & 1) << (64 - pos[i]) );
}
return res;
}//ajouter les 8bits (algo dérivation clés)
long transfK48toK56(long clair, long chiffre, long K16) 
{
	long K48b = permutation( permutation( K16,PC2inv, 48, 56),PC1inv, 56, 64);
	long mask = 0x00L;
	long tesst = K48b;
	printf("chiffre %lx\n",chiffre );
	while( mask < 256 && chiffre != DES(clair, tesst) ) 
	{	long res=rechbitperdu( mask);
		tesst = K48b | res;
		mask = mask + 1;
	}
printf("apres %lx\n",mask < 256 && chiffre );
	return tesst;
}

//trouver les 8bits de partie
long bitsParite(long K56b) 
{
	long res = K56b;
	long tmp, parite;
	
	for(int i = 0; i < 8; i++) {
		parite = 0;
		for(int j = 0; j < 8; j++) {
			if(j != 7) {
				tmp = 0x1L << ( ((7 - i) * 8) + (7 - j) );
				tmp = K56b & tmp;
				parite = tmp ? parite ^ 1 : parite ^ 0;
			}
			else {
				tmp = !parite;
				res |= tmp << ((7 - i) * 8);
			}
		}
	}
	return res;
}
//construire K64bits 
long rechercheK(long clair, long chiffre, long K16) 
{	
	//Recherche 56 bits de K à partir de K16 (8 bits manquants)
	long K56b = transfK48toK56(clair, chiffre, K16);
	
	printf("\n56 bons bits de K = %lx\n", K56b);
	
	//Calcul des 8 bits de parité restants
	long K64b = bitsParite(K56b);
	
	return K64b;
}
