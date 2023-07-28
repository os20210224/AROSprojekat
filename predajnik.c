#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

//./program /ime poruka prioritet
int main (int argc, char *argv[]) {
	//----podesavanje maksimanog proja poruka i duzine poruka----
	struct mq_attr atr;
	atr.mq_msgsize = 100;
	atr.mq_maxmsg = 10;
	//-------provera ulaznih parametara-------------------------
	if (argc != 4) {
		printf("\tProgram se poziva u sledecem formatu:\n\n\t./ime_programa /ime_reda poruka prioritet\n");
                exit(EXIT_FAILURE);
	}
	if (sizeof(argv[1]) > 256) {
		printf("\tMaksimalna duzina imena reda je 256 karaktera\n");
		exit(EXIT_FAILURE);
	}
	if (argv[1][0] != '/') {
		printf("\tIme reda mora poceti sa \"/\"\n");
                exit(EXIT_FAILURE);
	}
	if (sizeof(argv[2]) > atr.mq_msgsize) {
		printf("\tMaksimalna duzina poruke je %d karaktera\n", atr.mq_msgsize);
                exit(EXIT_FAILURE);
	}
	if (atoi(argv[3]) > 31 || atoi(argv[3]) < 0) {
		printf("\tPrioritet poruka je u opsegu 0-31\n");
                exit(EXIT_FAILURE);
	}
	//----------otvaranje reda------------
	mqd_t q = mq_open(argv[1], O_CREAT | O_WRONLY, 0600, &atr);
	if (q == -1)
		perror("greska pri otvaranju reda"), exit(EXIT_FAILURE);
	//---------slanje poruke--------------
	if ( mq_send(q, argv[2], sizeof(argv[2]), (unsigned int) atoi(argv[3])) == -1 )
		perror("greska pri slanju poruke"), exit(EXIT_FAILURE);

	mq_close(q);

	exit(EXIT_SUCCESS);
}

