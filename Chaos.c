#include <math.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char * Encrypt(unsigned char * data, double u, double x0);

double logistic(double u, double x, int n);

// data         待加密/解密的数据
// u, x0        3.5699456... < u <= 4 ; 0  < x0 < 1 ; 
unsigned char * Encrypt(unsigned char * data, double u, double x0) {
	int i, length;
	unsigned char * res;
	for (length = 0; data[length] != '\0'; length++);
	double x = logistic(u, x0, 2000);
	res = (unsigned char *)malloc(sizeof(unsigned char) * length);
	for (i = 0; i < length; i++) {
		x = logistic(u, x, 5);
		res[i] = (unsigned char) ((unsigned char)((int)(floor(x*1000))%127)^data[i]);
		// res[i] = (unsigned char) ((unsigned char)((int)(floor(x*127)))^data[i]);
	}
	return res;
}

// u, x 	3.5699456... < u <= 4 ; 0  < x0 < 1 ; 
// n		每次迭代的置换次数
double logistic(double u, double x, int n) {
	int i;
	for (i = 0; i < n; i++) {
		x = u * x * (1-x);
	}
	return x;
}

//加密解密示例
char * Example(char * str) {
	int i, length;
	double u, x0;
	u = 3.579;
	x0 = 0.13579;
	char * unc = str, *dec;
	unsigned char * data, * dest;
	for (length = 0; str[length] != '\0'; length++);
	dec = (char *)malloc(sizeof(char) * length);
	data = (unsigned char *)malloc(sizeof(unsigned char) * length);
	for (i = 0; i < length; i++)
	{
		data[i] = (unsigned char)unc[i];
	}
	dest = Encrypt(data, u, x0);
	for (i = 0; i < length; i++)
	{
		dec[i] = (char)dest[i];
	}
	return dec;   
}

int main() {
	int i, length;
	char str[] = "lryyyyy : chaotic encryption.";
	for (length = 0; str[length] != '\0'; length++);
	char * unc = str, * dec, *enc;
	dec = Example(str);		//加密
	enc = Example(dec);		//解密
	enc[length] = '\0';

	printf("Encrypted String : ");	printf("%s\n",dec);
	printf("Decrypted String : ");	printf("%s\n",enc);

	return 0;
}
