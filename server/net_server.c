/*
 * the implementation for the function in net_server.h 
 * author: zhenhua
 * date: 2015.1
*/

#include "net_server.h"

int createServer(Nest *nest, int dimension)
{
	int listen_fd, conn_fd;
	struct sockaddr_in cli_addr;
	int cli_len;
	char *recvline, str[INET_ADDRSTRLEN];
	int dev_tag = -1, n;
	int ret; 

	listen_fd = SocketListen(PORT);
	if(listen_fd == -1)
	{
		fprintf(stderr, "SocketListen create failed\n");
		return -1;
	}
	

	for(;;)
	{
		printf("\n\n\nServer is listening ... \n\n\n\n\n");
		fprintf(stderr, "\n\n\nServer is listening ... \n\n\n\n\n");

		cli_len = sizeof(cli_addr);
		conn_fd = Accept(listen_fd, (struct sockaddr *)&cli_addr, &cli_len);

		inet_ntop(AF_INET, &cli_addr.sin_addr, str, sizeof(str));
		
	
		while(1)
		{
#ifdef 	_DEBUG
			printf("\n\n\nsocket from %s at PORT %d is connecting... \n", str, ntohs(cli_addr.sin_port));
#endif
			recvline = (char *)malloc(sizeof(int));
			memset(recvline, '\0', sizeof(int));		
			n = Readn(conn_fd, recvline, sizeof(int));
			dev_tag = *(int *)recvline;
#ifdef _DEBUG
			printf("createServer | dev_tag: %d\n", dev_tag);
#endif
			switch(dev_tag)
			{
				case DEV_PC:
				case DEV_PHONE:
					ret = reponseWithDevice(nest, dimension, conn_fd, dev_tag);
					if(ret == -1)
					{
						fprintf(stderr, "reponseWithDevice failed\n");
						close(conn_fd);
					}
					else if(ret == -2)
					{
						fprintf(stderr, "reponseWithDevice ask to close the socket\n");
						close(conn_fd);
					}
					fflush(stdout);
#ifdef _DEBUG
					if(ret == 0)
					{ 
						printf("createServer | reponseWithDevice success\n");
						fprintf(stderr, "createServer | reponseWithDevice success\n");
					}
#endif
					break;

				case DEV_CLOSE:
					close(conn_fd); 
					break;				
				default:
					close(conn_fd);
					printf("dev_tag  default \n");
			}
			if(  ((dev_tag != DEV_PC) && (dev_tag != DEV_PHONE)) || (ret == -1) || (ret == -2) )
			{
				printf("close current socket\n");
				break;
			}
		}
	}
	
	free(recvline);
	return 0;
}



