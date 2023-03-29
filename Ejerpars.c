#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADS_NO 10

/* Esta funcion imprime si el hilo es par o impar y después termina. */
void* print_hello_world( void *args )
{
    int thread_id = *((int*)args);
    if (thread_id % 2 == 0) {
        printf( "Soy par.\n" );
    } else {
        printf( "Soy impar.\n" );
    }
    pthread_exit( NULL );
}

/* El programa principal crea 10 hilos, les asigna un ID y espera a que terminen. */
int main()
{
    pthread_t threads[THREADS_NO];
    int state, i, thread_ids[THREADS_NO];
   
    for(i=0; i < THREADS_NO; i++)
    {
        thread_ids[i] = i;
        state = pthread_create( &threads[i], NULL, print_hello_world, &thread_ids[i] );
        printf( "Main creo un hilo en la iteración %d.\n", i );
       
        if (state != 0)
        {
            perror("pthread_create() error.");
            exit(-1);
        }
    }
   
    // Esperamos a que terminen todos los hilos.
    for(i=0; i < THREADS_NO; i++)
    {
        state = pthread_join(threads[i], NULL);
        if (state != 0)
        {
            perror("pthread_join() error.");
            exit(-1);
        }
    }
   
    exit(0);
}
