
#ifndef COMPOSTERAREQUIRED_H_
#define COMPOSTERAREQUIRED_H_

#include "..\inc\sc_types.h"
#include "Compostera.h"

#ifdef __cplusplus
extern "C"
{
#endif 

/*! \file This header defines prototypes for all functions that are required by the state machine implementation.

This is a state machine uses time events which require access to a timing service. Thus the function prototypes:
	- compostera_setTimer and
	- compostera_unsetTimer
are defined.

This state machine makes use of operations declared in the state machines interface or internal scopes. Thus the function prototypes:
	- composteraIface_opLED
	- composteraIface_readParameters
	- composteraIface_start_wetting
	- composteraIface_start_drying
	- composteraIface_start_cooling
	- composteraIface_stop_wetting
	- composteraIface_stop_drying
	- composteraIface_stop_cooling
are defined.

These functions will be called during a 'run to completion step' (runCycle) of the statechart. 
There are some constraints that have to be considered for the implementation of these functions:
	- never call the statechart API functions from within these functions.
	- make sure that the execution time is as short as possible.
 
*/
extern void composteraIface_opLED(const Compostera* handle, const sc_integer LEDNumber, const sc_boolean State);
extern void composteraIface_readParameters(const Compostera* handle);
extern void composteraIface_start_wetting(const Compostera* handle);
extern void composteraIface_start_drying(const Compostera* handle);
extern void composteraIface_start_cooling(const Compostera* handle);
extern void composteraIface_stop_wetting(const Compostera* handle);
extern void composteraIface_stop_drying(const Compostera* handle);
extern void composteraIface_stop_cooling(const Compostera* handle);



/*!
 * This is a timed state machine that requires timer services
 */ 

/*! This function has to set up timers for the time events that are required by the state machine. */
/*! 
	This function will be called for each time event that is relevant for a state when a state will be entered.
	\param evid An unique identifier of the event.
	\time_ms The time in milli seconds
	\periodic Indicates the the time event must be raised periodically until the timer is unset 
*/
extern void compostera_setTimer(Compostera* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic);

/*! This function has to unset timers for the time events that are required by the state machine. */
/*! 
	This function will be called for each time event taht is relevant for a state when a state will be left.
	\param evid An unique identifier of the event.
*/
extern void compostera_unsetTimer(Compostera* handle, const sc_eventid evid);



#ifdef __cplusplus
}
#endif 

#endif /* COMPOSTERAREQUIRED_H_ */
