#include "drivers.h"
#include "freertos.h"

/* function including configuration of peripherals                            */
static void prvSetupHardware (void);

/* FreeRTOS tasks                                                             */
void vATaskFunction (void *pvParameters);
void vBTaskFunction (void *pvParameters);

void main (void)
{

  prvSetupHardware ();

  /* create tasks                                                             */
  xTaskCreate
  (
    vATaskFunction,           /* the function that implements the task        */
    "Task 1",                 /* the text name assigned to the task           */
    configMINIMAL_STACK_SIZE, /* the size of the stack of the task            */
    NULL,                     /* the parameter passed to the task             */
    1,                        /* the priority assigned to the task            */
    NULL                      /* the task handle                              */
  );

  xTaskCreate
  (
    vBTaskFunction,           /* the function that implements the task        */
    "Task 2",                 /* the text name assigned to the task           */
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

static void prvSetupHardware( void )
{
  /* enable clocks to all on chip peripherals                                 */
  SIM_Init (SIM_MODULE_ALL_PERIPH_ON_CONFIG);

  /* route core clock to PTF7 for monitoring                                  */
  SIM_SelClkout (CLKOUT_SRC1);
  PORT_Init (PORTF,PORT_MODULE_ALT3_MODE,PIN7);

  /* initialize LEDs on the board                                             */
  PORT_Init (PORTE, PORT_MODULE_ALT1_MODE, PIN5);
  GPIO_Init (GPIOE, GPIO_OUT_LOGIC0_MODE,  PIN5);

  PORT_Init (PORTF, PORT_MODULE_ALT1_MODE, PIN1);
  GPIO_Init (GPIOF, GPIO_OUT_LOGIC0_MODE,  PIN1);
}

void vATaskFunction (void *pvParameters)
{
  for(;;)
  {
    GPIO_Tgl (GPIOE, PIN5);

    /* task will be in blocked state for 1000ms                               */
    vTaskDelay (1000/portTICK_PERIOD_MS);
  }
}

void vBTaskFunction (void *pvParameters)
{
  for(;;)
  {
    GPIO_Tgl (GPIOF, PIN1);

    /* task will be in blocked state for 500ms                               */
    vTaskDelay (500/portTICK_PERIOD_MS);
  }
}