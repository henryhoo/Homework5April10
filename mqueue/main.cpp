#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

#include <iostream>

// default max message size, can be found in /proc/sys/fs/mqueue/msgsize_max
const std::size_t bufsize = 8192;

const char * queue = "/apple";

int main(int argc, char *argv[]) {
    char buffer[bufsize];
    if (argc == 1) {
        mq_unlink(queue);
        std::cout << "Queue unlinked\n";
        return 0;
    }

    // Using default attributes (max # messages, max message size)
    mqd_t mq = mq_open(queue, O_RDWR | O_CREAT | O_NONBLOCK, S_IRUSR | S_IWUSR, NULL);
    if (mq == -1) {
        perror("mq_open()");
    }

    if (mq_receive(mq, buffer, bufsize, NULL) == -1) {
        if (errno == EAGAIN) {
            std::cout << "No message\n";
        } else {
            perror("mq_receive()");
        }
    } else {
        std::cout << "Received message: `" << buffer << "'.\n";
    }
    if (mq_receive(mq, buffer, bufsize, NULL) == -1) {
        if (errno == EAGAIN) {
            std::cout << "No message\n";
        } else {
            perror("mq_receive()");
        }
    } else {
        std::cout << "Received message: `" << buffer << "'.\n";
    }


    if (mq_send(mq, argv[1], strlen(argv[1]), 0) == -1) {
        perror("mq_send()");
    }

    mq_close(mq);
    return 0;
}

