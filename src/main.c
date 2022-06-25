/*=============================================================================
 * Author: Juan Manuel Hern�ndez <jmhernandez@fi.uba.ar>
 * Date: 2022/05/08
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "main.h"

#include "sapi.h"

/* Include statechart header file. Be sure you run the statechart C code
 * generation tool!
 */
#include "Compostera.h"
#include "TimerTicks.h"

/*==================[macros and definitions]=================================*/

#define TICKRATE_1MS	(1)				/* 1000 ticks per second */
#define TICKRATE_MS		(TICKRATE_1MS)	/* 1000 ticks per second */

#define BUTTON_1		0b0000001
#define BUTTON_2    	0b0000010
#define BUTTON_3    	0b0000100
#define BUTTON_4    	0b0001000

/*==================[internal data declaration]==============================*/

volatile bool SysTick_Time_Flag = false;

/*! This is a state machine */
static Compostera statechart;

/*! This is a timed state machine that requires timer services */
#define NOF_TIMERS (sizeof(ComposteraTimeEvents)/sizeof(sc_boolean))

TimerTicks ticks[NOF_TIMERS];

#define VENTILADOR 				GPIO0
#define SENSOR_HUMEDAD 			GPIO1
#define TAPA 					GPIO4
#define BOMBA 					GPIO7
#define BUZZER 					GPIO8

#define LED_TAPA 				LED1
#define LED_BOMBA 				LED2
#define LED_VENTILADOR 			LED3
#define LED_LECTURA_CORRECTA 	LEDG
#define LED_LECTURA_ERRONEA 	LEDR

#define TEC_BOMBA 				TEC1
#define TEC_VENTILADOR 			TEC2

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

static float humidity = 0;
static float temperature = 0;

typedef enum {
	HIGH_TEMPERATURE,
	HIGH_HUMIDITY,
	LOW_HUMIDITY,
	STABLE_PARAMETERS,
	INIT_STATUS,
	ERROR_READING,
	HIGH_PARAMETERS
} status_t;

status_t status;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*! \file This header defines prototypes for all functions that are required
 *  by the state machine implementation.
 *
 *  This state machine makes use of operations declared in the state machines
 *  interface or internal scopes. Thus the function prototypes:
 *  - composteraIface_opLED
 *  are defined.
 *
 *  These functions will be called during a 'run to completion step' (runCycle)
 *  of the statechart.
 *  There are some constraints that have to be considered for the
 *  implementation of these functions:
 *  - never call the statechart API functions from within these functions.
 *  - make sure that the execution time is as short as possible.
 */

/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */

void composteraIface_opLED( Compostera* handle, sc_integer LEDNumber, sc_boolean State )
{
	gpioWrite( (LEDR + LEDNumber), State );
}


/*! * This is a timed state machine that requires timer services
 */

/*! This function has to set up timers for the time events that are required
 *  by the state machine.
 */
/*! This function will be called for each time event that is relevant for a
 *  state when a state will be entered.
 *  \param evid An unique identifier of the event.
 *  \time_ms The time in milli seconds
 *  \periodic Indicates the the time event must be raised periodically until
 *   the timer is unset
 */
void compostera_setTimer( Compostera* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic )
{
	SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
}

/*! This function has to unset timers for the time events that are required
 *  by the state machine.
 */
/*! This function will be called for each time event that is relevant for a
 *  state when a state will be left.
 *  \param evid An unique identifier of the event.
 */
void compostera_unsetTimer( Compostera* handle, const sc_eventid evid )
{
	UnsetTimerTick( ticks, NOF_TIMERS, evid );
}


/**
 * @brief	Hook on Handle interrupt from SysTick timer
 * @return	Nothing
 */
void myTickHook( void *ptr ){

	/* The sysTick Interrupt Handler only set a Flag */
	SysTick_Time_Flag = true;
}


void gpio_init() {
	gpioInit( TAPA, GPIO_INPUT );
	gpioInit( BOMBA, GPIO_OUTPUT );
	gpioInit( VENTILADOR, GPIO_OUTPUT );
	gpioInit( TEC_BOMBA, GPIO_INPUT );
	gpioInit( TEC2, GPIO_INPUT );
	gpioInit( BUZZER, GPIO_OUTPUT );
}

#define HIGH_TEMPERATURE_VALUE	30
#define HIGH_HUMIDITY_VALUE		70
#define LOW_HUMIDITY_VALUE		40

void composteraIface_readParameters(Compostera* handle) {

	if(dht11Read(&humidity, &temperature)) {
		gpioWrite( LED_LECTURA_CORRECTA, ON );
		gpioWrite( LED_LECTURA_ERRONEA, OFF );
		printf( "Temperatura: %d grados C.\r\n", (int) temperature );
		printf( "Humedad: %d  %.\r\n\r\n", (int) humidity );
		if(temperature > HIGH_TEMPERATURE_VALUE && humidity > HIGH_HUMIDITY_VALUE) {
			status = HIGH_PARAMETERS;
		} else if (temperature > HIGH_TEMPERATURE_VALUE) {
			status = HIGH_TEMPERATURE;
		} else if (humidity > HIGH_HUMIDITY_VALUE) {
			status = HIGH_HUMIDITY;
		} else if (humidity < LOW_HUMIDITY_VALUE) {
			status = LOW_HUMIDITY;
		} else status = STABLE_PARAMETERS;
	} else {
		gpioWrite( LED_LECTURA_ERRONEA, ON );
		gpioWrite( LED_LECTURA_CORRECTA, OFF );
		status = ERROR_READING;
		printf( "Error al leer DHT11.\r\n\r\n");
	}
}

void stop_automatic_control() {
	gpioWrite( LED_TAPA, ON );
	gpioWrite( BOMBA, ON );
	gpioWrite( VENTILADOR, ON );
	gpioWrite( BUZZER, ON );
}


/**
 * @brief	main routine for statechart example: EDU-CIAA-NXP - Compostera
 * @return	Function should not exit.
 */
int main(void)
{
	uint32_t i;

	/* Generic Initialization */
	boardConfig();

	gpio_init();

	uartConfig( UART_USB, 115200 ); // Inicializar periferico UART_USB

	dht11Init( GPIO1 ); // Inicializo el sensor DHT11

	/* Init Ticks counter => TICKRATE_MS */
	tickConfig( TICKRATE_MS );

	/* Add Tick Hook */
	tickCallbackSet( myTickHook, (void*)NULL );

	/* Init Timer Ticks */
	InitTimerTicks( ticks, NOF_TIMERS );

	/* Statechart Initialization */
	compostera_init( &statechart );
	compostera_enter( &statechart );

	composteraIface_raise_evParametrosEstable(&statechart);

	/* LED state is toggled in the main program */
	while (1) {
		/* The uC sleeps waiting for an interruption */
		__WFI();


		/* When a interrupt wakes to the uC, the main program validates it,
		 * checking the waited Flag */
		if (SysTick_Time_Flag == true) {

			/* Then reset its Flag */
			SysTick_Time_Flag = false;

			/* Then Update all Timer Ticks */
			UpdateTimers( ticks, NOF_TIMERS );

			/* Then Scan all Timer Ticks */
			for (i = 0; i < NOF_TIMERS; i++) {

				/* Then if there are pending events */
				if (IsPendEvent( ticks, NOF_TIMERS, ticks[i].evid ) == true) {

					/* Then Raise an Event -> Ticks.evid => OK */
					compostera_raiseTimeEvent( &statechart, ticks[i].evid );

					/* Then Mark as Attached -> Ticks.evid => OK */
					MarkAsAttEvent( ticks, NOF_TIMERS, ticks[i].evid );

				}
			}

			if(gpioRead( TAPA )){
				stop_automatic_control();
				composteraIface_raise_evAberturaTapa(&statechart);
			}else{
				composteraIface_raise_evCerradoTapa(&statechart);

				gpioWrite( LED_TAPA, OFF );


				switch(status) {
					case INIT_STATUS:
						break;
					case STABLE_PARAMETERS:
						if(!gpioRead( TEC_BOMBA )){
							gpioWrite( BOMBA, OFF );
							gpioWrite( LED_BOMBA, OFF );
						}else{
							gpioWrite( BOMBA, ON );
							gpioWrite( LED_BOMBA, ON );
						}

						if(!gpioRead( TEC_VENTILADOR )){
							gpioWrite( VENTILADOR, OFF );
							gpioWrite( LED_VENTILADOR, OFF );
						}else{
							gpioWrite( VENTILADOR, ON );
							gpioWrite( LED_VENTILADOR, ON );
						}
						//composteraIface_raise_evParametrosEstable(&statechart);

						break;
					case HIGH_TEMPERATURE:
						//composteraIface_raise_evTemperaturaMayor60(&statechart);
						gpioWrite( VENTILADOR, OFF );
						gpioWrite( BOMBA, ON );
						break;
					case LOW_HUMIDITY:
						//composteraIface_raise_evHumedadMenor40(&statechart);
						gpioWrite( BOMBA, OFF );
						gpioWrite( VENTILADOR, ON );
						break;
					case HIGH_HUMIDITY:
						//composteraIface_raise_evHumedadMayor60(&statechart);
						gpioWrite( VENTILADOR, OFF );
						gpioWrite( BOMBA, ON );
						break;
					case HIGH_PARAMETERS:
						//composteraIface_raise_evParametrosExcedidos(&statechart);
						gpioWrite( VENTILADOR, OFF );
						gpioWrite( BOMBA, OFF );
						break;
					case ERROR_READING:
						//composteraIface_raise_evLecturaErronea(&statechart);
						gpioWrite( BOMBA, ON );
						gpioWrite( VENTILADOR, ON );
						break;
					default:
						break;
				}

				gpioWrite( BUZZER, OFF );
			}

//			delay(500);
//			printf( "Temperatura: %d grados C.\r\n", (int) temperature );
//			printf( "Humedad: %d  %.\r\n\r\n", (int) humidity );
			/* Then Run an Cycle of Statechart */
			compostera_runCycle(&statechart);		// Run Cycle of Statechart
		}
	}
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/
