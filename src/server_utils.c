#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>

void start_server(char* buf, size_t bufsize, const int PORT) 
{
  int sockfd;

  struct sockaddr_in serv,cli;
  socklen_t addrlen = sizeof(cli);

  //Initialize the ingress address for server socket
  memset(&serv, 0, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_port = htons(PORT);
  serv.sin_addr.s_addr = INADDR_ANY;

  //Initialize socket descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
  {
    perror("socket failed");
    return;
  }

  int broadcast_enable = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable))) 
  {
    perror("setsockopt failed");
    return;
  }

  if (bind(sockfd, (const struct sockaddr*)&serv, sizeof(serv)) < 0)
  {
    perror("bind failed");
  }

  //Begin server event loop
  for (;;)  
  {
    int bytes_received = recvfrom(sockfd, buf, bufsize, 0, (struct sockaddr*)&cli, &addrlen);
    if (bytes_received < 0)  
    {
      perror("Server receive error: failed to receive bytes from socket\n");
      continue;
    }

    buf[bytes_received] = '\0';
    printf("Received: %s\n", buf);

    // START LOGGING LOGIC
    // perform_log(buf)
       
    int bytes_sent = sendto(sockfd, MSG, strlen(MSG), 0, (struct sockaddr*)&cli, addrlen);
    if (bytes_sent < 0)
    {
      printf("Server reply error: failed to send bytes to client\n");
      continue;
    }
  }

  close(sockfd);
}
