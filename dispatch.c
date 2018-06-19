#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/epoll.h>

int PORT=7800;
int SER_PORT=7801;
const char *IP="127.0.0.1";
int main()
{
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    assert(sockfd!=-1);
    struct sockaddr_in saddr;
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(PORT);
    saddr.sin_addr.s_addr=inet_addr(IP);

    int res=bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr));
    assert(res!=-1);
    

    int ser_sockfd=socket(AF_INET,SOCK_STREAM,0);
    assert(ser_sockfd!=-1);

    struct sockaddr_in ser_saddr;
    ser_saddr.sin_family=AF_INET;
    ser_saddr.sin_port=htons(SER_PORT);
    ser_saddr.sin_addr.s_addr=inet_addr(IP);

    res=connect(ser_sockfd,(struct sockaddr *)&ser_saddr,sizeof(ser_saddr));
    assert(res!=-1) ;

    listen(sockfd,5);

        struct sockaddr_in caddr;
        int len=sizeof(caddr);
    while(1)
    {
        
        int c=accept(sockfd,(struct sockaddr *)&caddr,&len);
        assert(c!=-1);
        printf("c=%d\n",c); 
    
        while(1)
        {
            char buff[128]={0};
            int word=recv(c,buff,128,0)>0;
            if(word==0)
            {
                close(c);
                break;
            }
            else
            {
            printf("buff=%s\n",buff);
            fflush(stdout);
            send(ser_sockfd,buff,strlen(buff),0);
            memset(buff,0,strlen(buff));
            }
        }
    }
    close(sockfd);
    close(ser_sockfd);
    return 0;
    
}
