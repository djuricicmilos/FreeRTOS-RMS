#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

typedef struct
{
    const char *name;
    TickType_t execTime;
    TickType_t period;
    UBaseType_t priority;
    TickType_t release_time;
    TickType_t remaining_time;
} Task_Params;

void Task(void *pvParameters)
{
    Task_Params *params = (Task_Params *)pvParameters;

    for (;;)
    {
        if (params->remaining_time == 0)
            params->remaining_time = params->execTime;

        printf("| %-8s | %5lu | %5lu | Početak       |\n",
               params->name,
               (unsigned long)xTaskGetTickCount(),
               (unsigned long)params->remaining_time);

        TickType_t lastTick = xTaskGetTickCount();

        while (params->remaining_time > 0)
        {
            TickType_t currentTick = xTaskGetTickCount();

            if (currentTick > lastTick)
            {
                params->remaining_time -= 1;
            }
            
            lastTick = currentTick;
        }

            printf("| %-8s | %5lu | %5s | Kraj          |\n",
                params->name,
                (unsigned long)lastTick,
                "/");

        vTaskDelayUntil(&params->release_time, params->period);
    }
}

void rms_algorithm(Task_Params *tasks, size_t numTasks)
{
    size_t i, j;
    Task_Params temp;
    for (i = 0; i < numTasks - 1; i++) {
        for (j = 0; j < numTasks - i - 1; j++) {
            if (tasks[j].period > tasks[j + 1].period) {
                temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    for (size_t i = 0; i < numTasks; i++) {
        tasks[i].priority = (UBaseType_t)(numTasks - i); 
    }
}

void main_RMS(void)
{
    // 1. Inicijalizacija zadataka
    Task_Params taskSet[] = {
        {"Z1", pdMS_TO_TICKS(500),  pdMS_TO_TICKS(3000), 0, xTaskGetTickCount(), 0},
        {"Z2", pdMS_TO_TICKS(1000), pdMS_TO_TICKS(4000), 0, xTaskGetTickCount(), 0},
        {"Z3", pdMS_TO_TICKS(2000), pdMS_TO_TICKS(6000), 0, xTaskGetTickCount(), 0}
    };

    const size_t numTasks = sizeof(taskSet) / sizeof(taskSet[0]);

    // 2. Sortiranje zadataka po periodu (za RMS) i dodeljivanje prioriteta
    rms_algorithm(taskSet, numTasks);


    // 3. Kreiranje zadataka
    for (size_t i = 0; i < numTasks; i++) {
        xTaskCreate(Task, 
                    taskSet[i].name, 
                    configMINIMAL_STACK_SIZE, 
                    &taskSet[i],
                    taskSet[i].priority,
                    NULL);
    }
 
    printf("\n");
    printf("+----------+-------+-------+---------------+\n");
    printf("| Zadatak  | Izvr. | Preos.| Akcija        |\n");
    printf("|          | (ms)  |(ticks)|               |\n");
    printf("+----------+-------+-------+---------------+\n");
 
    // 4. Pokretanje schedulera
    vTaskStartScheduler();

}
