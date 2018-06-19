#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/epoll.h>

int  PORT=7801;
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
    
    listen(sockfd,5);
    while(1)
    {
        struct sockaddr_in caddr;
        int len=sizeof(caddr);
        //

        int c=accept(sockfd,(struct sockaddr *)&caddr,&len);
        assert(c!=-1);
        printf("c=%d\n",c);
        if(c>1)
        {

        
        while(1)
        {
            char buff[128]={0};
            int size=recv(c,buff,128,0);
            if(size==0)
            {
                printf("one cli over\n");
                close(c);
                break;
            }
            else{
                printf("%s\n",buff);

            }
            
         }
        }
    }
    close(sockfd);
    return 0;
    
}
