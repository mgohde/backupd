#include "utils.h"

int makeConnection(char *sockPath, char *command, char *arg)
{
    int clientSock;
    struct sockaddr_un addr;
    FILE *con;
    char *line;
    size_t lineLen;
    
    clientSock=socket(AF_UNIX, SOCK_STREAM, 0);
    
    if(clientSock==-1)
    {
        printerr("ERROR: Could not create client socket.\n");
        return 0;
    }
    
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family=AF_UNIX;
    //Use the default server socket path for now:
    strncpy(addr.sun_path, sockPath, sizeof(addr.sun_path)-1);
    
    if(connect(clientSock, (struct sockaddr*) &addr, sizeof(struct sockaddr_un)))
    {
        printerr("ERROR: Could not connect to server socket.\n");
        close(clientSock);
        return 0;
    }
    
    //Now convert the file descriptor to a normal file:
    con=fdopen(clientSock, "r+");
    
    fprintf(stdout, "About to send command: %s %s\n", command, arg);
    fprintf(con, "%s %s\n", command, arg);
    
    line=NULL;
    lineLen=0;
    lineLen=getline(&line, NULL, con);
    
    if(lineLen!=-1)
    {
        if(!strcmp(line, "OK\n"))
        {
            return 1;
        }
        
        free(line);
    }
    
    return 0;
}