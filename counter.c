//Esteban Gomez 
//Dylan Morales

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;

void *mythread(void *arg) {
  char *letter = arg;
  int counter = 0; // Local counter variable for each thread
  printf("%s: begin [addr of counter: %p]\n", letter, &counter);
  for (int i = 0; i < max; i++) {
    counter = counter + 1;
  }
  printf("%s: done\n", letter);
  return (void *)(size_t)counter; // Cast to return the counter value
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: main <loopcount>\n");
    exit(1);
  }
  max = atoi(argv[1]);

  pthread_t p1, p2;
  int total_counter = 0;
  void *counter_p1, *counter_p2;

  printf("main: begin\n");
  pthread_create(&p1, NULL, mythread, "A");
  pthread_create(&p2, NULL, mythread, "B");

  pthread_join(p1, &counter_p1);
  pthread_join(p2, &counter_p2);

  total_counter = (int)(size_t)counter_p1 + (int)(size_t)counter_p2;
  printf("main: done\n [counter: %d]\n [should: %d]\n",
      total_counter, max * 2);

  return 0;
}