#include <stdio.h>
int checksum(unsigned char *data, int length)
 {
     int sum = 0;
     
     for (int i = 0; i < length; i++) {
         sum +=data[i];
         printf("%c %d\n", data[i], data[i]);
	 }
	 printf("%d\n",sum);
	
     sum = -sum;
     return (sum & 0xFF);
 }

int resultsum(unsigned char *data, int length, int scheck)
 {
	 int sum = 0;
	 for (int i = 0; i < length; i++) {
         	sum +=data[i];
	}
	printf("%d\n",sum);
	
	sum +=scheck;
	sum = -sum;
	return (sum & 0xFF);
 }

int main() {
	char a[10] = {'h','e', 'l', 'l','o', 'w', 'o', 'r', 'l', 'd'};
	int csum = checksum(a,10);	
	printf("CHECKSUM: %d\n", csum);
	
	int rsum = resultsum(a,10,csum);
	printf("RECEIVED CHECKSUM : %d\n", rsum);
	
	if(rsum == 0)
		printf("\n\nNO ERROR IN TRANSMISSION\n\n");
	else
		printf("\n\nERROR DETECTED\n");
	
}
