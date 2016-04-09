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
mq_unlink("/70");
mq_unlink("/71");
mq_unlink("/72");
mq_unlink("/73");
mq_unlink("/74");
mq_unlink("/75");
mq_unlink("/76");
}
