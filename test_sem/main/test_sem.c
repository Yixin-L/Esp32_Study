#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_log.h"

// SemaphoreHandle_t bin_sem;

// void taskA(void* param){
//     //释放信号量
//     while(1){
//         xSemaphoreGive(bin_sem);
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }
// }

// void taskB(void* param){
//     //等待信号量成功后，打印提示
//     while(1){
//         if(pdTRUE == xSemaphoreTake(bin_sem,portMAX_DELAY)){
//             ESP_LOGI("bin","task B take binsem success");
//         }
//     }
// }
// void app_main(void)
// {
//     bin_sem = xSemaphoreCreateBinary();
//     xTaskCreatePinnedToCore(taskA, "taskA",2048, NULL, 3, NULL, 1);
//     xTaskCreatePinnedToCore(taskB, "taskB",2048, NULL, 4, NULL, 1); 
// }


int iCount = 0;
SemaphoreHandle_t semphrHandle;
//任务1
void myTask1(void* pvParam){
    while(1){
        //xSemaphoreTake(semphrHandle,portMAX_DELAY);//获得信号量
        for(int i=0;i<10;i++){
            iCount++;
            printf("myTask1 iCount = %d\n",iCount);
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        //xSemaphoreGive(semphrHandle);//释放信号量
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
//任务1
void myTask2(void* pvParam){
    while(1){
        //xSemaphoreTake(semphrHandle,portMAX_DELAY);//获得信号量
        for(int i=0;i<10;i++){
            iCount++;
            printf("myTask2 iCount = %d\n",iCount);
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        //xSemaphoreGive(semphrHandle);//释放信号量
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void carInTask(void* pvParam){
    BaseType_t iResult;
    int emptySpace = 0;
    while(1){
        emptySpace = uxSemaphoreGetCount(semphrHandle);//取得当前停车位的数量
        printf("emptySpace = %d!\n",emptySpace);
        iResult = xSemaphoreTake(semphrHandle,portMAX_DELAY);//获得一个信号量
        if(iResult == pdPASS){
            printf("One Car in!\n");
        }
        else{
            printf("No Space!\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));//每1秒进一个车
    }
}

void carOutTask(void* pvParam){
    BaseType_t iResult;
    while(1){
        vTaskDelay(pdMS_TO_TICKS(6000));

        xSemaphoreGive(semphrHandle);//每6秒释放一个车位
        printf("One Car out!\n");
    }
}

//主函数
void app_main(void)
{
    //semphrHandle = xSemaphoreCreateBinary();//创建一个二进制信号量
    //xSemaphoreGive(semphrHandle);//释放信号量
    //xTaskCreate(myTask1,"myTask1",1024*5,NULL,1,NULL);
    //xTaskCreate(myTask2,"myTask2",1024*5,NULL,1,NULL);
    semphrHandle = xSemaphoreCreateCounting(5, 5);
    xTaskCreate(carInTask,"carInTask",1024*5,NULL,1,NULL);
    xTaskCreate(carOutTask,"carOutTask",1024*5,NULL,1,NULL);

    vTaskDelay(pdMS_TO_TICKS(2000));
}


