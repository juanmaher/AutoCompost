
#ifndef COMPOSTERA_H_
#define COMPOSTERA_H_

#include "..\inc\sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'compostera'.
*/

/*! Define dimension of the state configuration vector for orthogonal states. */
#define COMPOSTERA_MAX_ORTHOGONAL_STATES 6

/*! Define maximum number of time events that can be active at once */
#define COMPOSTERA_MAX_PARALLEL_TIME_EVENTS 3

/*! Define indices of states in the StateConfVector */
#define SCVI_COMPOSTERA_HUMEDAD_HUMEDECIENDO 0
#define SCVI_COMPOSTERA_HUMEDAD_DESHUMEDECIENDO 0
#define SCVI_COMPOSTERA_HUMEDAD_ESPERANDO 0
#define SCVI_COMPOSTERA_TEMPERATURA_ENFRIANDO 1
#define SCVI_COMPOSTERA_TEMPERATURA_ESPERANDO 1
#define SCVI_COMPOSTERA_COMPOSTAR_RELLENANDO 2
#define SCVI_COMPOSTERA_COMPOSTAR_ESPERANDO 2
#define SCVI_COMPOSTERA_COMPOSTAR_SONANDO 2
#define SCVI_COMPOSTERA_COMPOSTAR_MEZCLANDO 2
#define SCVI_COMPOSTERA_SENSOR_HUMEDAD_LEYENDO 3
#define SCVI_COMPOSTERA_SENSOR_HUMEDAD_SUPERIOR 3
#define SCVI_COMPOSTERA_SENSOR_HUMEDAD_ESTABLE 3
#define SCVI_COMPOSTERA_SENSOR_HUMEDAD_INFERIOR 3
#define SCVI_COMPOSTERA_SENSOR_TEMPERATURE_LEYENDO 4
#define SCVI_COMPOSTERA_SENSOR_TEMPERATURE_SUPERIOR 4
#define SCVI_COMPOSTERA_SENSOR_TEMPERATURE_ESTABLE 4
#define SCVI_COMPOSTERA_SENSOR_LID_CERRADO 5
#define SCVI_COMPOSTERA_SENSOR_LID_ABIERTO 5
#define SCVI_COMPOSTERA_SENSOR_LID_INICIO 5

/*! Enumeration of all states */ 
typedef enum
{
	Compostera_last_state,
	Compostera_Humedad_HUMEDECIENDO,
	Compostera_Humedad_DESHUMEDECIENDO,
	Compostera_Humedad_ESPERANDO,
	Compostera_Temperatura_ENFRIANDO,
	Compostera_Temperatura_ESPERANDO,
	Compostera_Compostar_RELLENANDO,
	Compostera_Compostar_ESPERANDO,
	Compostera_Compostar_SONANDO,
	Compostera_Compostar_MEZCLANDO,
	Compostera_Sensor_Humedad_LEYENDO,
	Compostera_Sensor_Humedad_SUPERIOR,
	Compostera_Sensor_Humedad_ESTABLE,
	Compostera_Sensor_Humedad_INFERIOR,
	Compostera_Sensor_Temperature_LEYENDO,
	Compostera_Sensor_Temperature_SUPERIOR,
	Compostera_Sensor_Temperature_ESTABLE,
	Compostera_Sensor_Lid_CERRADO,
	Compostera_Sensor_Lid_ABIERTO,
	Compostera_Sensor_Lid_INICIO
} ComposteraStates;

/*! Type definition of the data structure for the ComposteraIface interface scope. */
typedef struct
{
	sc_boolean evHumedadMenor40_raised;
	sc_boolean evHumedadMayor60_raised;
	sc_boolean evHumedadEstable_raised;
	sc_boolean evTemperaturaMayor60_raised;
	sc_boolean evTemperaturaEstable_raised;
	sc_boolean evCerradoTapa_raised;
	sc_boolean evAberturaTapa_raised;
} ComposteraIface;


/* Declaration of constants for scope ComposteraIface. */
extern const sc_integer COMPOSTERA_COMPOSTERAIFACE_LEDR;
extern const sc_integer COMPOSTERA_COMPOSTERAIFACE_LEDG;
extern const sc_integer COMPOSTERA_COMPOSTERAIFACE_LEDB;
extern const sc_integer COMPOSTERA_COMPOSTERAIFACE_LED1;
extern const sc_integer COMPOSTERA_COMPOSTERAIFACE_LED2;
extern const sc_integer COMPOSTERA_COMPOSTERAIFACE_LED3;
extern const sc_boolean COMPOSTERA_COMPOSTERAIFACE_LED_ON;
extern const sc_boolean COMPOSTERA_COMPOSTERAIFACE_LED_OFF;
extern const sc_integer COMPOSTERA_COMPOSTERAIFACE_TEC1;
extern const sc_integer COMPOSTERA_COMPOSTERAIFACE_TEC2;
extern const sc_integer COMPOSTERA_COMPOSTERAIFACE_TEC3;
extern const sc_integer COMPOSTERA_COMPOSTERAIFACE_TEC4;


/*! Type definition of the data structure for the ComposteraInternal interface scope. */
typedef struct
{
	sc_boolean siTemperaturaMayor60_raised;
	sc_boolean siTemperaturaEstable_raised;
	sc_boolean siHumedadMenor40_raised;
	sc_boolean siHumedadEstable_raised;
	sc_boolean siHumedadMayor60_raised;
	sc_boolean siAberturaTapa_raised;
	sc_boolean siCerradoTapa_raised;
} ComposteraInternal;



/*! Type definition of the data structure for the ComposteraTimeEvents interface scope. */
typedef struct
{
	sc_boolean compostera_Compostar_RELLENANDO_tev0_raised;
	sc_boolean compostera_Compostar_MEZCLANDO_tev0_raised;
	sc_boolean compostera_Sensor_Humedad_SUPERIOR_tev0_raised;
	sc_boolean compostera_Sensor_Humedad_ESTABLE_tev0_raised;
	sc_boolean compostera_Sensor_Humedad_INFERIOR_tev0_raised;
	sc_boolean compostera_Sensor_Temperature_SUPERIOR_tev0_raised;
	sc_boolean compostera_Sensor_Temperature_ESTABLE_tev0_raised;
} ComposteraTimeEvents;




/*! 
 * Type definition of the data structure for the Compostera state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	ComposteraStates stateConfVector[COMPOSTERA_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	ComposteraIface iface;
	ComposteraInternal internal;
	ComposteraTimeEvents timeEvents;
} Compostera;



/*! Initializes the Compostera state machine data structures. Must be called before first usage.*/
extern void compostera_init(Compostera* handle);

/*! Activates the state machine */
extern void compostera_enter(Compostera* handle);

/*! Deactivates the state machine */
extern void compostera_exit(Compostera* handle);

/*! Performs a 'run to completion' step. */
extern void compostera_runCycle(Compostera* handle);

/*! Raises a time event. */
extern void compostera_raiseTimeEvent(Compostera* handle, sc_eventid evid);

/*! Raises the in event 'evHumedadMenor40' that is defined in the default interface scope. */ 
extern void composteraIface_raise_evHumedadMenor40(Compostera* handle);

/*! Raises the in event 'evHumedadMayor60' that is defined in the default interface scope. */ 
extern void composteraIface_raise_evHumedadMayor60(Compostera* handle);

/*! Raises the in event 'evHumedadEstable' that is defined in the default interface scope. */ 
extern void composteraIface_raise_evHumedadEstable(Compostera* handle);

/*! Raises the in event 'evTemperaturaMayor60' that is defined in the default interface scope. */ 
extern void composteraIface_raise_evTemperaturaMayor60(Compostera* handle);

/*! Raises the in event 'evTemperaturaEstable' that is defined in the default interface scope. */ 
extern void composteraIface_raise_evTemperaturaEstable(Compostera* handle);

/*! Raises the in event 'evCerradoTapa' that is defined in the default interface scope. */ 
extern void composteraIface_raise_evCerradoTapa(Compostera* handle);

/*! Raises the in event 'evAberturaTapa' that is defined in the default interface scope. */ 
extern void composteraIface_raise_evAberturaTapa(Compostera* handle);

/*! Gets the value of the variable 'LEDR' that is defined in the default interface scope. */ 
extern const sc_integer composteraIface_get_lEDR(const Compostera* handle);
/*! Gets the value of the variable 'LEDG' that is defined in the default interface scope. */ 
extern const sc_integer composteraIface_get_lEDG(const Compostera* handle);
/*! Gets the value of the variable 'LEDB' that is defined in the default interface scope. */ 
extern const sc_integer composteraIface_get_lEDB(const Compostera* handle);
/*! Gets the value of the variable 'LED1' that is defined in the default interface scope. */ 
extern const sc_integer composteraIface_get_lED1(const Compostera* handle);
/*! Gets the value of the variable 'LED2' that is defined in the default interface scope. */ 
extern const sc_integer composteraIface_get_lED2(const Compostera* handle);
/*! Gets the value of the variable 'LED3' that is defined in the default interface scope. */ 
extern const sc_integer composteraIface_get_lED3(const Compostera* handle);
/*! Gets the value of the variable 'LED_ON' that is defined in the default interface scope. */ 
extern const sc_boolean composteraIface_get_lED_ON(const Compostera* handle);
/*! Gets the value of the variable 'LED_OFF' that is defined in the default interface scope. */ 
extern const sc_boolean composteraIface_get_lED_OFF(const Compostera* handle);
/*! Gets the value of the variable 'TEC1' that is defined in the default interface scope. */ 
extern const sc_integer composteraIface_get_tEC1(const Compostera* handle);
/*! Gets the value of the variable 'TEC2' that is defined in the default interface scope. */ 
extern const sc_integer composteraIface_get_tEC2(const Compostera* handle);
/*! Gets the value of the variable 'TEC3' that is defined in the default interface scope. */ 
extern const sc_integer composteraIface_get_tEC3(const Compostera* handle);
/*! Gets the value of the variable 'TEC4' that is defined in the default interface scope. */ 
extern const sc_integer composteraIface_get_tEC4(const Compostera* handle);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean compostera_isActive(const Compostera* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean compostera_isFinal(const Compostera* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean compostera_isStateActive(const Compostera* handle, ComposteraStates state);


#ifdef __cplusplus
}
#endif 

#endif /* COMPOSTERA_H_ */
