/*
 * bt-tool.c
 *
 *  Created on: Mar 19, 2013
 *      Author: lester
 */
#include "lib/bluez-api.h"
#include <qsiFunc.h>

int main(int argc, char *argv[])
{

	int i, len, n_argc = argc-1;
	char** n_argv;

	if (n_argc == 0){
		printf("Usage: test-bt-tool [PROFILE] [OPTION ...]\n");
		printf("PROFILE : \n");
		printf("	0: adapter\n");
		printf("	1: agent\n");
		printf("	2: audio\n");
		printf("	3: input\n");
		printf("	4: device\n");
		printf("	5: monitor\n");
		printf("	6: bt_network\n");
		printf("	7: bt_obex\n");
		printf("	8: bt_serial\n");
		return 0;
	}


	n_argv=(char **)qsi_malloc((n_argc)*sizeof(char*));

	for (i=0; i<(n_argc); i++){
		len = strlen(argv[i+1]);
		n_argv[i]=(char *)qsi_malloc((len+1)*sizeof(char));
		memcpy(n_argv[i], argv[i+1], len);
		n_argv[i][len]=0x0;
		//printf("%d: %s\n",i,n_argv[i]);
	}

	char ch=argv[1][0];



	switch (ch){
		case '0':	printf("ch: %c adapter\n",ch);		bt_adapter(n_argc, n_argv);	break;
		case '1':	printf("ch: %c agent\n",ch);		bt_agent(n_argc, n_argv);	break;
		case '2':	printf("ch: %c audio\n",ch);		bt_audio(n_argc, n_argv);	break;
		case '3':	printf("ch: %c input\n",ch);		bt_input(n_argc, n_argv);	break;
		case '4':	printf("ch: %c device\n",ch);		bt_device(n_argc, n_argv);	break;
		case '5':	printf("ch: %c monitor\n",ch);		bt_monitor(n_argc, n_argv);	break;
		case '6':	printf("ch: %c bt_network\n",ch);	bt_network(n_argc, n_argv);	break;
		case '7':	printf("ch: %c bt_obex\n",ch);		bt_obex(n_argc, n_argv);	break;
		case '8':	printf("ch: %c bt_serial\n",ch);	bt_serial(n_argc, n_argv);	break;
		default:	printf("invalid second arg\n");									break;
	}

	for (i=0; i<(n_argc); i++){
			free(n_argv[i]);
		}
	return 0;
}
