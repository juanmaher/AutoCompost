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


/*! This function scan all EDU-CIAA-NXP buttons (TEC1, TEC2, TEC3 and TEC4),
 *  and return ID of pressed button (TEC1 or TEC2 or TEC3 or TEC4)
 *  or false if no button was pressed.
 */
uint32_t Buttons_GetStatus_(void) {
	uint8_t ret = false;
	uint32_t idx;

	for (idx = 1; idx < 4; ++idx) {
		if (gpioRead( TEC1 + idx ) == 0)
			ret |= 1 << idx;
	}

	return ret;
}

/*! This function scan all EDU-CIAA-NXP button TEC1
 *  and return ID of pressed button TEC1
 *  or false if no button was pressed.
 */
bool_t Button1_GetStatus_(void) {
	return !gpioRead( TEC1 );
}

void gpio_init() {
	gpioInit( GPIO2, GPIO_INPUT );
}

void composteraIface_readParameters(Compostera* handle) {

//	if(dht11Read(&humidity, &temperature)) {
//		// Si leyo bien prendo el LEDG y enciendo el LEDR
//		gpioWrite( LEDG, ON );
//		gpioWrite( LEDR, OFF );
//
////		 int number = 252;
////		 char buf[10];
////		 sprintf (buf, "%f", number);
////		 printf( "numero random %d \r\n", number);
//
//
//		// Informo los valores de los sensores
////		printf( "Temperatura: %d grados C.\r\n", (int) temperature );
////		printf( "Humedad: %d  %.\r\n\r\n", (int) humidity );
//
//	} else {
//		// Si leyo mal apago el LEDG y enciendo el LEDR
//		gpioWrite( LEDG, OFF );
//		gpioWrite( LEDR, ON );
//		// Informo el error de lectura
//		printf( "Error al leer DHT11.\r\n\r\n");
//
//	}
	if(dht11Read(&humidity, &temperature)) {
		printf( "Temperatura: %d grados C.\r\n", (int) temperature );
		printf( "Humedad: %d  %.\r\n\r\n", (int) humidity );
		if(temperature > 30 && humidity > 60) {
			status = HIGH_PARAMETERS;
		} else if (temperature > 30) {
			status = HIGH_TEMPERATURE;
		} else if (humidity > 60) {
			status = HIGH_HUMIDITY;
		} else if (humidity < 30) {
			status = LOW_HUMIDITY;
		} else status = STABLE_PARAMETERS;
	} else {
		status = ERROR_READING;
		printf( "Error al leer DHT11.\r\n\r\n");
	}
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

			/* Then Get status of buttons */
//			BUTTON_Status = Buttons_GetStatus_();
//			BUTTON_1_Status = Button1_GetStatus_();
//
//			if (BUTTON_1_Status != 0) {
//				composteraIface_raise_evTEC1Oprimido(&statechart);
//				BUTTON_1_Press = 1;
//				BUTTON_Press = BUTTON_1;
//			} else {
//				if (BUTTON_Status != 0 && BUTTON_1_Press != 1) {
//					switch (BUTTON_Status) {
//						case BUTTON_2:
//							composteraIface_raise_evTEC2Oprimido(&statechart);
//							BUTTON_Press = BUTTON_2;
//							break;
//						case BUTTON_3:
//							composteraIface_raise_evTEC3Oprimido(&statechart);
//							BUTTON_Press = BUTTON_3;
//							break;
//						case BUTTON_4:
//							composteraIface_raise_evTEC4Oprimido(&statechart);
//							BUTTON_Press = BUTTON_4;
//							break;
//					}
//
//				} else {
//					switch (BUTTON_Press) {
//						case BUTTON_1:
//							composteraIface_raise_evTEC1NoOprimido(&statechart);
//							BUTTON_1_Press = 0;
//							break;
//						case BUTTON_2:
//							composteraIface_raise_evTEC2NoOprimido(&statechart);
//							break;
//						case BUTTON_3:
//							composteraIface_raise_evTEC3NoOprimido(&statechart);
//							break;
//						case BUTTON_4:
//							composteraIface_raise_evTEC4NoOprimido(&statechart);
//							break;
//					}
//				}
//			}

//			if( !gpioRead(GPIO2) ) {
//				composteraIface_raise_evAberturaTapa(&statechart);
//			}

			switch(status) {
				case INIT_STATUS:
					break;
				case STABLE_PARAMETERS:
					gpioWrite( LEDG, ON );
					composteraIface_raise_evParametrosEstable(&statechart);
					break;
				case HIGH_TEMPERATURE:
					composteraIface_raise_evTemperaturaMayor60(&statechart);
					break;
				case LOW_HUMIDITY:
					composteraIface_raise_evHumedadMenor40(&statechart);
					break;
				case HIGH_HUMIDITY:
					composteraIface_raise_evHumedadMayor60(&statechart);
					break;
				case HIGH_PARAMETERS:
					composteraIface_raise_evParametrosExcedidos(&statechart);
					break;
				case ERROR_READING:
					gpioWrite( LEDR, ON );
					composteraIface_raise_evLecturaErronea(&statechart);
					break;
				default:
					break;
			}

			/* Then Run an Cycle of Statechart */
			compostera_runCycle(&statechart);		// Run Cycle of Statechart
		}
	}
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/
