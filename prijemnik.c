#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int main (int argc, char *argv[]) {
	//--------provera ulaznih parametara-----------
	if (argc != 2) {
                printf("\tProgram se poziva u sledecem formatu:\n\n\t./ime_procesa /ime_reda\n");
                exit(EXIT_FAILURE);
        }
        if (sizeof(argv[1]) > 256) {
                printf("\tMaksimalna duzina imena reda je 256 karaktera\n");
                exit(EXIT_FAILURE);
        }
        if (argv[1][0] != '/') {
                printf("\tIme reda mora poceti sa kosom crtom \"/\"\n");
                exit(EXIT_FAILURE);
        }
	//-------otvaranje reda u rezimu citanja-----------
	mqd_t q = mq_open(argv[1], O_RDONLY);
        if (q == -1)
                perror("greska pri otvaranju reda"), exit(EXIT_FAILURE);
	//------uzimanje velicine poruke------------------
	struct mq_attr atr;
	if ( mq_getattr(q, &atr) == -1)
		perror("greska pri citanju atributa"), exit(EXIT_FAILURE);
	//------primanje poruke i upisivanje u buffer poruka-----
	char poruka[atr.mq_msgsize];
        if ( mq_receive(q, poruka, sizeof(poruka), NULL) == -1 )
                perror("greska pri primanju poruke"), exit(EXIT_FAILURE);
	//------ispis poruke----------------
	printf("Primljena poruka:\t%s\n", poruka);
	//------zatvaranje reda i unlinkovanje u slucaju da je ostao prazan-----
	mq_close(q);
	if (atr.mq_curmsgs == 1) mq_unlink(argv[1]);

	exit(EXIT_SUCCESS);
}
