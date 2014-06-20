#include "../include/utils.h"

char *to_base(unsigned long long n, uint base, uint fixed){
	assert(base >= 2 && base <= 16);
	
	int len = length_base(n, base);
	len = MAX(len, fixed);
	char *res = (char *) malloc(len + 1);
	res[len] = '\0';
	
	int i;
	for(i = 0; i < len; i++){
		char c = n % base;
		
		if(c >= 0 && c < 10){
			c += '0';
		}else{
			c += 'a' - 10;
		}
		
		res[len - i - 1] = c;
		n /= base;
	}
	
	return res;
}

uint length_base(unsigned long long n, uint base){
	assert(base >= 2 && base <= 16);
	
	if(n == 0){
		return 1;
	}
	
	return (int) _log(n, base) + 1;
}

uint _log(unsigned long long n, uint base){
	assert(n > 0 && base >= 2);
	int x = 0;
	double q = n;
	
	while(1 <= q){
		q /= base;
		x++;
	}
	
	return x - 1;
}

uint _ceil(float x){
	return (x > (int) x) ? ((int) x + 1) : ((int) x);
}

int random(int a, int b){
	assert(a <= b);
	double u = rand() / (double) RAND_MAX;
	
	return (int) ((b - a + 1) * u) + a;
}

void print_sep(char sep){
	int i;
	for(i = 0; i < 80; i++){
		printf("%c", sep);
	}
	printf("\n");
}
