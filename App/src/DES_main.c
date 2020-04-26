#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_algo.h"
#include "../head/DES_K16.h"
#include "../head/DES_K.h"


int main()
{
long MessageClair = 0xB307FD04379D8075;
long MessageChiffreJuste =0x937B2FD61208B0DD;
long MessagesChiffresFaux[] = {0x916E2F961208B0CD
,0x93692F961209B0DD
,0x937B2DD21209B0DD
,0x932B2BD40209B0DD
,0x922B2FD20008B0DD
,0x923B2BD6120AB0DD
,0x933B2BD60208B2DD
,0x923B2BD7420CB0DF
,0x9A3B2BD75218B0DD
,0x93732FD65218B0DD
,0x937B27D75208B0DD
,0xD37B3FDF525CB0DD
,0x937B2FD75A58B0DC
,0x937B3FD61200B0DC
,0xD37B3FD61208B8DD
,0xD37B3FD61608B094
,0xF37B2FD61648B09D
,0x935B2FD61608B19D
,0x937B0FD61608A09D
,0x877B6EF61608A19D
,0x977B2ED63608A09D
,0x977B6FD61228B0DD
,0x877B2ED6120890DD
,0x837B2ED61308F0FD
,0x177B2EC61308B4DD
,0x93FB2FC61308B0DD
,0x937BAFC61208B4DD
,0x937A2F461308F0CD
,0x937F2FD69308B4C9
,0x937E2FD61288B0CD
,0x937E2FD6120830D9
,0x937E2FD21209B049			};
	


	long  K16 = chercher_k16(MessageChiffreJuste,MessagesChiffresFaux);
	
	
	
    printf("\n\n\n\n-----------------------------------------------------------------\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf(" La valeur de K16 \n");
	printf(" K16= %lx\n\n\n", K16);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("-----------------------------------------------------------------\n\n");

	long K = rechercheK(MessageClair, MessageChiffreJuste, K16);

	printf("\n\n\n\n-----------------------------------------------------------------\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf(" La valeur de K \n");
	printf(" K= %lx\n\n\n", K);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("-----------------------------------------------------------------\n\n");
	
	printf("\n\n\n\n-----------------------------------------------------------------\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("ChiffrÃ© juste donnÃ©e = %lx\n",MessageChiffreJuste);
	printf("ChiffrÃ© juste trouvÃ© avec DES et K = %lx\n\n",DES(MessageClair,K));
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("-----------------------------------------------------------------\n\n");
	
	return EXIT_SUCCESS;
}
