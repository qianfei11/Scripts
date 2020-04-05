#include <stdio.h>
#include <stdlib.h>
#define r (rand() * 10000) / RAND_MAX

int main() {
	int chairs; // sum of chairs
	int customers = 0; // sum of customers
	int count = 0; // counter
	int waiting = 0; // waiting people
	int finish = 0; // finished people
	int work = 0; // barber's working state
	int sleeping = 0; // barber's sleeping state
	char opendoor; // whether open the door or not
	printf("Please input the number of chairs: \n");
	scanf("%d", &chairs);
	getchar();
	printf("There are %d chairs in barber shop.\n", chairs);
	printf("Open the door? [y/n]\n");
	opendoor = getchar();
	while(opendoor != 'y') {
		printf("Sorry...\n");
		getchar();
		printf("Open the door? [y/n]\n");
		opendoor = getchar();
	}
	printf("Welcome!\n");
	if(r % 2) { // There are customers
		printf("Customers are waiting.\n");
		customers++;
		printf("Barber start serving customer %d.\n", customers);
		work = 1;
Loop:
		for(count = 0; r % 2 && count <= 5; count++) { // Customers come randomly
			customers++;
			printf("Here comes customer %d.\n", customers);
			sleeping = 0;
			if(work == 1) {
				if(waiting < chairs) {
					printf("There are %d empty chair(s).\n", chairs - waiting);
					waiting++;
				} else {
					printf("There are no empty chairs.\n");
				}
			} else {
				printf("Barber start serving customer %d.\n", customers);
				work = 1;
				
			}
		}
		if(work == 1) {
			sleep(2);
			printf("Finished!\n");
			work = 0;
			finish++;
		}
		if(finish > 4) {
			printf("Already served %d customers, %d customers are waiting, continue? [y/n]\n", finish, waiting);
			getchar();
			opendoor = getchar();
			if(opendoor == 'n') {
				exit(0);
			}
			sleeping = 0;
		}
		if(waiting > 0) { // if any, serve the waiting one
			printf("%d customers are waiting.\n", waiting);
			waiting--;
			work = 1;
			goto Loop;
		} else {
			if(sleeping == 0) { // start sleeping
				printf("Barber is sleeping.\n");
				sleeping = 1;
			}
			goto Loop;
		}
	} else {
		if(sleeping == 0) {
			printf("Barber is sleeping.\n");
			sleeping = 1;
		}
		goto Loop;
	}
	return 0;
}
