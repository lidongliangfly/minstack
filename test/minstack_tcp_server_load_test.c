/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                              minstack                                       *
 * Copyright (C) 2010,2011  Aurelien BOUIN (a_bouin@yahoo.fr)                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  This program is free software; you can redistribute it and/or              *
 *  modify it under the terms of the GNU General Public License                *
 *  as published by the Free Software Foundation; either version 3             *
 *  of the License, or (at your option) any later version.                     *
 *                                                                             *
 *  This program is distributed in the hope that it will be useful,            *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 *  GNU General Public License for more details.                               *
 *                                                                             *
 *  You should have received a copy of the GNU General Public License          *
 *  along with this program; if not, write to the Free Software                *
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <tcp.h>
#include <minstack_debug.h>

int run = 1;

void usage(const char *appli);
void stop(int exit_status);
void listenner(int cid,char *from,int from_size, int *port, char *buffer,unsigned int buffer_size_returned);

int main (int argc, char **argv){
	minstack_tcp *mt_listen;
	int loop = 0;
	if(argc < 2 || argc > 3)
		usage(argv[0]);

	signal(SIGABRT, stop);
	signal(SIGTERM, stop);
	signal(SIGINT, stop);

	printf("starting %s on the port %d\n",argv[0],atoi(argv[1]));
	if(argc == 3)
	    minstack_set_debug_level(atoi(argv[2]));
	while(run)
	{
	    loop++;
	    printf("Start %d\n",loop);
	    mt_listen = minstack_tcp_init("The minstack server test");
	    if(mt_listen == NULL)
	    {
	        printf("We could not initialized the server test...\n");
	        return 0;
	    }
        if(minstack_tcp_init_server(mt_listen,atoi(argv[1]),10))
        {
            printf("We could not initialized the server test...\n");
            return 0;
        }
        minstack_tcp_set_external_read_function(mt_listen,listenner);
        minstack_tcp_start(mt_listen);
	    minstack_tcp_uninit(mt_listen);
	    usleep(30*1000);
	}
	printf("stopping %s\n",argv[0]);
	return 0;
}

void usage(const char *appli)
{
	printf("%s have to be started with the port number to listen too\n",appli);
	printf("example: %s 10000 (debug_level)   will start a server that listen on the port 10000 with the debug level in option\n",appli);
	exit(0);
}

void stop(int exit_status)
{
	run = 0;
}

void listenner(int cid,char *from,int from_size, int *port, char *buffer,unsigned int buffer_size_returned)
{
	if(buffer && buffer_size_returned)
		printf("<%s[%d]:%d>%s\n",from,*port,cid,buffer);
}

