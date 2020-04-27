#include <stdio.h>
#include <stdlib.h>
long pow(int a,int b){
	if(b == 0){
		return 1;
	} else {
		return a*pow(a,b-1);
	}
}
void HixaToBinaire(long k, int n,int * t) {
	
	for(int i = n - 1; i >= 0; i--) {
	
		t[n-i-1]=(k >> i) & 1;
	}

}
long BinaireToHixa(int *tab,int nbrBit){	
	long nombre=0;
	int i=0,j=nbrBit-1;
	while(j>=0){
		if(tab[j] != 0){
			nombre =nombre + pow(2,i);
		}
		i++;
		j--;
	}

	return nombre;
}


long permutation( long aPermuter ,int * tablePermutation, int tailleEntree, int tailleSortie) {
	int tabEntreBinaire[ tailleEntree ],  tabPemuterBinaire[ tailleSortie ],  pos;
	HixaToBinaire(aPermuter,tailleEntree,tabEntreBinaire);
	long res = 0x0L;

	for (int i = 0; i < tailleSortie; i++) 
	{	pos=tablePermutation[i]-1;
		tabPemuterBinaire[i]=tabEntreBinaire[pos];
	}
	res=BinaireToHixa(tabPemuterBinaire,tailleSortie);
	return res;
}
