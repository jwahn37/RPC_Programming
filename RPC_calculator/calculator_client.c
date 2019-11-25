/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculator.h"


void
calc_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	CMD_INPUT  add_1_arg;

	scanf("%s", add_1_arg.cmd_input);
#ifndef	DEBUG
	clnt = clnt_create (host, CALC, CALC_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = calculation_1(&add_1_arg, clnt);
	printf("The answer is %d\n",*result_1);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	calc_1 (host);
exit (0);
}
