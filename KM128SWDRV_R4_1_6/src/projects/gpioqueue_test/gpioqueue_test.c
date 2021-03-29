#include "drivers.h"
#include "freertos.h"

/* values passed to the two tasks just to check the task parameter            */
#define mainQUEUE_TX_PARAM    (0xAAUL)
#define mainQUEUE_RX_PARAM    (0xBBUL)

/* function including configuration of peripherals                            */
static void prvSetupHardware( void );

/* FreeRTOS tasks                                                             */
static void prvQueueRxTask (void *pvParameters);
static void prvQueueTxTask (void *pvParameters);

/* queue handler.                                                             */
static QueueHandle_t xQueue = NULL;

void main (void)
{
  prvSetupHardware ();

  /* create the queue of length 1.                                            */
  xQueue = xQueueCreate (1, sizeof(unsigned long));

  if (xQueue != NULL)
  {
    /* create tasks.                                                          */
    xTaskCreate
    (
      prvQueueRxTask,             /* the function that implements the task    */
      "Receive task",             /* the text name assigned to the task       */
      configMINIMAL_STACK_SIZE,   /* the size of the stack of the task        */
      (void*)mainQUEUE_RX_PARAM,  /* the parameter passed to the task         */
      2,                          /* the priority assigned to the task        */
      NULL                        /* the task handle                          */
    );

    xTaskCreate
    (
      prvQueueTxTask,             /* the function that implements the task    */
      "Transmit task",            /* the text name assigned to the task       */
      configMINIMAL_STACK_SIZE,   /* the size of the stack of the task        */
      (void*)mainQUEUE_TX_PARAM,  /* the parameter passed to the task         */
      1,                          /* the priority assigned to the task        */
      NULL                        /* the task handle                          */
    );

    /* start the tasks and timer running including enabling all interrupts    */
    vTaskStartScheduler ();
  }

  /* this loop will never be reached                                          */
  while(1);
}

static void prvSetupHardware (void)
{
  /* enable clocks to all on chip peripherals                                 */
  SIM_Init (SIM_MODULE_ALL_PERIPH_ON_CONFIG);

  /* initialize LED on the board                                              */
  PORT_Init (PORTE, PORT_MODULE_LED_MODE, PIN5);
  GPIO_Init (GPIOE, GPIO_OUT_LOGIC0_MODE, PIN5);
}

static void prvQueueTxTask( void *pvParameters )
{
  TickType_t xNextWakeTime;
  const unsigned long ulTxValue = 100;

  /* check the task parameter is as expected                                  */
  configASSERT (((unsigned long)pvParameters) == mainQUEUE_TX_PARAM);

  /* initialise xNextWakeTime.                                                */
  xNextWakeTime = xTaskGetTickCount ();

  for( ;; )
  {
    /* the task is blocked for 500ms                                          */
    vTaskDelayUntil (&xNextWakeTime, 500/portTICK_PERIOD_MS);

    /* send data to queue for unblocking the receive task                     */
    xQueueSend (xQueue, &ulTxValue, 0U);
  }
}

static void prvQueueRxTask (void *pvParameters)
{
  unsigned long ulRxValue;

  /* check the task parameter is as expected                                  */
  configASSERT (((unsigned long)pvParameters) == mainQUEUE_RX_PARAM);

  for( ;; )
  {
    /* wait until something arrives in the queue - this task will block
    indefinitely provided INCLUDE_vTaskSuspend is set to 1 in freertos_cfg.h  */
    xQueueReceive (xQueue, &ulRxValue, portMAX_DELAY);

    /*  check the received value.                                             */
    if( ulRxValue == 100UL )
    {
      /* toggle the LED                                                       */
      GPIO_Tgl (GPIOE, PIN5);
      ulRxValue = 0U;
    }
  }
}
