#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutex;
pthread_cond_t cond;

typedef struct _node_t {
	int data;
	struct _node_t *next;
} node_t;

node_t *head = NULL;

void *producer(void *arg) {
	while(1) {
		pthread_mutex_lock(&mutex);
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
		cout << "produce temp->data: " << head->data << endl;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
		sleep(random() % 3);
	}
	pthread_exit(NULL);
}

void *consumer(void *arg) {
	node_t *temp = NULL;
	while(1) {
		pthread_mutex_lock(&mutex);
		if(NULL == head) {
//			cout << "null.. sleep(2).." << endl;
//			sleep(2);
			pthread_cond_wait(&cond, &mutex);
			sleep(2);
		}
		temp = head;
		head = head->next;
		cout << "consume temp->data: " << temp->data << endl;
		free(temp);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int main() {
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_t tid1 = -1, tid2 = -1;
	srandom(getpid());
	pthread_create(&tid1, NULL, producer, NULL);
	pthread_create(&tid2, NULL, consumer, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}
