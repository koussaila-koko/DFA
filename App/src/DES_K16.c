#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_tables.h"
long s_boxResultat(long rechercheSBOX1,long rechercheSBOX2,int j){
long res;
res=Sbox[j][(((rechercheSBOX1>>5)&0x00000001)<<1)|(rechercheSBOX1&0x00000001)][(rechercheSBOX1>>1)&0x0000000F] ^
	Sbox[j][(((rechercheSBOX2>>5)&0x00000001)<<1)|(rechercheSBOX2&0x00000001)][(rechercheSBOX2>>1)&0x0000000F];
return res;
	}
	//si c la premier fois que la Sbox "s" contient une erreur 
	//	  on calcule S(K16 XOR E(R16)) XOR S(K16 XOR E(R16 XOR e)) (6bits)
	//sinon on regarte si elle satisfit l equation tmp on lajoute sinon on la replace par 0
	void solution (long valeurPossiblePerSbox[8][15],long R15,long FR15,int j,long A,int nbrSolutionPossible){

					long tmp = A >> (32 - (4 * (j + 1))) & 0x0000000F;
					long ExpR16 = permutation(R15, E, 32, 48);
					long  x= permutation(FR15, E, 32, 48);
					x = x >> (48 - (6 * (j + 1))) & 0x3F;
					ExpR16 = ExpR16 >> (48 - (6 * (j + 1))) & 0x3F;
					
					if(valeurPossiblePerSbox[j][0]==-1){
							for(long k16i= 0;k16i < 64; k16i ++){
							long cal = s_boxResultat(k16i ^ x,k16i ^ ExpR16,j);
								if(tmp == cal){
								valeurPossiblePerSbox[j][nbrSolutionPossible] = k16i;
								nbrSolutionPossible++;
								}
							}
					}else{
							for(int k = 0;k < 15; k ++){
							if(valeurPossiblePerSbox[j][k]!=0){
										long cal = s_boxResultat(valeurPossiblePerSbox[j][k] ^ ExpR16,valeurPossiblePerSbox[j][k] ^ x,j);
									if(tmp != cal){
											valeurPossiblePerSbox[j][k] = 0;
										}
									}
							}
							}
	}


long chercher_k16(long chiffreJuste,long faute[]){
	long Solpossible[8][15] = {{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										 {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										 {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										 {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										 {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										 {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										 {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										 {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	long R15,L16,L16F,FR15,e,A,Cjust,Cfaut;
long k16 =0x000000000000L;
	Cjust = permutation(chiffreJuste, IP, 64, 64) ;
	L16 = (Cjust >> 32) & 0xFFFFFFFFL;
	R15 = Cjust & 0xFFFFFFFFL;
	for(int i = 0; i < 32; i++) {
	Cfaut = permutation(faute[i], IP, 64, 64);
	L16F = (Cfaut >> 32) & 0xFFFFFFFFL;
	FR15 = Cfaut & 0xFFFFFFFFL;
	A = permutation(L16 ^ L16F, Pinv, 32, 32);
	e = permutation((R15 ^ FR15) & 0xFFFFFFFFL, E, 32, 48);
	for(int s = 0;s < 8; s ++){
					int nbrSolutionPossible=0;
					if( ((e >> (48 - (6 * (s + 1)))) & 0x3F) != 0){
						//recuperation des solutions pour
						//message i ssi e différent de zéro 
						solution ( Solpossible,R15, FR15, s,A, nbrSolutionPossible);
					}
			}
	}
for(int s = 0;s < 8; s ++){
	//récupération de la solution de chaque s_box
			for(int n = 0;n < 15; n ++){
				if(Solpossible[s][n]!=0){
					Solpossible[s][0] = Solpossible[s][n];				}
			long a=Solpossible[s][0] << 48 -(6 * (s+1));
			//concatener avec K16
		k16 = k16 | a;	
			}
		}
	return k16;
}

