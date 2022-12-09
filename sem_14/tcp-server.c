/* TCP-сервер */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int sockfd, newsockfd;
    int clilen;
    int n;
    char line[1000];
    struct sockaddr_in servaddr, cliaddr; 
    /* Создаем TCP-сокет */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror(NULL);
        exit(1);
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family= AF_INET;
    servaddr.sin_port= htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Настраиваем адрес сокета */
    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    /* Переводим созданный сокет в пассивное (слушающее) 
    состояние. Глубину очереди для установленных 
    соединений описываем значением 5 */
    if(listen(sockfd, 5) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    /* Основной цикл сервера */
    while(1){
        
        clilen = sizeof(cliaddr);
        
        if((newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        
        // Создаем процесс чтобы сервер мог одновременно обрабатывать множество запросов
        int pid_from_fork = fork();
        if (pid_from_fork == -1) {
            exit(127);
        }
        if (pid_from_fork == 0) {
        while((n = read(newsockfd, line, 999)) > 0){
            /* Принятые данные отправляем обратно */
            if((n = write(newsockfd, line, strlen(line)+1)) < 0){
                perror(NULL);
                close(sockfd);
                close(newsockfd);
                exit(1);
            }
            printf("%s", line);
        }
        /* Если при чтении возникла ошибка – завершаем работу */
        if(n < 0){
            perror(NULL);
            close(sockfd);
            close(newsockfd);
            exit(1);
        }
        /* Закрываем дескриптор присоединенного сокета и
        уходим ожидать нового соединения */
        close(newsockfd);
        // завершаем дочерний процесс
        return 0;
        }
    }
}