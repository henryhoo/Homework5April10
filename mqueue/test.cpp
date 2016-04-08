#include <iostream>
#include <cstring>
#include <errno.h>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

using namespace std;

int main()
{
    mqd_t mqID;
    mqID = mq_open("/anonymQueue", O_RDWR | O_CREAT | O_EXCL, 0666, NULL);

    if (mqID < 0)
    {
        if (errno == EEXIST)
        {
            mq_unlink("/anonymQueue");
            mqID = mq_open("/anonymQueue", O_RDWR | O_CREAT, 0666, NULL);
        }
        else
        {
            cout<<"open message queue error..."<<strerror(errno)<<endl;
            return -1;
        }
    }

    if (fork() == 0)
    {
        mq_attr mqAttr;
        mq_getattr(mqID, &mqAttr);

        char *buf = new char[mqAttr.mq_msgsize];

        for (int i = 1; i <= 5; ++i)
        {
            if (mq_receive(mqID, buf, mqAttr.mq_msgsize, NULL) < 0)
            {
                cout<<"receive message  failed. ";
                cout<<"error info:"<<strerror(errno)<<endl;
                continue;
            }

            cout<<"receive message "<<i<<": "<<buf<<endl;   
        }
        exit(0);
    }

    char msg[] = "yuki";
    for (int i = 1; i <= 5; ++i)
    {
        if (mq_send(mqID, msg, sizeof(msg), i) < 0)
        {
            cout<<"send message "<<i<<" failed. ";
            cout<<"error info:"<<strerror(errno)<<endl;
        }
        cout<<"send message "<<i<<" success. "<<endl;   

        sleep(1);
    }
}
