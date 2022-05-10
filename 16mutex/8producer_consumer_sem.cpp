#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

sem_t sem1;
sem_t sem2;

typedef struct _node_t {
	int data;
	struct _node_t *next;
} node_t;

node_t *head = NULL;

void *producer(void *arg) {
	while(1) {
		sem_wait(&sem1);
		node_t *new_node = (node_t*)malloc(sizeof(node_t));
		if(NULL == new_node) {
			cout << "malloc failed.." << endl;
			break;
		} 
		memset(new_node, 0, sizeof(node_t));
		new_node->data = random() % 100 + 1;
		new_node->next = NULL;

		new_node->next = head;
		head = new_node;
		cout << "生产者生产产品: " << head->data << endl;
		sem_post(&sem2);
//		usleep(1);
		sleep(random() % 3);
	}
	pthread_exit(NULL);
}

void *consumer(void *arg) {
	node_t *temp = NULL;
	while(1) {
		sem_wait(&sem2);
		if(NULL == head) {
			cout << "head == NULL" << endl;
			sleep(2);
		}
		temp = head;
		head = head->next;
		cout << "消费者消费产品: " << temp->data << endl;
		free(temp);
		sem_post(&sem1);
		sleep(random() % 3);
	}
	pthread_exit(NULL);
}

int main() {
	sem_init(&sem1, 0, 8);
	sem_init(&sem2, 0, 0);
	pthread_t tid[6];
	srandom(getpid());
	for(int i = 0;i < 6;i++) {
		if(i < 2) {
			pthread_create(&tid[i], NULL, producer, NULL);
		} else {
			pthread_create(&tid[i], NULL, consumer, NULL);
		}
	}
	for(int i = 0;i < 6;i++) {
		pthread_join(tid[i], NULL);
	}
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	return 0;
}
