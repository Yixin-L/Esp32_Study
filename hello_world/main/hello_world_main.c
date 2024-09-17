/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
//#include "esp_task_wdt.h"
#include "freertos/timers.h"

// void myTask1(void *pvParam){
//     while(1){
//         //;
//         printf("task1\n");
//         vTaskDelay(1000/portTICK_PERIOD_MS);
//     }
// }

// void myTask2(void *pvParam){
//     esp_task_wdt_add(NULL);//添加watch dog
//     while(1){
//         printf("task2\n");
//         esp_task_wdt_reset();//喂狗
//         vTaskDelay(1000/portTICK_PERIOD_MS);
//     }
// }

void Timer1CallBack(TimerHandle_t xTimer){
    const char *strName;
    strName = pcTimerGetName(xTimer);
    //printf("Timer Name = %s\n", strName);
    int *id;
    id = (int*)pvTimerGetTimerID(xTimer);

    printf("Timer Name = %s, id = %d\n", strName, *id);
    
}
int id1 = 1;
int id2 = 2;
void app_main(void)
{
    TimerHandle_t xTimer1;
    TimerHandle_t xTimer2;
    xTimer1 = xTimerCreate("Timer1", pdMS_TO_TICKS(1000), pdTRUE, (void*)&id1,Timer1CallBack); 
    xTimer2 = xTimerCreate("Timer2", pdMS_TO_TICKS(2000), pdTRUE, (void*)&id2,Timer1CallBack); 
    vTaskDelay(pdMS_TO_TICKS(2000));
    xTimerStart(xTimer1, 0);
    xTimerStart(xTimer2, 0);

    while(1){
        vTaskDelay(pdMS_TO_TICKS(1000));
        xTimerReset(xTimer2, 0);
    }

    // vTaskDelay(pdMS_TO_TICKS(6000));
    // xTimerStop(xTimer1, 0);
    

    // TaskHandle_t pxTask1;
    
    // xTaskCreate(myTask1, "myTask1", 1024, NULL, 0, &pxTask1);
    // xTaskCreate(myTask2, "myTask2", 1024, NULL, 0, &pxTask1);
    
    // UBaseType_t isStack;

    // while(1){
    //     isStack = uxTaskGetStackHighWaterMark(pxTask1);
    //     printf("task1 isStack = %d\n", isStack);

    //     vTaskDelay(3000/portTICK_PERIOD_MS);
    // }
}
