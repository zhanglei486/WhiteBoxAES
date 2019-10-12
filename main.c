#include "aes_table.c"


#define GETU32(pt) (\
        ((u32)(pt)[0] << 24) ^ ((u32)(pt)[1] << 16) ^\
        ((u32)(pt)[2] <<  8) ^ ((u32)(pt)[3]) )
        
#define PUTU32(ct, st) {\
        (ct)[0] = (u8)((st) >> 24); (ct)[1] = (u8)((st) >> 16);\
        (ct)[2] = (u8)((st) >>  8); (ct)[3] = (u8)(st); }


void printstate(unsigned char * in){
        for(int i = 0; i < 16; i++) {
                printf("%.2X", in[i]);

        }
        printf("\n");

        return;
}

char ascii2hex(char in){
    char out;

    if (('0' <= in) && (in <= '9'))
        out = in - '0';

    if (('A' <= in) && (in <= 'F'))
        out = in - 'A' + 10;

    if (('a' <= in) && (in <= 'f'))
        out = in - 'a' + 10;

    return out;
}

void asciiStr2hex (char * in, char * out, int len){
    int j = 0;
    for (int i = 0; i < len; i += 2)
        out[j++]  = (ascii2hex(in[i ]) << 4) +  ascii2hex(in[i+1]);
}

int main(int argc, char * argv[]){
        unsigned char key[16]={0,};
        unsigned char OUT[32]={0,};
        unsigned char IN[32]={0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,};
        unsigned char IN2[32]={0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,};
        if(argc>1)
		asciiStr2hex(argv[1], (char *)IN, 32);
        //unsigned char IN[32] = "00112233445566778899aabbccddeeff";

        printf("key:\n");
        printstate(key);
        printf("plaintext:\n");
        printstate(IN);

        aes_128_encrypt (key, IN, OUT);
        printf("standard aes,output:\n");
        printstate(OUT);

        aes_128_table_encrypt(IN2, OUT);
	printf("whitebox aes,output:\n");
	printstate(OUT);

        return 0;
}
