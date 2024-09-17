#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
// #include "freertos/event_groups.h"

// EventGroupHandle_t xCreatedEventGroup;
// #define BIT_0 ( 1 << 0 ) //标志位第0位
// #define BIT_4 ( 1 << 4 ) //标志位第4位

static TaskHandle_t xTask1 = NULL;
void Task1(void *pvParam)
{
    while (1)
    {
        printf("-----------\n");
        // printf("task1 begin to wait!\n");
        //  xEventGroupWaitBits(
        //              xCreatedEventGroup, /* 事件组 */
        //              BIT_0 | BIT_4, /* 事件组需要等待的bits位 */
        //              pdTRUE, /* 在函数返回时会被清除（重新等待） */
        //              pdFALSE, /* '或'的设置(pdFALSE)，只要有一个bit使能就停止阻塞   '与'的设置(pdTRUE),两个bit同时使能才能停止阻塞*/
        //              portMAX_DELAY);
        //  printf("-----------\n");
        //  printf("In task1, BIT0 or BIT4 is set!\n");
        //  vTaskDelay(pdMS_TO_TICKS(1000));

        printf("Task 1 wait notification!\n");
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("-------------\n");
        printf("Task1 got notification!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Task2(void *pvParam)
{
    // vTaskDelay(pdMS_TO_TICKS(1000));//阻塞，让Task1有时间优先运行
    while (1)
    {
        // printf("-----------\n");
        //  printf("task2 begin to set bit0!\n");
        //  xEventGroupSetBits(xCreatedEventGroup,BIT_0);
        //  vTaskDelay(pdMS_TO_TICKS(5000));

        // printf("-----------\n");
        // printf("task2 begin to set bit4!\n");
        // xEventGroupSetBits(xCreatedEventGroup,BIT_4);
        // vTaskDelay(pdMS_TO_TICKS(5000));

        vTaskDelay(pdMS_TO_TICKS(5000));
        printf("-------------\n");
        printf("Task2 notify Task1!\n");
        xTaskNotifyGive(xTask1);
    }
}

void app_main(void)
{
    // xCreatedEventGroup = xEventGroupCreate();
    //  if(xCreatedEventGroup == NULL){
    //      printf("Event Group create fail!\n");
    //  }else{
    //      vTaskSuspendAll();
    //      xTaskCreate(Task1, "Task1", 1024*5, NULL, 1, NULL);
    //      xTaskCreate(Task2, "Task2", 1024*5, NULL, 1, NULL);
    //      xTaskResumeAll();
    //  }

    vTaskSuspendAll(); // 挂起所有任务，任务创建完再按照优先级依次操作
    xTaskCreate(Task1, "Task1", 1024 * 5, NULL, 1, &xTask1); // 传出Task1的任务句柄
    xTaskCreate(Task2, "Task2", 1024 * 5, NULL, 1, NULL);
    xTaskResumeAll(); // 开启任务调度器
}
