#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Local includes. */
#include "console.h"

#define mainQUEUE_LENGTH                   (2)
#define TASK1_PERIOD_MS                    pdMS_TO_TICKS(14)    // Période de 1000 millisecondes
#define TASK2_PERIOD_MS                    pdMS_TO_TICKS(13)    // Période de 2000 millisecondes
#define TASK3_PERIOD_MS                    pdMS_TO_TICKS(15)    // Période de 4000 millisecondes
#define TASK4_PERIOD_MS                    pdMS_TO_TICKS(18)    // Période de 8000 millisecondes
#define APERIODIC_TASK_DELAY_MS            pdMS_TO_TICKS(50)   // Période de 10000 millisecondes

#define TASK1_PRIORITY                 	( tskIDLE_PRIORITY + 1 )
#define TASK2_PRIORITY                 	( tskIDLE_PRIORITY + 2 )
#define TASK3_PRIORITY                 	( tskIDLE_PRIORITY + 3 )
#define TASK4_PRIORITY                 	( tskIDLE_PRIORITY + 4 )
#define APERIODIC_TASK_PRIORITY        	( tskIDLE_PRIORITY + 5 )

/* Tâche qui reçoit les données de la file */
static void prvPeriodicTask1(void *pvParameters);

/* Tâche qui convertit les températures */
static void prvPeriodicTask2(void *pvParameters);

/* Tâche qui multiplie les nombres entiers */
static void prvPeriodicTask3(void *pvParameters);

/* Tâche qui effectue une recherche binaire */
static void prvPeriodicTask4(void *pvParameters);

/* Tâche qui simule une tâche aperiodique */
static void prvAperiodicTask(void *pvParameters);

/* File utilisée par les deux tâches */
static QueueHandle_t xQueue = NULL;

/* LIST AND ELEMENT TO SEARCH FOR BINARY SEARCH */
int list[50] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50
};
int element = 25;

/* Fonction principale de l'application */
void ipsa_sched(void)
{
	/* Création de la file */
	xQueue = xQueueCreate(mainQUEUE_LENGTH, sizeof(uint32_t));

	if (xQueue != NULL)
	{
    	/* Création des tâches périodiques */
    	xTaskCreate(prvPeriodicTask1, "PT1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);
    	xTaskCreate(prvPeriodicTask2, "PT2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, NULL);
    	xTaskCreate(prvPeriodicTask3, "PT3", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, NULL);
    	xTaskCreate(prvPeriodicTask4,"PT4", configMINIMAL_STACK_SIZE, NULL, TASK4_PRIORITY, NULL);

    	/* Création de la tâche aperiodique */
    	xTaskCreate(prvAperiodicTask, "AT", configMINIMAL_STACK_SIZE, NULL, APERIODIC_TASK_PRIORITY, NULL);

    	/* Démarrage des tâches */
    	vTaskStartScheduler();
	}

	/* Si tout se passe bien, le noyau planificateur est maintenant en cours d'exécution,
	et la ligne suivante ne sera jamais exécutée. Si la ligne suivante est exécutée,
	cela signifie qu'il n'y avait pas assez de mémoire heap FreeRTOS disponible pour
	créer les tâches inactives et/ou de temporisation nécessaires au fonctionnement
	du port. Consultez la section sur la gestion de la mémoire sur le site Web
	FreeRTOS pour plus de détails. */
	for (;;)
	{
	}
}

/* Tâche qui reçoit les données de la file */
static void prvPeriodicTask1(void *pvParameters)
{
	for (;;)
	{
    	printf("Working\n");
    	vTaskDelay(TASK1_PERIOD_MS);
	}
}

/* Tâche qui convertit les températures */
static void prvPeriodicTask2(void *pvParameters)
{
	for (;;)
	{
    	float fahrenheit = 90.0f;
    	float celsius = (fahrenheit - 32.0f) * 5.0f / 9.0f;
    	printf("Temperature: %f°F = %f°C\n", fahrenheit, celsius);
    	vTaskDelay(TASK2_PERIOD_MS);
	}
}

/* Tâche qui multiplie les nombres entiers */
static void prvPeriodicTask3(void *pvParameters)
{
	int64_t a = 1234567;
	int64_t b = 9876;
	int64_t result = a * b;

	for (;;)
	{
    	printf("Multiplication: %" PRId64 " * %" PRId64 " = %" PRId64 "\n", a, b, result);
    	vTaskDelay(TASK3_PERIOD_MS);
	}
}

/* Tâche qui effectue une recherche binaire */
static void prvPeriodicTask4(void *pvParameters)
{
	int left = 0;
	int right = sizeof(list) / sizeof(list[0]);
	int mid;

	for (;;)
	{
    	while (left <= right)
    	{
        	mid = (left + right) / 2;

        	if (list[mid] < element)
        	{
            	left = mid + 1;
        	}
        	else
        	{
            	right = mid - 1;
        	}
    	}

    	if (list[mid] != element)
    	{
        	printf("Element %d not found\n", element);
    	}
    	else
    	{
        	printf("Element %d found\n", element);
    	}

    	vTaskDelay(TASK4_PERIOD_MS);
	}
}

/* Tâche qui simule une tâche aperiodique */
static void prvAperiodicTask( void * pvParameters )
{
	for( ; ; )
	{
   	 printf("Bonjour je suis la tache apériodique\n");
    	// simulate a 100 ms task mais je vais mettre plus sinon c'est vraimenet chiant
    	vTaskDelay( APERIODIC_TASK_DELAY_MS );
    	// do some work here oui
	}
}
