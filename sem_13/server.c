#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int sockfd;
  int clilen, n;
  char line[1000];
  char buffer[1000];

  struct sockaddr_in servaddr, cliaddr;

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(51000);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror(NULL);
    exit(1);
  }

  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror(NULL);
    close(sockfd);
    exit(1);
  }

  while (1) {
    clilen = sizeof(cliaddr);

    if ((n = recvfrom(sockfd, line, 999, 0, (struct sockaddr *)&cliaddr,
                      &clilen)) < 0) {
      perror(NULL);
      close(sockfd);
      exit(1);
    }
    printf("%s\n", line);

    if (line[0] == 'G') {
      if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cliaddr,
                 clilen) < 0) {
        perror(NULL);
        close(sockfd);
        exit(1);
      }
      printf("%s\n", buffer);
    } else {
      if (sendto(sockfd, line, strlen(line), 0, (struct sockaddr *)&cliaddr,
                 clilen) < 0) {
        perror(NULL);
        close(sockfd);
        exit(1);
      }
    }

    strcpy(buffer, line);
  }
  return 0;
}