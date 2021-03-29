#include "drivers.h"
#include "freertos.h"

/* PIT callback declarations                                                  */
void pit_callback (PIT_CALLBACK_TYPE type);

/* function including configuration of peripherals                            */
static void prvSetupHardware (void);

/* PIT interrupt handler task                                                 */
static void prvHandlerTask (void * pvParameters);

/* task notification handler                                                  */
TaskHandle_t xTaskToNotify = NULL;

void main (void)
{
  prvSetupHardware ();

  /* create task*/
  xTaskCreate
  (
    prvHandlerTask,           /* the function that implements the task        */
    "Handler Task",           /* the text name assigned to the task           */
    configMINIMAL_STACK_SIZE, /* the size of the stack of the task            */
    NULL,                     /* the parameter passed to the task             */
    1,                        /* the priority assigned to the task            */
    NULL                      /* the task handle                              */
  );

  /* start the tasks and timer running including enabling all interrupts      */
  vTaskStartScheduler ();

  /* this loop will never be reached                                          */
  while(1);
}


void prvSetupHardware( void ){

  /* enable clocks to all on chip peripherals                                 */
  SIM_Init (SIM_MODULE_ALL_PERIPH_ON_CONFIG);

  /* initialize led                                                           */
  PORT_Init (PORTE, PORT_MODULE_ALT1_MODE, PIN5);
  GPIO_Init (GPIOE, GPIO_OUT_LOGIC1_MODE , PIN5);

  /* initialize PIT                                                           */
  PIT_InstallCallback (PRI_LVL2, pit_callback);
  PIT_Init (PIT0, CH0, PIT_CH_TMR_EN_CONFIG, 1000000);
}

static void prvHandlerTask (void *pvParameters)
{
  xTaskToNotify = xTaskGetCurrentTaskHandle ();
  for(;;)
  {
    /* task is blocked until gets notification                                */
    ulTaskNotifyTake (pdTRUE, portMAX_DELAY);
    GPIO_Tgl (GPIOE, PIN5);
  }
}

void pit_callback (PIT_CALLBACK_TYPE type)
{
  if (type == PIT0CH0_CALLBACK)
  {
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    /* test if the xTaskToNotify isn't NULL.                                  */
    configASSERT (xTaskToNotify != NULL);

    /* notify handler task                                                    */
    vTaskNotifyGiveFromISR (xTaskToNotify, &xHigherPriorityTaskWoken);

    /* switch task                                                            */
    portEND_SWITCHING_ISR (xHigherPriorityTaskWoken);
  }
}