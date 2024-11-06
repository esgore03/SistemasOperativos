//Esteban Gomez 
//Dylan Morales

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;

void *mythread(void *arg) {
  int counter = 0;
  for (int i = 0; i < max; i++) {
    counter += 1;
  }
  return (void *)(size_t)counter;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: main <loopcount> <num_threads>\n");
    exit(1);
  }
  max = atoi(argv[1]);
  int num_threads = atoi(argv[2]);

  pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
  void **counters = malloc(num_threads * sizeof(void *));
  int total_counter = 0;

  for (int i = 0; i < num_threads; i++) {
    pthread_create(&threads[i], NULL, mythread, NULL);
  }

  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], &counters[i]);
    total_counter += (int)(size_t)counters[i];
  }

  printf("main: done\n [counter: %d]\n [should: %d]\n",
      total_counter, max * num_threads);

  free(threads);
  free(counters);
  return 0;
}