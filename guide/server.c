#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#define PORT 3456
#define BACKLOG 2
#define MAXCHARSIZE 1000
void process_client(int connectfd, struct sockaddr_in client);
int main(void)
{
        int listenfd,connectfd;
        struct sockaddr_in server,client;
        int sin_size;
        int opt=SO_REUSEADDR;
        pid_t pid;
        if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
        perror("create socket failed.");
        exit(-1);
        }
        setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
        bzero(&server,sizeof(server));
        server.sin_family=AF_INET;
        server.sin_port=htons(PORT);
        server.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(listenfd,(struct sockaddr *)&server,sizeof(struct sockaddr ))==-1)
        {
        perror("Bind error.");
        exit(-1);
        }
        if(listen(listenfd,BACKLOG)==-1)
        {
        perror("listen error.");
        exit(-1);
        }
        sin_size=sizeof(struct sockaddr_in);
        while(1)
        {
        if((connectfd=accept(listenfd,(struct sockaddr *)&client,&sin_size))==-1)
        {
        perror("Acccept error.");
        exit(-1);
        }
        if((pid=fork())>0)
        {
        close(connectfd);
        continue;
        }
        else if(pid==0)
        {
        close(listenfd);
        process_client(connectfd,client);
        exit(1);
        }
        else
        {
        perror("Fork error.\n");
        exit(0);
        }
        }
        close(listenfd);
}
void process_client(int connectfd,struct sockaddr_in client)
{
        char recvbuf[MAXCHARSIZE];
        char sendbuf[MAXCHARSIZE];
        char client_name[MAXCHARSIZE];
        char ttt[]="sorry...could't find the right value of it ,please check it again!";
        int recvlen,i;
        printf("You get a connection from %s\n",inet_ntoa(client.sin_addr));
        send(connectfd,"welcome to my server.\n",22,0);
        recvlen=recv(connectfd,client_name,MAXCHARSIZE,0);
        if(recvlen==0)
        {
        close(connectfd);
        printf("Client disconnected.\n");
        return;
        }
        else if(recvlen<0)
        {
        close(connectfd);
        printf("Connect broked.\n");
        return;
        }
        client_name[recvlen]='\0';
        printf("the vlaue of foo is %s.\n",client_name);
        while(recvlen=recv(connectfd,recvbuf,MAXCHARSIZE,0))
        {
        recvbuf[recvlen]='\0';
        printf("Receive from client message:%s\n",recvbuf);
        printf("wait...we will find the right value of it.\n");
        for(i=0;i<recvlen;i++)

        sendbuf[i]=recvbuf[recvlen-i-1];
        sendbuf[recvlen]='\0';
        if(strcmp(recvbuf,"foo")==0)
                {
                printf("ok...get it!\n");
                send(connectfd,client_name,strlen(client_name),0);
                }
        else
                {
                printf("sorry...not find it.\n");
                send(connectfd,ttt,strlen(ttt),0);
                }
        }
	printf("Client:%s disconnected.\n",client_name);
	close(connectfd);
}
