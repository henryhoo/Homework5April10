#include <iostream>
#include <cstring>
#include <errno.h>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <fcntl.h>
#include <stdio.h>
#include <cmath>
using namespace std;
const std::size_t bufsize = 8192;

int main(int argc, char *argv[]){
	int pid = atoi(argv[1]);
	double t = atof(argv[2]);
	double child1,child2,parent,now;
	mqd_t mq1,mq2,mqp,mqself;
	if(argc!=3||pid<0||pid>6){
		cout<<"input error"<<endl;	
		return -1;
	}
	int status = 0;
	char buffer[bufsize];

	status = fork();

	if (status == -1)
	{
		//error
		cout<<"fail to create subprocess"<<endl;
	}

	else if (status == 0)
	{
		//sub process
		switch(pid){
			case 0:
				now = t;
				mq1 = mq_open("/71",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq1 == -1){
					perror("mq_open()");
				}
				mq2 = mq_open("/72",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq2 == -1){
					perror("mq_open()");
				}
				mqself = mq_open("/70",O_WRONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mqself == -1){
					perror("mq_open()");
				}
				sprintf(buffer,"%f",now);
				cout<<"process "<<pid<<": current temperature"<<now<<endl;
				if (mq_send(mqself, buffer, strlen(buffer), 0) == -1) {
					perror("mq_send()");
				}

				while(true){
					if (mq_receive(mq1, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//							cout << "No message 1\n";
						} else {
							perror("mq_receive()");
						}
					} else {
						//						cout << "Received message 1: `" << buffer << "'.\n";
						child1 = atof(buffer);

					}

					if (mq_receive(mq2, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//						cout << "No message 2\n"<<now;
						} else {
							perror("mq_receive()");
						}
					} else {
						//				cout << "Received message 2: `" << buffer << "'.\n";
						child2 = atof(buffer);
						if(fabs(now-(now+child1+child2)/3)<0.01){
							cout<<"process "<<pid<<": final temperature"<<now<<endl;
							exit(0);
						}
						else{
							now=(now+child1+child2)/3;
							sprintf(buffer,"%f",now);
							cout<<"process "<<pid<<": current temperature"<<now<<endl;
							if (mq_send(mqself, buffer, strlen(buffer), 0) == -1) {
								perror("mq_send()");
							}
						}
					}
				}
				break;
			case 1:	
				mqp = mq_open("/70",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mqp == -1){
					perror("mq_open()");
				}	
				mq1 = mq_open("/73",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq1 == -1){
					perror("mq_open()");
				}
				mq2 = mq_open("/74",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq2 == -1){
					perror("mq_open()");
				}
				mqself = mq_open("/71",O_WRONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq2 == -1){
					perror("mq_open()");
				}
				now=t;
				sprintf(buffer,"%f",now);
				//cout<<"process "<<pid<<": current temperature"<<now<<endl;	
				while(true){
					if (mq_receive(mq1, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//cout << "No message 1\n";
						} else {
							perror("mq_receive()");
						}
					} else {
						//cout << "Received message 1: `" << buffer << "'.\n";
						child1 = atof(buffer);

					}

					if (mq_receive(mq2, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//cout << "No message 2\n"<<now;
						} else {
							perror("mq_receive()");
						}
					} else {
						//cout << "Received message 2: `" << buffer << "'.\n";
						child2 = atof(buffer);
						now=(now+child1+child2)/3;
						sprintf(buffer,"%f",now);
						cout<<"process "<<pid<<": current temperature"<<now<<endl;
						if (mq_send(mqself, buffer, strlen(buffer), 0) == -1) {
							perror("mq_send()");
						}
					}
					if (mq_receive(mqp, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//cout << "No message 2\n"<<now;
						} else {
							perror("mq_receive()");
						}
					} else {
						//cout << "Received message 2: `" << buffer << "'.\n";
						parent = atof(buffer);
						now=(now+parent)/2;
						sprintf(buffer,"%f",now);
						cout<<"process "<<pid<<": current temperature"<<now<<endl;
						if (mq_send(mqself, buffer, strlen(buffer), 0) == -1) {
							perror("mq_send()");
						}
					}
				}
				break;
			case 2:	
				mqp = mq_open("/70",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mqp == -1){
					perror("mq_open()");
				}	
				mq1 = mq_open("/75",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq1 == -1){
					perror("mq_open()");
				}
				mq2 = mq_open("/76",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq2 == -1){
					perror("mq_open()");
				}
				mqself = mq_open("/72",O_WRONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq2 == -1){
					perror("mq_open()");
				}
				now=t;
				sprintf(buffer,"%f",now);
				//cout<<"process "<<pid<<": current temperature"<<now<<endl;	
				while(true){
					if (mq_receive(mq1, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//cout << "No message 1\n";
						} else {
							perror("mq_receive()");
						}
					} else {
						//cout << "Received message 1: `" << buffer << "'.\n";
						child1 = atof(buffer);

					}

					if (mq_receive(mq2, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//cout << "No message 2\n"<<now;
						} else {
							perror("mq_receive()");
						}
					} else {
						//cout << "Received message 2: `" << buffer << "'.\n";
						child2 = atof(buffer);
						now=(now+child1+child2)/3;
						sprintf(buffer,"%f",now);
						cout<<"process "<<pid<<": current temperature"<<now<<endl;
						if (mq_send(mqself, buffer, strlen(buffer), 0) == -1) {
							perror("mq_send()");
						}
					}
					if (mq_receive(mqp, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//cout << "No message 2\n"<<now;
						} else {
							perror("mq_receive()");
						}
					} else {
						//cout << "Received message 2: `" << buffer << "'.\n";
						parent = atof(buffer);
						now=(now+parent)/2;
						sprintf(buffer,"%f",now);
						cout<<"process "<<pid<<": current temperature"<<now<<endl;
						if (mq_send(mqself, buffer, strlen(buffer), 0) == -1) {
							perror("mq_send()");
						}
					}
				}
				break;
			case 3:	
				mqp = mq_open("/71",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mqp == -1){
					perror("mq_open()");
				}	
				mqself = mq_open("/73",O_WRONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq2 == -1){
					perror("mq_open()");
				}
				now=t;
				sprintf(buffer,"%f",now);
				//cout<<"process "<<pid<<": current temperature"<<now<<endl;	
				while(true){
					if (mq_receive(mqp, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//cout << "No message 2\n"<<now;
						} else {
							perror("mq_receive()");
						}
					} else {
						//cout << "Received message 2: `" << buffer << "'.\n";
						parent = atof(buffer);
						now=(now+parent)/2;
						sprintf(buffer,"%f",now);
						cout<<"process "<<pid<<": current temperature"<<now<<endl;
						if (mq_send(mqself, buffer, strlen(buffer), 0) == -1) {
							perror("mq_send()");
						}
					}
				}
				break;
			case 4:	
				mqp = mq_open("/71",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mqp == -1){
					perror("mq_open()");
				}	
				mqself = mq_open("/74",O_WRONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq2 == -1){
					perror("mq_open()");
				}
				now=t;
				sprintf(buffer,"%f",now);
				//cout<<"process "<<pid<<": current temperature"<<now<<endl;	
				while(true){
					if (mq_receive(mqp, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//cout << "No message 2\n"<<now;
						} else {
							perror("mq_receive()");
						}
					} else {
						//cout << "Received message 2: `" << buffer << "'.\n";
						parent = atof(buffer);
						now=(now+parent)/2;
						sprintf(buffer,"%f",now);
						cout<<"process "<<pid<<": current temperature"<<now<<endl;
						if (mq_send(mqself, buffer, strlen(buffer), 0) == -1) {
							perror("mq_send()");
						}
					}
				}
				break;
			case 5:	
				mqp = mq_open("/72",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mqp == -1){
					perror("mq_open()");
				}	
				mqself = mq_open("/75",O_WRONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq2 == -1){
					perror("mq_open()");
				}
				now=t;
				sprintf(buffer,"%f",now);
				//cout<<"process "<<pid<<": current temperature"<<now<<endl;	
				while(true){
					if (mq_receive(mqp, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//cout << "No message 2\n"<<now;
						} else {
							perror("mq_receive()");
						}
					} else {
						//cout << "Received message 2: `" << buffer << "'.\n";
						parent = atof(buffer);
						now=(now+parent)/2;
						sprintf(buffer,"%f",now);
						cout<<"process "<<pid<<": current temperature"<<now<<endl;
						if (mq_send(mqself, buffer, strlen(buffer), 0) == -1) {
							perror("mq_send()");
						}
					}
				}
				break;
			case 6:	
				mqp = mq_open("/72",O_RDONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mqp == -1){
					perror("mq_open()");
				}	
				mqself = mq_open("/76",O_WRONLY | O_CREAT | O_NONBLOCK,0666,NULL);
				if(mq2 == -1){
					perror("mq_open()");
				}
				now=t;
				sprintf(buffer,"%f",now);
				//cout<<"process "<<pid<<": current temperature"<<now<<endl;	
				while(true){
					if (mq_receive(mqp, buffer, bufsize, NULL) == -1) {
						if (errno == EAGAIN) {
							//cout << "No message 2\n"<<now;
						} else {
							perror("mq_receive()");
						}
					} else {
						//cout << "Received message 2: `" << buffer << "'.\n";
						parent = atof(buffer);
						now=(now+parent)/2;
						sprintf(buffer,"%f",now);
						cout<<"process "<<pid<<": current temperature"<<now<<endl;
						if (mq_send(mqself, buffer, strlen(buffer), 0) == -1) {
							perror("mq_send()");
						}
					}
					//					cout<<"in";
				}
				break;

		}
	}
	else
	{
		//parent process
		cout<<"parents end"<<endl;	
		return 0;
	}
}
