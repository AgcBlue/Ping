#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <format>
#include <cstdint>
#include "FUNC.h"
#include <string.h>

using namespace std;

char* intToChar(int x)
{
    int xx = x, coun = 0;
    while(xx)
    {
        coun++;
        xx = xx / 10;
    }

    char* c = new char [coun];

    for(int i = coun - 1; i >= 0; i--)
    {
        c[i] = char(x % 10 + 48);
        x = x / 10;
    }

    return c;
}

void allPortPing(char* argv, int* portList, int portCount)
{

    char *IP_ADDR = new char[100];

    if(argv != 0)
    {
        delete[] IP_ADDR;
        IP_ADDR = argv;
    }
    else
    {
        cin.getline(IP_ADDR, 100);
    }

    int sock;

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 500000;

    struct sockaddr_in connAddr;

    int v[10000] = {0}, ii = 0;

    connAddr.sin_family =  AF_INET;

    if(inet_pton(AF_INET, IP_ADDR, &connAddr.sin_addr) <= 0)
    {
        perror("IP ERROR");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < portCount; i++)
    {    
        connAddr.sin_port = htons(portList[i]);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));


        if(connect(sock, (struct sockaddr*)& connAddr, sizeof(connAddr)) == 0)
        {
            v[ii] =  portList[i];
            ii++;
        }

        close(sock);
    }

    if(argv == 0)
    {
        delete[] IP_ADDR;
    }

    cout << "Active ports number: " << ii << endl;
    if(ii > 0)
    {    
        cout << "Active ports: ";
        for(int i = 0; i < ii; i++)
        {
            if(i + 1 < ii)
            {
                cout << v[i] << ", ";
            }
            else
            {
                cout << v[i] << ".";
            }
        }
        cout << endl;
    }
    
    
}

bool multipleHostPing(char* argv, int* portList, int portCount)
{


    int sock;

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;

    struct sockaddr_in connAddr;

    int v[10000] = {0};

    connAddr.sin_family =  AF_INET;

    char *IP_ADDR = new char[100];

    if(argv != 0)
    {
        delete[] IP_ADDR;
        IP_ADDR = argv;
    }
    else
    {
        cin.getline(IP_ADDR, 100);
    }

    char* p = strstr(IP_ADDR, "192.168.");

    if(p == NULL)
    {
        cout << "The IP is not local." << endl;
        return 1;
    }

    int pointCounter = 0, coun = 0;
    for(int i = 0; i < strlen(IP_ADDR); i++)
    {
        if(IP_ADDR[i] == '.')
        {
            pointCounter++;
        }
        if(pointCounter == 3)
        {
            IP_ADDR[i + 1] = 0;
            coun = i + 1;
            break;
        }
    }

    for(int i = 0; i < 256; i++)
    {
        char* a = intToChar(i);

        for(int j = 0; j < strlen(a); j++)
        {
            IP_ADDR[coun + j] = a[j];
        }
        IP_ADDR[strlen(a) + coun] = 0;


        if(inet_pton(AF_INET, IP_ADDR, &connAddr.sin_addr) > 0)
        {    
            int ii = 0;

            for(int j = 0; j < portCount; j++)
            {    
                connAddr.sin_port = htons(portList[j]);
                sock = socket(AF_INET, SOCK_STREAM, 0);
                setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));


                if(connect(sock, (struct sockaddr*)& connAddr, sizeof(connAddr)) == 0)
                {
                    v[ii] =  portList[j];
                    ii++;
                }

                close(sock);
            }

            if(ii > 0)
            {    
                cout << "For the IP address: " << IP_ADDR << endl;
                cout << "Active ports number: " << ii << endl;
                cout << "Active ports: ";
                for(int j = 0; j < ii; j++)
                {
                    if(j + 1 < ii)
                    {
                        cout << v[j] << ", ";
                    }
                    else
                    {
                        cout << v[j] << ".";
                    }
                }
                cout << endl;
            }

            for(int j = 0; j < 3; j++)
            {
                IP_ADDR[coun + j] = 0;
            }

        }

        
    }
    

    if(argv == 0)
    {
        delete[] IP_ADDR;
    }
    
    return 0;

}

void checkFlagsPing(char* argv, int* portList, int portCount)
{

    char *IP_ADDR = new char[100];

    if(argv != 0)
    {
        delete[] IP_ADDR;
        IP_ADDR = argv;
    }
    else
    {
        cin.getline(IP_ADDR, 100);
    }

    int sock;

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 500000;

    struct sockaddr_in connAddr;

    int v[10000] = {0}, ii = 0;

    connAddr.sin_family =  AF_INET;

    if(inet_pton(AF_INET, IP_ADDR, &connAddr.sin_addr) <= 0)
    {
        perror("IP ERROR");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < portCount; i++)
    {    
        connAddr.sin_port = htons(portList[i]);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));


        if(connect(sock, (struct sockaddr*)& connAddr, sizeof(connAddr)) == 0)
        {

            char banner[1024] = {0};

            struct timeval tv = {2, 0};  // 2 seconds
            setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
            
            int bytes = recv(sock, banner, sizeof(banner) - 1, 0);

            
            if(bytes > 0)
            {
                
                cout << "Port " << portList[i] << " : " << banner << endl;
            }
            else
            {
                send(sock, "HEAD / HTTP/1.0\r\n\r\n", 19, 0);
                
                bytes = recv(sock, banner, sizeof(banner) - 1, 0);

                if(bytes > 0)
                {
                    
                    cout << "Port " << portList[i] << " : " << banner << endl;
                }
            }
            v[ii] =  portList[i];
            ii++;
        }

        close(sock);
    }

    if(argv == 0)
    {
        delete[] IP_ADDR;
    }

    cout << "Active ports number: " << ii << endl;
    if(ii > 0)
    {    
        cout << "Active ports: ";
        for(int i = 0; i < ii; i++)
        {
            if(i + 1 < ii)
            {
                cout << v[i] << ", ";
            }
            else
            {
                cout << v[i] << ".";
            }
        }
        cout << endl;
    }
    
}

void interpretor(int argc, char * argv[])
{
    int allPorts[10000];
    for(int i = 1; i < 9999; i++)
    {
        allPorts[i -1] = i;
    }

    int commonPorts[] = 
    {
        21, 22, 23, 25, 53, 80, 110, 143, 443, 445, 
        587, 993, 995, 3306, 3389, 5432, 8080, 8443
    };

    int quickPorts[] = 
    {
        22, 80, 443, 445, 3389
    };

    int* port = allPorts;
    int portCount = 9999;

    int mode = 0;

    if(argc > 2)
    {
        for(int i = 1; i < argc - 1; i++)
        {

            if(strcmp(argv[i], "-fl") == 0)
            {
                mode = 2;
            }
            if(strcmp(argv[i], "-mI") == 0)
            {
                mode = 1;
            }
            if(strcmp(argv[i], "-sI") == 0)
            {
                mode = 0;
            }

            if(strcmp(argv[i], "-al") == 0)
            {
                port = allPorts;
                portCount = 9999;
            }

            if(strcmp(argv[i], "-com") == 0)
            {
                port = commonPorts;
                portCount = 18;
            }

            if(strcmp(argv[i], "-qk") == 0)
            {
                port = quickPorts;
                portCount = 5;
            }
        }
        if(mode == 1)
        {
            multipleHostPing(argv[argc - 1], port, portCount);
        }
        else if(mode == 0)
        {
            allPortPing(argv[argc - 1], port, portCount);
        }
        else if(mode == 2)
        {
            checkFlagsPing(argv[argc - 1], port, portCount);
        }
    }
    else
    {
        allPortPing(argv[argc - 1], port, portCount);
    }
}

int main(int argc, char * argv[])
{   
    interpretor(argc, argv);
}