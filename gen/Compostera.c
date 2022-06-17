
#include "Compostera.h"
#include "..\inc\sc_types.h"
#include "ComposteraRequired.h"

#include <stdlib.h>
#include <string.h>
/*! \file Implementation of the state machine 'compostera'
*/

/* prototypes of all internal functions */
static sc_boolean check_Humedad_HUMEDECIENDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Humedad_HUMEDECIENDO_tr1_tr1(const Compostera* handle);
static sc_boolean check_Humedad_DESHUMEDECIENDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Humedad_DESHUMEDECIENDO_tr1_tr1(const Compostera* handle);
static sc_boolean check_Humedad_ESPERANDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Humedad_ESPERANDO_tr1_tr1(const Compostera* handle);
static sc_boolean check_Temperatura_ENFRIANDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Temperatura_ENFRIANDO_tr1_tr1(const Compostera* handle);
static sc_boolean check_Temperatura_ESPERANDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Compostar_RELLENANDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Compostar_RELLENANDO_tr1_tr1(const Compostera* handle);
static sc_boolean check_Compostar_ESPERANDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Compostar_SONANDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Compostar_MEZCLANDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Compostar_MEZCLANDO_tr1_tr1(const Compostera* handle);
static sc_boolean check_Sensor_Humedad_LEYENDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Sensor_Humedad_LEYENDO_tr1_tr1(const Compostera* handle);
static sc_boolean check_Sensor_Humedad_LEYENDO_tr2_tr2(const Compostera* handle);
static sc_boolean check_Sensor_Humedad_SUPERIOR_tr0_tr0(const Compostera* handle);
static sc_boolean check_Sensor_Humedad_ESTABLE_tr0_tr0(const Compostera* handle);
static sc_boolean check_Sensor_Humedad_INFERIOR_tr0_tr0(const Compostera* handle);
static sc_boolean check_Sensor_Temperature_LEYENDO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Sensor_Temperature_LEYENDO_tr1_tr1(const Compostera* handle);
static sc_boolean check_Sensor_Temperature_SUPERIOR_tr0_tr0(const Compostera* handle);
static sc_boolean check_Sensor_Temperature_ESTABLE_tr0_tr0(const Compostera* handle);
static sc_boolean check_Sensor_Lid_CERRADO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Sensor_Lid_ABIERTO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Sensor_Lid_INICIO_tr0_tr0(const Compostera* handle);
static sc_boolean check_Sensor_Lid_INICIO_tr1_tr1(const Compostera* handle);
static void effect_Humedad_HUMEDECIENDO_tr0(Compostera* handle);
static void effect_Humedad_HUMEDECIENDO_tr1(Compostera* handle);
static void effect_Humedad_DESHUMEDECIENDO_tr0(Compostera* handle);
static void effect_Humedad_DESHUMEDECIENDO_tr1(Compostera* handle);
static void effect_Humedad_ESPERANDO_tr0(Compostera* handle);
static void effect_Humedad_ESPERANDO_tr1(Compostera* handle);
static void effect_Temperatura_ENFRIANDO_tr0(Compostera* handle);
static void effect_Temperatura_ENFRIANDO_tr1(Compostera* handle);
static void effect_Temperatura_ESPERANDO_tr0(Compostera* handle);
static void effect_Compostar_RELLENANDO_tr0(Compostera* handle);
static void effect_Compostar_RELLENANDO_tr1(Compostera* handle);
static void effect_Compostar_ESPERANDO_tr0(Compostera* handle);
static void effect_Compostar_SONANDO_tr0(Compostera* handle);
static void effect_Compostar_MEZCLANDO_tr0(Compostera* handle);
static void effect_Compostar_MEZCLANDO_tr1(Compostera* handle);
static void effect_Sensor_Humedad_LEYENDO_tr0(Compostera* handle);
static void effect_Sensor_Humedad_LEYENDO_tr1(Compostera* handle);
static void effect_Sensor_Humedad_LEYENDO_tr2(Compostera* handle);
static void effect_Sensor_Humedad_SUPERIOR_tr0(Compostera* handle);
static void effect_Sensor_Humedad_ESTABLE_tr0(Compostera* handle);
static void effect_Sensor_Humedad_INFERIOR_tr0(Compostera* handle);
static void effect_Sensor_Temperature_LEYENDO_tr0(Compostera* handle);
static void effect_Sensor_Temperature_LEYENDO_tr1(Compostera* handle);
static void effect_Sensor_Temperature_SUPERIOR_tr0(Compostera* handle);
static void effect_Sensor_Temperature_ESTABLE_tr0(Compostera* handle);
static void effect_Sensor_Lid_CERRADO_tr0(Compostera* handle);
static void effect_Sensor_Lid_ABIERTO_tr0(Compostera* handle);
static void effect_Sensor_Lid_INICIO_tr0(Compostera* handle);
static void effect_Sensor_Lid_INICIO_tr1(Compostera* handle);
static void enact_Temperatura_ENFRIANDO(Compostera* handle);
static void enact_Temperatura_ESPERANDO(Compostera* handle);
static void enact_Compostar_RELLENANDO(Compostera* handle);
static void enact_Compostar_ESPERANDO(Compostera* handle);
static void enact_Compostar_SONANDO(Compostera* handle);
static void enact_Compostar_MEZCLANDO(Compostera* handle);
static void enact_Sensor_Humedad_SUPERIOR(Compostera* handle);
static void enact_Sensor_Humedad_ESTABLE(Compostera* handle);
static void enact_Sensor_Humedad_INFERIOR(Compostera* handle);
static void enact_Sensor_Temperature_SUPERIOR(Compostera* handle);
static void enact_Sensor_Temperature_ESTABLE(Compostera* handle);
static void enact_Sensor_Lid_CERRADO(Compostera* handle);
static void enact_Sensor_Lid_ABIERTO(Compostera* handle);
static void exact_Compostar_RELLENANDO(Compostera* handle);
static void exact_Compostar_MEZCLANDO(Compostera* handle);
static void exact_Sensor_Humedad_SUPERIOR(Compostera* handle);
static void exact_Sensor_Humedad_ESTABLE(Compostera* handle);
static void exact_Sensor_Humedad_INFERIOR(Compostera* handle);
static void exact_Sensor_Temperature_SUPERIOR(Compostera* handle);
static void exact_Sensor_Temperature_ESTABLE(Compostera* handle);
static void enseq_Humedad_HUMEDECIENDO_default(Compostera* handle);
static void enseq_Humedad_DESHUMEDECIENDO_default(Compostera* handle);
static void enseq_Humedad_ESPERANDO_default(Compostera* handle);
static void enseq_Temperatura_ENFRIANDO_default(Compostera* handle);
static void enseq_Temperatura_ESPERANDO_default(Compostera* handle);
static void enseq_Compostar_RELLENANDO_default(Compostera* handle);
static void enseq_Compostar_ESPERANDO_default(Compostera* handle);
static void enseq_Compostar_SONANDO_default(Compostera* handle);
static void enseq_Compostar_MEZCLANDO_default(Compostera* handle);
static void enseq_Sensor_Humedad_LEYENDO_default(Compostera* handle);
static void enseq_Sensor_Humedad_SUPERIOR_default(Compostera* handle);
static void enseq_Sensor_Humedad_ESTABLE_default(Compostera* handle);
static void enseq_Sensor_Humedad_INFERIOR_default(Compostera* handle);
static void enseq_Sensor_Temperature_LEYENDO_default(Compostera* handle);
static void enseq_Sensor_Temperature_SUPERIOR_default(Compostera* handle);
static void enseq_Sensor_Temperature_ESTABLE_default(Compostera* handle);
static void enseq_Sensor_Lid_CERRADO_default(Compostera* handle);
static void enseq_Sensor_Lid_ABIERTO_default(Compostera* handle);
static void enseq_Sensor_Lid_INICIO_default(Compostera* handle);
static void enseq_Humedad_default(Compostera* handle);
static void enseq_Temperatura_default(Compostera* handle);
static void enseq_Compostar_default(Compostera* handle);
static void enseq_Sensor_Humedad_default(Compostera* handle);
static void enseq_Sensor_Temperature_default(Compostera* handle);
static void enseq_Sensor_Lid_default(Compostera* handle);
static void exseq_Humedad_HUMEDECIENDO(Compostera* handle);
static void exseq_Humedad_DESHUMEDECIENDO(Compostera* handle);
static void exseq_Humedad_ESPERANDO(Compostera* handle);
static void exseq_Temperatura_ENFRIANDO(Compostera* handle);
static void exseq_Temperatura_ESPERANDO(Compostera* handle);
static void exseq_Compostar_RELLENANDO(Compostera* handle);
static void exseq_Compostar_ESPERANDO(Compostera* handle);
static void exseq_Compostar_SONANDO(Compostera* handle);
static void exseq_Compostar_MEZCLANDO(Compostera* handle);
static void exseq_Sensor_Humedad_LEYENDO(Compostera* handle);
static void exseq_Sensor_Humedad_SUPERIOR(Compostera* handle);
static void exseq_Sensor_Humedad_ESTABLE(Compostera* handle);
static void exseq_Sensor_Humedad_INFERIOR(Compostera* handle);
static void exseq_Sensor_Temperature_LEYENDO(Compostera* handle);
static void exseq_Sensor_Temperature_SUPERIOR(Compostera* handle);
static void exseq_Sensor_Temperature_ESTABLE(Compostera* handle);
static void exseq_Sensor_Lid_CERRADO(Compostera* handle);
static void exseq_Sensor_Lid_ABIERTO(Compostera* handle);
static void exseq_Sensor_Lid_INICIO(Compostera* handle);
static void exseq_Humedad(Compostera* handle);
static void exseq_Temperatura(Compostera* handle);
static void exseq_Compostar(Compostera* handle);
static void exseq_Sensor_Humedad(Compostera* handle);
static void exseq_Sensor_Temperature(Compostera* handle);
static void exseq_Sensor_Lid(Compostera* handle);
static void react_Humedad_HUMEDECIENDO(Compostera* handle);
static void react_Humedad_DESHUMEDECIENDO(Compostera* handle);
static void react_Humedad_ESPERANDO(Compostera* handle);
static void react_Temperatura_ENFRIANDO(Compostera* handle);
static void react_Temperatura_ESPERANDO(Compostera* handle);
static void react_Compostar_RELLENANDO(Compostera* handle);
static void react_Compostar_ESPERANDO(Compostera* handle);
static void react_Compostar_SONANDO(Compostera* handle);
static void react_Compostar_MEZCLANDO(Compostera* handle);
static void react_Sensor_Humedad_LEYENDO(Compostera* handle);
static void react_Sensor_Humedad_SUPERIOR(Compostera* handle);
static void react_Sensor_Humedad_ESTABLE(Compostera* handle);
static void react_Sensor_Humedad_INFERIOR(Compostera* handle);
static void react_Sensor_Temperature_LEYENDO(Compostera* handle);
static void react_Sensor_Temperature_SUPERIOR(Compostera* handle);
static void react_Sensor_Temperature_ESTABLE(Compostera* handle);
static void react_Sensor_Lid_CERRADO(Compostera* handle);
static void react_Sensor_Lid_ABIERTO(Compostera* handle);
static void react_Sensor_Lid_INICIO(Compostera* handle);
static void react_Humedad__entry_Default(Compostera* handle);
static void react_Temperatura__entry_Default(Compostera* handle);
static void react_Compostar__entry_Default(Compostera* handle);
static void react_Sensor_Humedad__entry_Default(Compostera* handle);
static void react_Sensor_Temperature__entry_Default(Compostera* handle);
static void react_Sensor_Lid__entry_Default(Compostera* handle);
static void clearInEvents(Compostera* handle);
static void clearOutEvents(Compostera* handle);

const sc_integer COMPOSTERA_COMPOSTERAIFACE_LEDR = 0;
const sc_integer COMPOSTERA_COMPOSTERAIFACE_LEDG = 1;
const sc_integer COMPOSTERA_COMPOSTERAIFACE_LEDB = 2;
const sc_integer COMPOSTERA_COMPOSTERAIFACE_LED1 = 3;
const sc_integer COMPOSTERA_COMPOSTERAIFACE_LED2 = 4;
const sc_integer COMPOSTERA_COMPOSTERAIFACE_LED3 = 5;
const sc_boolean COMPOSTERA_COMPOSTERAIFACE_LED_ON = bool_true;
const sc_boolean COMPOSTERA_COMPOSTERAIFACE_LED_OFF = bool_false;
const sc_integer COMPOSTERA_COMPOSTERAIFACE_TEC1 = 1 << 0;
const sc_integer COMPOSTERA_COMPOSTERAIFACE_TEC2 = 1 << 1;
const sc_integer COMPOSTERA_COMPOSTERAIFACE_TEC3 = 1 << 2;
const sc_integer COMPOSTERA_COMPOSTERAIFACE_TEC4 = 1 << 3;

void compostera_init(Compostera* handle)
{
		sc_integer i;
	
		for (i = 0; i < COMPOSTERA_MAX_ORTHOGONAL_STATES; ++i)
		{
			handle->stateConfVector[i] = Compostera_last_state;
		}
		
		
		handle->stateConfVectorPosition = 0;
	
		clearInEvents(handle);
		clearOutEvents(handle);
	
}

void compostera_enter(Compostera* handle)
{
	/* Default enter sequence for statechart compostera */
	enseq_Humedad_default(handle);
	enseq_Temperatura_default(handle);
	enseq_Compostar_default(handle);
	enseq_Sensor_Humedad_default(handle);
	enseq_Sensor_Temperature_default(handle);
	enseq_Sensor_Lid_default(handle);
}

void compostera_runCycle(Compostera* handle)
{
	clearOutEvents(handle);
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < COMPOSTERA_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case Compostera_Humedad_HUMEDECIENDO:
		{
			react_Humedad_HUMEDECIENDO(handle);
			break;
		}
		case Compostera_Humedad_DESHUMEDECIENDO:
		{
			react_Humedad_DESHUMEDECIENDO(handle);
			break;
		}
		case Compostera_Humedad_ESPERANDO:
		{
			react_Humedad_ESPERANDO(handle);
			break;
		}
		case Compostera_Temperatura_ENFRIANDO:
		{
			react_Temperatura_ENFRIANDO(handle);
			break;
		}
		case Compostera_Temperatura_ESPERANDO:
		{
			react_Temperatura_ESPERANDO(handle);
			break;
		}
		case Compostera_Compostar_RELLENANDO:
		{
			react_Compostar_RELLENANDO(handle);
			break;
		}
		case Compostera_Compostar_ESPERANDO:
		{
			react_Compostar_ESPERANDO(handle);
			break;
		}
		case Compostera_Compostar_SONANDO:
		{
			react_Compostar_SONANDO(handle);
			break;
		}
		case Compostera_Compostar_MEZCLANDO:
		{
			react_Compostar_MEZCLANDO(handle);
			break;
		}
		case Compostera_Sensor_Humedad_LEYENDO:
		{
			react_Sensor_Humedad_LEYENDO(handle);
			break;
		}
		case Compostera_Sensor_Humedad_SUPERIOR:
		{
			react_Sensor_Humedad_SUPERIOR(handle);
			break;
		}
		case Compostera_Sensor_Humedad_ESTABLE:
		{
			react_Sensor_Humedad_ESTABLE(handle);
			break;
		}
		case Compostera_Sensor_Humedad_INFERIOR:
		{
			react_Sensor_Humedad_INFERIOR(handle);
			break;
		}
		case Compostera_Sensor_Temperature_LEYENDO:
		{
			react_Sensor_Temperature_LEYENDO(handle);
			break;
		}
		case Compostera_Sensor_Temperature_SUPERIOR:
		{
			react_Sensor_Temperature_SUPERIOR(handle);
			break;
		}
		case Compostera_Sensor_Temperature_ESTABLE:
		{
			react_Sensor_Temperature_ESTABLE(handle);
			break;
		}
		case Compostera_Sensor_Lid_CERRADO:
		{
			react_Sensor_Lid_CERRADO(handle);
			break;
		}
		case Compostera_Sensor_Lid_ABIERTO:
		{
			react_Sensor_Lid_ABIERTO(handle);
			break;
		}
		case Compostera_Sensor_Lid_INICIO:
		{
			react_Sensor_Lid_INICIO(handle);
			break;
		}
		default:
			break;
		}
	}
	
	clearInEvents(handle);
}

void compostera_exit(Compostera* handle)
{
	/* Default exit sequence for statechart compostera */
	exseq_Humedad(handle);
	exseq_Temperatura(handle);
	exseq_Compostar(handle);
	exseq_Sensor_Humedad(handle);
	exseq_Sensor_Temperature(handle);
	exseq_Sensor_Lid(handle);
}

sc_boolean compostera_isActive(const Compostera* handle)
{
	sc_boolean result = bool_false;
	int i;
	
	for(i = 0; i < COMPOSTERA_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Compostera_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean compostera_isFinal(const Compostera* handle)
{
   return bool_false;
}

void compostera_raiseTimeEvent(Compostera* handle, sc_eventid evid)
{
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + sizeof(ComposteraTimeEvents))
		{
		*(sc_boolean*)evid = bool_true;
	}		
}

sc_boolean compostera_isStateActive(const Compostera* handle, ComposteraStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Compostera_Humedad_HUMEDECIENDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_HUMEDAD_HUMEDECIENDO] == Compostera_Humedad_HUMEDECIENDO
			);
			break;
		case Compostera_Humedad_DESHUMEDECIENDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_HUMEDAD_DESHUMEDECIENDO] == Compostera_Humedad_DESHUMEDECIENDO
			);
			break;
		case Compostera_Humedad_ESPERANDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_HUMEDAD_ESPERANDO] == Compostera_Humedad_ESPERANDO
			);
			break;
		case Compostera_Temperatura_ENFRIANDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_TEMPERATURA_ENFRIANDO] == Compostera_Temperatura_ENFRIANDO
			);
			break;
		case Compostera_Temperatura_ESPERANDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_TEMPERATURA_ESPERANDO] == Compostera_Temperatura_ESPERANDO
			);
			break;
		case Compostera_Compostar_RELLENANDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_COMPOSTAR_RELLENANDO] == Compostera_Compostar_RELLENANDO
			);
			break;
		case Compostera_Compostar_ESPERANDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_COMPOSTAR_ESPERANDO] == Compostera_Compostar_ESPERANDO
			);
			break;
		case Compostera_Compostar_SONANDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_COMPOSTAR_SONANDO] == Compostera_Compostar_SONANDO
			);
			break;
		case Compostera_Compostar_MEZCLANDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_COMPOSTAR_MEZCLANDO] == Compostera_Compostar_MEZCLANDO
			);
			break;
		case Compostera_Sensor_Humedad_LEYENDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_SENSOR_HUMEDAD_LEYENDO] == Compostera_Sensor_Humedad_LEYENDO
			);
			break;
		case Compostera_Sensor_Humedad_SUPERIOR :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_SENSOR_HUMEDAD_SUPERIOR] == Compostera_Sensor_Humedad_SUPERIOR
			);
			break;
		case Compostera_Sensor_Humedad_ESTABLE :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_SENSOR_HUMEDAD_ESTABLE] == Compostera_Sensor_Humedad_ESTABLE
			);
			break;
		case Compostera_Sensor_Humedad_INFERIOR :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_SENSOR_HUMEDAD_INFERIOR] == Compostera_Sensor_Humedad_INFERIOR
			);
			break;
		case Compostera_Sensor_Temperature_LEYENDO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_SENSOR_TEMPERATURE_LEYENDO] == Compostera_Sensor_Temperature_LEYENDO
			);
			break;
		case Compostera_Sensor_Temperature_SUPERIOR :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_SENSOR_TEMPERATURE_SUPERIOR] == Compostera_Sensor_Temperature_SUPERIOR
			);
			break;
		case Compostera_Sensor_Temperature_ESTABLE :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_SENSOR_TEMPERATURE_ESTABLE] == Compostera_Sensor_Temperature_ESTABLE
			);
			break;
		case Compostera_Sensor_Lid_CERRADO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_SENSOR_LID_CERRADO] == Compostera_Sensor_Lid_CERRADO
			);
			break;
		case Compostera_Sensor_Lid_ABIERTO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_SENSOR_LID_ABIERTO] == Compostera_Sensor_Lid_ABIERTO
			);
			break;
		case Compostera_Sensor_Lid_INICIO :
			result = (sc_boolean) (handle->stateConfVector[SCVI_COMPOSTERA_SENSOR_LID_INICIO] == Compostera_Sensor_Lid_INICIO
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}

static void clearInEvents(Compostera* handle)
{
	handle->iface.evHumedadMenor40_raised = bool_false;
	handle->iface.evHumedadMayor60_raised = bool_false;
	handle->iface.evHumedadEstable_raised = bool_false;
	handle->iface.evTemperaturaMayor60_raised = bool_false;
	handle->iface.evTemperaturaEstable_raised = bool_false;
	handle->iface.evCerradoTapa_raised = bool_false;
	handle->iface.evAberturaTapa_raised = bool_false;
	handle->internal.siTemperaturaMayor60_raised = bool_false;
	handle->internal.siTemperaturaEstable_raised = bool_false;
	handle->internal.siHumedadMenor40_raised = bool_false;
	handle->internal.siHumedadEstable_raised = bool_false;
	handle->internal.siHumedadMayor60_raised = bool_false;
	handle->internal.siAberturaTapa_raised = bool_false;
	handle->internal.siCerradoTapa_raised = bool_false;
	handle->timeEvents.compostera_Compostar_RELLENANDO_tev0_raised = bool_false;
	handle->timeEvents.compostera_Compostar_MEZCLANDO_tev0_raised = bool_false;
	handle->timeEvents.compostera_Sensor_Humedad_SUPERIOR_tev0_raised = bool_false;
	handle->timeEvents.compostera_Sensor_Humedad_ESTABLE_tev0_raised = bool_false;
	handle->timeEvents.compostera_Sensor_Humedad_INFERIOR_tev0_raised = bool_false;
	handle->timeEvents.compostera_Sensor_Temperature_SUPERIOR_tev0_raised = bool_false;
	handle->timeEvents.compostera_Sensor_Temperature_ESTABLE_tev0_raised = bool_false;
}

static void clearOutEvents(Compostera* handle)
{
}

void composteraIface_raise_evHumedadMenor40(Compostera* handle)
{
	handle->iface.evHumedadMenor40_raised = bool_true;
}
void composteraIface_raise_evHumedadMayor60(Compostera* handle)
{
	handle->iface.evHumedadMayor60_raised = bool_true;
}
void composteraIface_raise_evHumedadEstable(Compostera* handle)
{
	handle->iface.evHumedadEstable_raised = bool_true;
}
void composteraIface_raise_evTemperaturaMayor60(Compostera* handle)
{
	handle->iface.evTemperaturaMayor60_raised = bool_true;
}
void composteraIface_raise_evTemperaturaEstable(Compostera* handle)
{
	handle->iface.evTemperaturaEstable_raised = bool_true;
}
void composteraIface_raise_evCerradoTapa(Compostera* handle)
{
	handle->iface.evCerradoTapa_raised = bool_true;
}
void composteraIface_raise_evAberturaTapa(Compostera* handle)
{
	handle->iface.evAberturaTapa_raised = bool_true;
}


const sc_integer composteraIface_get_lEDR(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_LEDR;
}
const sc_integer composteraIface_get_lEDG(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_LEDG;
}
const sc_integer composteraIface_get_lEDB(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_LEDB;
}
const sc_integer composteraIface_get_lED1(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_LED1;
}
const sc_integer composteraIface_get_lED2(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_LED2;
}
const sc_integer composteraIface_get_lED3(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_LED3;
}
const sc_boolean composteraIface_get_lED_ON(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_LED_ON;
}
const sc_boolean composteraIface_get_lED_OFF(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_LED_OFF;
}
const sc_integer composteraIface_get_tEC1(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_TEC1;
}
const sc_integer composteraIface_get_tEC2(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_TEC2;
}
const sc_integer composteraIface_get_tEC3(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_TEC3;
}
const sc_integer composteraIface_get_tEC4(const Compostera* handle)
{
	return COMPOSTERA_COMPOSTERAIFACE_TEC4;
}

/* implementations of all internal functions */

static sc_boolean check_Humedad_HUMEDECIENDO_tr0_tr0(const Compostera* handle)
{
	return handle->internal.siHumedadEstable_raised;
}

static sc_boolean check_Humedad_HUMEDECIENDO_tr1_tr1(const Compostera* handle)
{
	return handle->internal.siAberturaTapa_raised;
}

static sc_boolean check_Humedad_DESHUMEDECIENDO_tr0_tr0(const Compostera* handle)
{
	return handle->internal.siHumedadEstable_raised;
}

static sc_boolean check_Humedad_DESHUMEDECIENDO_tr1_tr1(const Compostera* handle)
{
	return handle->internal.siAberturaTapa_raised;
}

static sc_boolean check_Humedad_ESPERANDO_tr0_tr0(const Compostera* handle)
{
	return handle->internal.siHumedadMayor60_raised;
}

static sc_boolean check_Humedad_ESPERANDO_tr1_tr1(const Compostera* handle)
{
	return handle->internal.siHumedadMenor40_raised;
}

static sc_boolean check_Temperatura_ENFRIANDO_tr0_tr0(const Compostera* handle)
{
	return handle->internal.siTemperaturaEstable_raised;
}

static sc_boolean check_Temperatura_ENFRIANDO_tr1_tr1(const Compostera* handle)
{
	return handle->internal.siAberturaTapa_raised;
}

static sc_boolean check_Temperatura_ESPERANDO_tr0_tr0(const Compostera* handle)
{
	return handle->internal.siTemperaturaMayor60_raised;
}

static sc_boolean check_Compostar_RELLENANDO_tr0_tr0(const Compostera* handle)
{
	return handle->timeEvents.compostera_Compostar_RELLENANDO_tev0_raised;
}

static sc_boolean check_Compostar_RELLENANDO_tr1_tr1(const Compostera* handle)
{
	return handle->internal.siCerradoTapa_raised;
}

static sc_boolean check_Compostar_ESPERANDO_tr0_tr0(const Compostera* handle)
{
	return handle->internal.siAberturaTapa_raised;
}

static sc_boolean check_Compostar_SONANDO_tr0_tr0(const Compostera* handle)
{
	return handle->internal.siCerradoTapa_raised;
}

static sc_boolean check_Compostar_MEZCLANDO_tr0_tr0(const Compostera* handle)
{
	return handle->timeEvents.compostera_Compostar_MEZCLANDO_tev0_raised;
}

static sc_boolean check_Compostar_MEZCLANDO_tr1_tr1(const Compostera* handle)
{
	return handle->internal.siAberturaTapa_raised;
}

static sc_boolean check_Sensor_Humedad_LEYENDO_tr0_tr0(const Compostera* handle)
{
	return handle->iface.evHumedadMayor60_raised;
}

static sc_boolean check_Sensor_Humedad_LEYENDO_tr1_tr1(const Compostera* handle)
{
	return handle->iface.evHumedadMenor40_raised;
}

static sc_boolean check_Sensor_Humedad_LEYENDO_tr2_tr2(const Compostera* handle)
{
	return handle->iface.evHumedadEstable_raised;
}

static sc_boolean check_Sensor_Humedad_SUPERIOR_tr0_tr0(const Compostera* handle)
{
	return handle->timeEvents.compostera_Sensor_Humedad_SUPERIOR_tev0_raised;
}

static sc_boolean check_Sensor_Humedad_ESTABLE_tr0_tr0(const Compostera* handle)
{
	return handle->timeEvents.compostera_Sensor_Humedad_ESTABLE_tev0_raised;
}

static sc_boolean check_Sensor_Humedad_INFERIOR_tr0_tr0(const Compostera* handle)
{
	return handle->timeEvents.compostera_Sensor_Humedad_INFERIOR_tev0_raised;
}

static sc_boolean check_Sensor_Temperature_LEYENDO_tr0_tr0(const Compostera* handle)
{
	return handle->iface.evTemperaturaMayor60_raised;
}

static sc_boolean check_Sensor_Temperature_LEYENDO_tr1_tr1(const Compostera* handle)
{
	return handle->iface.evTemperaturaEstable_raised;
}

static sc_boolean check_Sensor_Temperature_SUPERIOR_tr0_tr0(const Compostera* handle)
{
	return handle->timeEvents.compostera_Sensor_Temperature_SUPERIOR_tev0_raised;
}

static sc_boolean check_Sensor_Temperature_ESTABLE_tr0_tr0(const Compostera* handle)
{
	return handle->timeEvents.compostera_Sensor_Temperature_ESTABLE_tev0_raised;
}

static sc_boolean check_Sensor_Lid_CERRADO_tr0_tr0(const Compostera* handle)
{
	return handle->iface.evAberturaTapa_raised;
}

static sc_boolean check_Sensor_Lid_ABIERTO_tr0_tr0(const Compostera* handle)
{
	return handle->iface.evCerradoTapa_raised;
}

static sc_boolean check_Sensor_Lid_INICIO_tr0_tr0(const Compostera* handle)
{
	return handle->iface.evCerradoTapa_raised;
}

static sc_boolean check_Sensor_Lid_INICIO_tr1_tr1(const Compostera* handle)
{
	return handle->iface.evAberturaTapa_raised;
}

static void effect_Humedad_HUMEDECIENDO_tr0(Compostera* handle)
{
	exseq_Humedad_HUMEDECIENDO(handle);
	enseq_Humedad_ESPERANDO_default(handle);
}

static void effect_Humedad_HUMEDECIENDO_tr1(Compostera* handle)
{
	exseq_Humedad_HUMEDECIENDO(handle);
	enseq_Humedad_ESPERANDO_default(handle);
}

static void effect_Humedad_DESHUMEDECIENDO_tr0(Compostera* handle)
{
	exseq_Humedad_DESHUMEDECIENDO(handle);
	enseq_Humedad_ESPERANDO_default(handle);
}

static void effect_Humedad_DESHUMEDECIENDO_tr1(Compostera* handle)
{
	exseq_Humedad_DESHUMEDECIENDO(handle);
	enseq_Humedad_ESPERANDO_default(handle);
}

static void effect_Humedad_ESPERANDO_tr0(Compostera* handle)
{
	exseq_Humedad_ESPERANDO(handle);
	enseq_Humedad_DESHUMEDECIENDO_default(handle);
}

static void effect_Humedad_ESPERANDO_tr1(Compostera* handle)
{
	exseq_Humedad_ESPERANDO(handle);
	enseq_Humedad_HUMEDECIENDO_default(handle);
}

static void effect_Temperatura_ENFRIANDO_tr0(Compostera* handle)
{
	exseq_Temperatura_ENFRIANDO(handle);
	enseq_Temperatura_ESPERANDO_default(handle);
}

static void effect_Temperatura_ENFRIANDO_tr1(Compostera* handle)
{
	exseq_Temperatura_ENFRIANDO(handle);
	enseq_Temperatura_ESPERANDO_default(handle);
}

static void effect_Temperatura_ESPERANDO_tr0(Compostera* handle)
{
	exseq_Temperatura_ESPERANDO(handle);
	enseq_Temperatura_ENFRIANDO_default(handle);
}

static void effect_Compostar_RELLENANDO_tr0(Compostera* handle)
{
	exseq_Compostar_RELLENANDO(handle);
	enseq_Compostar_SONANDO_default(handle);
}

static void effect_Compostar_RELLENANDO_tr1(Compostera* handle)
{
	exseq_Compostar_RELLENANDO(handle);
	enseq_Compostar_MEZCLANDO_default(handle);
}

static void effect_Compostar_ESPERANDO_tr0(Compostera* handle)
{
	exseq_Compostar_ESPERANDO(handle);
	enseq_Compostar_RELLENANDO_default(handle);
}

static void effect_Compostar_SONANDO_tr0(Compostera* handle)
{
	exseq_Compostar_SONANDO(handle);
	enseq_Compostar_MEZCLANDO_default(handle);
}

static void effect_Compostar_MEZCLANDO_tr0(Compostera* handle)
{
	exseq_Compostar_MEZCLANDO(handle);
	enseq_Compostar_ESPERANDO_default(handle);
}

static void effect_Compostar_MEZCLANDO_tr1(Compostera* handle)
{
	exseq_Compostar_MEZCLANDO(handle);
	enseq_Compostar_RELLENANDO_default(handle);
}

static void effect_Sensor_Humedad_LEYENDO_tr0(Compostera* handle)
{
	exseq_Sensor_Humedad_LEYENDO(handle);
	enseq_Sensor_Humedad_SUPERIOR_default(handle);
}

static void effect_Sensor_Humedad_LEYENDO_tr1(Compostera* handle)
{
	exseq_Sensor_Humedad_LEYENDO(handle);
	enseq_Sensor_Humedad_INFERIOR_default(handle);
}

static void effect_Sensor_Humedad_LEYENDO_tr2(Compostera* handle)
{
	exseq_Sensor_Humedad_LEYENDO(handle);
	enseq_Sensor_Humedad_ESTABLE_default(handle);
}

static void effect_Sensor_Humedad_SUPERIOR_tr0(Compostera* handle)
{
	exseq_Sensor_Humedad_SUPERIOR(handle);
	enseq_Sensor_Humedad_LEYENDO_default(handle);
}

static void effect_Sensor_Humedad_ESTABLE_tr0(Compostera* handle)
{
	exseq_Sensor_Humedad_ESTABLE(handle);
	enseq_Sensor_Humedad_LEYENDO_default(handle);
}

static void effect_Sensor_Humedad_INFERIOR_tr0(Compostera* handle)
{
	exseq_Sensor_Humedad_INFERIOR(handle);
	enseq_Sensor_Humedad_LEYENDO_default(handle);
}

static void effect_Sensor_Temperature_LEYENDO_tr0(Compostera* handle)
{
	exseq_Sensor_Temperature_LEYENDO(handle);
	enseq_Sensor_Temperature_SUPERIOR_default(handle);
}

static void effect_Sensor_Temperature_LEYENDO_tr1(Compostera* handle)
{
	exseq_Sensor_Temperature_LEYENDO(handle);
	enseq_Sensor_Temperature_ESTABLE_default(handle);
}

static void effect_Sensor_Temperature_SUPERIOR_tr0(Compostera* handle)
{
	exseq_Sensor_Temperature_SUPERIOR(handle);
	enseq_Sensor_Temperature_LEYENDO_default(handle);
}

static void effect_Sensor_Temperature_ESTABLE_tr0(Compostera* handle)
{
	exseq_Sensor_Temperature_ESTABLE(handle);
	enseq_Sensor_Temperature_LEYENDO_default(handle);
}

static void effect_Sensor_Lid_CERRADO_tr0(Compostera* handle)
{
	exseq_Sensor_Lid_CERRADO(handle);
	enseq_Sensor_Lid_ABIERTO_default(handle);
}

static void effect_Sensor_Lid_ABIERTO_tr0(Compostera* handle)
{
	exseq_Sensor_Lid_ABIERTO(handle);
	enseq_Sensor_Lid_CERRADO_default(handle);
}

static void effect_Sensor_Lid_INICIO_tr0(Compostera* handle)
{
	exseq_Sensor_Lid_INICIO(handle);
	enseq_Sensor_Lid_CERRADO_default(handle);
}

static void effect_Sensor_Lid_INICIO_tr1(Compostera* handle)
{
	exseq_Sensor_Lid_INICIO(handle);
	enseq_Sensor_Lid_ABIERTO_default(handle);
}

/* Entry action for state 'ENFRIANDO'. */
static void enact_Temperatura_ENFRIANDO(Compostera* handle)
{
	/* Entry action for state 'ENFRIANDO'. */
	composteraIface_opLED(handle, COMPOSTERA_COMPOSTERAIFACE_LEDR, COMPOSTERA_COMPOSTERAIFACE_LED_ON);
}

/* Entry action for state 'ESPERANDO'. */
static void enact_Temperatura_ESPERANDO(Compostera* handle)
{
	/* Entry action for state 'ESPERANDO'. */
	composteraIface_opLED(handle, COMPOSTERA_COMPOSTERAIFACE_LEDR, COMPOSTERA_COMPOSTERAIFACE_LED_OFF);
}

/* Entry action for state 'RELLENANDO'. */
static void enact_Compostar_RELLENANDO(Compostera* handle)
{
	/* Entry action for state 'RELLENANDO'. */
	compostera_setTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Compostar_RELLENANDO_tev0_raised) , 1 * 1000, bool_false);
	composteraIface_opLED(handle, COMPOSTERA_COMPOSTERAIFACE_LED3, COMPOSTERA_COMPOSTERAIFACE_LED_ON);
	composteraIface_opLED(handle, COMPOSTERA_COMPOSTERAIFACE_LED2, COMPOSTERA_COMPOSTERAIFACE_LED_OFF);
}

/* Entry action for state 'ESPERANDO'. */
static void enact_Compostar_ESPERANDO(Compostera* handle)
{
	/* Entry action for state 'ESPERANDO'. */
	composteraIface_opLED(handle, COMPOSTERA_COMPOSTERAIFACE_LED2, COMPOSTERA_COMPOSTERAIFACE_LED_OFF);
}

/* Entry action for state 'SONANDO'. */
static void enact_Compostar_SONANDO(Compostera* handle)
{
	/* Entry action for state 'SONANDO'. */
	composteraIface_opLED(handle, COMPOSTERA_COMPOSTERAIFACE_LED1, COMPOSTERA_COMPOSTERAIFACE_LED_ON);
	composteraIface_opLED(handle, COMPOSTERA_COMPOSTERAIFACE_LED3, COMPOSTERA_COMPOSTERAIFACE_LED_OFF);
}

/* Entry action for state 'MEZCLANDO'. */
static void enact_Compostar_MEZCLANDO(Compostera* handle)
{
	/* Entry action for state 'MEZCLANDO'. */
	compostera_setTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Compostar_MEZCLANDO_tev0_raised) , 2 * 1000, bool_false);
	composteraIface_opLED(handle, COMPOSTERA_COMPOSTERAIFACE_LED2, COMPOSTERA_COMPOSTERAIFACE_LED_ON);
	composteraIface_opLED(handle, COMPOSTERA_COMPOSTERAIFACE_LED3, COMPOSTERA_COMPOSTERAIFACE_LED_OFF);
	composteraIface_opLED(handle, COMPOSTERA_COMPOSTERAIFACE_LED1, COMPOSTERA_COMPOSTERAIFACE_LED_OFF);
}

/* Entry action for state 'SUPERIOR'. */
static void enact_Sensor_Humedad_SUPERIOR(Compostera* handle)
{
	/* Entry action for state 'SUPERIOR'. */
	compostera_setTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Sensor_Humedad_SUPERIOR_tev0_raised) , 2 * 1000, bool_false);
	handle->internal.siHumedadMayor60_raised = bool_true;
}

/* Entry action for state 'ESTABLE'. */
static void enact_Sensor_Humedad_ESTABLE(Compostera* handle)
{
	/* Entry action for state 'ESTABLE'. */
	compostera_setTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Sensor_Humedad_ESTABLE_tev0_raised) , 2 * 1000, bool_false);
	handle->internal.siHumedadEstable_raised = bool_true;
}

/* Entry action for state 'INFERIOR'. */
static void enact_Sensor_Humedad_INFERIOR(Compostera* handle)
{
	/* Entry action for state 'INFERIOR'. */
	compostera_setTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Sensor_Humedad_INFERIOR_tev0_raised) , 2 * 1000, bool_false);
	handle->internal.siHumedadMenor40_raised = bool_true;
}

/* Entry action for state 'SUPERIOR'. */
static void enact_Sensor_Temperature_SUPERIOR(Compostera* handle)
{
	/* Entry action for state 'SUPERIOR'. */
	compostera_setTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Sensor_Temperature_SUPERIOR_tev0_raised) , 2 * 1000, bool_false);
	handle->internal.siTemperaturaMayor60_raised = bool_true;
}

/* Entry action for state 'ESTABLE'. */
static void enact_Sensor_Temperature_ESTABLE(Compostera* handle)
{
	/* Entry action for state 'ESTABLE'. */
	compostera_setTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Sensor_Temperature_ESTABLE_tev0_raised) , 2 * 1000, bool_false);
	handle->internal.siTemperaturaEstable_raised = bool_true;
}

/* Entry action for state 'CERRADO'. */
static void enact_Sensor_Lid_CERRADO(Compostera* handle)
{
	/* Entry action for state 'CERRADO'. */
	handle->internal.siCerradoTapa_raised = bool_true;
}

/* Entry action for state 'ABIERTO'. */
static void enact_Sensor_Lid_ABIERTO(Compostera* handle)
{
	/* Entry action for state 'ABIERTO'. */
	handle->internal.siAberturaTapa_raised = bool_true;
}

/* Exit action for state 'RELLENANDO'. */
static void exact_Compostar_RELLENANDO(Compostera* handle)
{
	/* Exit action for state 'RELLENANDO'. */
	compostera_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Compostar_RELLENANDO_tev0_raised) );		
}

/* Exit action for state 'MEZCLANDO'. */
static void exact_Compostar_MEZCLANDO(Compostera* handle)
{
	/* Exit action for state 'MEZCLANDO'. */
	compostera_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Compostar_MEZCLANDO_tev0_raised) );		
}

/* Exit action for state 'SUPERIOR'. */
static void exact_Sensor_Humedad_SUPERIOR(Compostera* handle)
{
	/* Exit action for state 'SUPERIOR'. */
	compostera_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Sensor_Humedad_SUPERIOR_tev0_raised) );		
}

/* Exit action for state 'ESTABLE'. */
static void exact_Sensor_Humedad_ESTABLE(Compostera* handle)
{
	/* Exit action for state 'ESTABLE'. */
	compostera_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Sensor_Humedad_ESTABLE_tev0_raised) );		
}

/* Exit action for state 'INFERIOR'. */
static void exact_Sensor_Humedad_INFERIOR(Compostera* handle)
{
	/* Exit action for state 'INFERIOR'. */
	compostera_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Sensor_Humedad_INFERIOR_tev0_raised) );		
}

/* Exit action for state 'SUPERIOR'. */
static void exact_Sensor_Temperature_SUPERIOR(Compostera* handle)
{
	/* Exit action for state 'SUPERIOR'. */
	compostera_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Sensor_Temperature_SUPERIOR_tev0_raised) );		
}

/* Exit action for state 'ESTABLE'. */
static void exact_Sensor_Temperature_ESTABLE(Compostera* handle)
{
	/* Exit action for state 'ESTABLE'. */
	compostera_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.compostera_Sensor_Temperature_ESTABLE_tev0_raised) );		
}

/* 'default' enter sequence for state HUMEDECIENDO */
static void enseq_Humedad_HUMEDECIENDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state HUMEDECIENDO */
	handle->stateConfVector[0] = Compostera_Humedad_HUMEDECIENDO;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state DESHUMEDECIENDO */
static void enseq_Humedad_DESHUMEDECIENDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state DESHUMEDECIENDO */
	handle->stateConfVector[0] = Compostera_Humedad_DESHUMEDECIENDO;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state ESPERANDO */
static void enseq_Humedad_ESPERANDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state ESPERANDO */
	handle->stateConfVector[0] = Compostera_Humedad_ESPERANDO;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state ENFRIANDO */
static void enseq_Temperatura_ENFRIANDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state ENFRIANDO */
	enact_Temperatura_ENFRIANDO(handle);
	handle->stateConfVector[1] = Compostera_Temperatura_ENFRIANDO;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state ESPERANDO */
static void enseq_Temperatura_ESPERANDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state ESPERANDO */
	enact_Temperatura_ESPERANDO(handle);
	handle->stateConfVector[1] = Compostera_Temperatura_ESPERANDO;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state RELLENANDO */
static void enseq_Compostar_RELLENANDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state RELLENANDO */
	enact_Compostar_RELLENANDO(handle);
	handle->stateConfVector[2] = Compostera_Compostar_RELLENANDO;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state ESPERANDO */
static void enseq_Compostar_ESPERANDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state ESPERANDO */
	enact_Compostar_ESPERANDO(handle);
	handle->stateConfVector[2] = Compostera_Compostar_ESPERANDO;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state SONANDO */
static void enseq_Compostar_SONANDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state SONANDO */
	enact_Compostar_SONANDO(handle);
	handle->stateConfVector[2] = Compostera_Compostar_SONANDO;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state MEZCLANDO */
static void enseq_Compostar_MEZCLANDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state MEZCLANDO */
	enact_Compostar_MEZCLANDO(handle);
	handle->stateConfVector[2] = Compostera_Compostar_MEZCLANDO;
	handle->stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state LEYENDO */
static void enseq_Sensor_Humedad_LEYENDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state LEYENDO */
	handle->stateConfVector[3] = Compostera_Sensor_Humedad_LEYENDO;
	handle->stateConfVectorPosition = 3;
}

/* 'default' enter sequence for state SUPERIOR */
static void enseq_Sensor_Humedad_SUPERIOR_default(Compostera* handle)
{
	/* 'default' enter sequence for state SUPERIOR */
	enact_Sensor_Humedad_SUPERIOR(handle);
	handle->stateConfVector[3] = Compostera_Sensor_Humedad_SUPERIOR;
	handle->stateConfVectorPosition = 3;
}

/* 'default' enter sequence for state ESTABLE */
static void enseq_Sensor_Humedad_ESTABLE_default(Compostera* handle)
{
	/* 'default' enter sequence for state ESTABLE */
	enact_Sensor_Humedad_ESTABLE(handle);
	handle->stateConfVector[3] = Compostera_Sensor_Humedad_ESTABLE;
	handle->stateConfVectorPosition = 3;
}

/* 'default' enter sequence for state INFERIOR */
static void enseq_Sensor_Humedad_INFERIOR_default(Compostera* handle)
{
	/* 'default' enter sequence for state INFERIOR */
	enact_Sensor_Humedad_INFERIOR(handle);
	handle->stateConfVector[3] = Compostera_Sensor_Humedad_INFERIOR;
	handle->stateConfVectorPosition = 3;
}

/* 'default' enter sequence for state LEYENDO */
static void enseq_Sensor_Temperature_LEYENDO_default(Compostera* handle)
{
	/* 'default' enter sequence for state LEYENDO */
	handle->stateConfVector[4] = Compostera_Sensor_Temperature_LEYENDO;
	handle->stateConfVectorPosition = 4;
}

/* 'default' enter sequence for state SUPERIOR */
static void enseq_Sensor_Temperature_SUPERIOR_default(Compostera* handle)
{
	/* 'default' enter sequence for state SUPERIOR */
	enact_Sensor_Temperature_SUPERIOR(handle);
	handle->stateConfVector[4] = Compostera_Sensor_Temperature_SUPERIOR;
	handle->stateConfVectorPosition = 4;
}

/* 'default' enter sequence for state ESTABLE */
static void enseq_Sensor_Temperature_ESTABLE_default(Compostera* handle)
{
	/* 'default' enter sequence for state ESTABLE */
	enact_Sensor_Temperature_ESTABLE(handle);
	handle->stateConfVector[4] = Compostera_Sensor_Temperature_ESTABLE;
	handle->stateConfVectorPosition = 4;
}

/* 'default' enter sequence for state CERRADO */
static void enseq_Sensor_Lid_CERRADO_default(Compostera* handle)
{
	/* 'default' enter sequence for state CERRADO */
	enact_Sensor_Lid_CERRADO(handle);
	handle->stateConfVector[5] = Compostera_Sensor_Lid_CERRADO;
	handle->stateConfVectorPosition = 5;
}

/* 'default' enter sequence for state ABIERTO */
static void enseq_Sensor_Lid_ABIERTO_default(Compostera* handle)
{
	/* 'default' enter sequence for state ABIERTO */
	enact_Sensor_Lid_ABIERTO(handle);
	handle->stateConfVector[5] = Compostera_Sensor_Lid_ABIERTO;
	handle->stateConfVectorPosition = 5;
}

/* 'default' enter sequence for state INICIO */
static void enseq_Sensor_Lid_INICIO_default(Compostera* handle)
{
	/* 'default' enter sequence for state INICIO */
	handle->stateConfVector[5] = Compostera_Sensor_Lid_INICIO;
	handle->stateConfVectorPosition = 5;
}

/* 'default' enter sequence for region Humedad */
static void enseq_Humedad_default(Compostera* handle)
{
	/* 'default' enter sequence for region Humedad */
	react_Humedad__entry_Default(handle);
}

/* 'default' enter sequence for region Temperatura */
static void enseq_Temperatura_default(Compostera* handle)
{
	/* 'default' enter sequence for region Temperatura */
	react_Temperatura__entry_Default(handle);
}

/* 'default' enter sequence for region Compostar */
static void enseq_Compostar_default(Compostera* handle)
{
	/* 'default' enter sequence for region Compostar */
	react_Compostar__entry_Default(handle);
}

/* 'default' enter sequence for region Sensor_Humedad */
static void enseq_Sensor_Humedad_default(Compostera* handle)
{
	/* 'default' enter sequence for region Sensor_Humedad */
	react_Sensor_Humedad__entry_Default(handle);
}

/* 'default' enter sequence for region Sensor_Temperature */
static void enseq_Sensor_Temperature_default(Compostera* handle)
{
	/* 'default' enter sequence for region Sensor_Temperature */
	react_Sensor_Temperature__entry_Default(handle);
}

/* 'default' enter sequence for region Sensor_Lid */
static void enseq_Sensor_Lid_default(Compostera* handle)
{
	/* 'default' enter sequence for region Sensor_Lid */
	react_Sensor_Lid__entry_Default(handle);
}

/* Default exit sequence for state HUMEDECIENDO */
static void exseq_Humedad_HUMEDECIENDO(Compostera* handle)
{
	/* Default exit sequence for state HUMEDECIENDO */
	handle->stateConfVector[0] = Compostera_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state DESHUMEDECIENDO */
static void exseq_Humedad_DESHUMEDECIENDO(Compostera* handle)
{
	/* Default exit sequence for state DESHUMEDECIENDO */
	handle->stateConfVector[0] = Compostera_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state ESPERANDO */
static void exseq_Humedad_ESPERANDO(Compostera* handle)
{
	/* Default exit sequence for state ESPERANDO */
	handle->stateConfVector[0] = Compostera_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state ENFRIANDO */
static void exseq_Temperatura_ENFRIANDO(Compostera* handle)
{
	/* Default exit sequence for state ENFRIANDO */
	handle->stateConfVector[1] = Compostera_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state ESPERANDO */
static void exseq_Temperatura_ESPERANDO(Compostera* handle)
{
	/* Default exit sequence for state ESPERANDO */
	handle->stateConfVector[1] = Compostera_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state RELLENANDO */
static void exseq_Compostar_RELLENANDO(Compostera* handle)
{
	/* Default exit sequence for state RELLENANDO */
	handle->stateConfVector[2] = Compostera_last_state;
	handle->stateConfVectorPosition = 2;
	exact_Compostar_RELLENANDO(handle);
}

/* Default exit sequence for state ESPERANDO */
static void exseq_Compostar_ESPERANDO(Compostera* handle)
{
	/* Default exit sequence for state ESPERANDO */
	handle->stateConfVector[2] = Compostera_last_state;
	handle->stateConfVectorPosition = 2;
}

/* Default exit sequence for state SONANDO */
static void exseq_Compostar_SONANDO(Compostera* handle)
{
	/* Default exit sequence for state SONANDO */
	handle->stateConfVector[2] = Compostera_last_state;
	handle->stateConfVectorPosition = 2;
}

/* Default exit sequence for state MEZCLANDO */
static void exseq_Compostar_MEZCLANDO(Compostera* handle)
{
	/* Default exit sequence for state MEZCLANDO */
	handle->stateConfVector[2] = Compostera_last_state;
	handle->stateConfVectorPosition = 2;
	exact_Compostar_MEZCLANDO(handle);
}

/* Default exit sequence for state LEYENDO */
static void exseq_Sensor_Humedad_LEYENDO(Compostera* handle)
{
	/* Default exit sequence for state LEYENDO */
	handle->stateConfVector[3] = Compostera_last_state;
	handle->stateConfVectorPosition = 3;
}

/* Default exit sequence for state SUPERIOR */
static void exseq_Sensor_Humedad_SUPERIOR(Compostera* handle)
{
	/* Default exit sequence for state SUPERIOR */
	handle->stateConfVector[3] = Compostera_last_state;
	handle->stateConfVectorPosition = 3;
	exact_Sensor_Humedad_SUPERIOR(handle);
}

/* Default exit sequence for state ESTABLE */
static void exseq_Sensor_Humedad_ESTABLE(Compostera* handle)
{
	/* Default exit sequence for state ESTABLE */
	handle->stateConfVector[3] = Compostera_last_state;
	handle->stateConfVectorPosition = 3;
	exact_Sensor_Humedad_ESTABLE(handle);
}

/* Default exit sequence for state INFERIOR */
static void exseq_Sensor_Humedad_INFERIOR(Compostera* handle)
{
	/* Default exit sequence for state INFERIOR */
	handle->stateConfVector[3] = Compostera_last_state;
	handle->stateConfVectorPosition = 3;
	exact_Sensor_Humedad_INFERIOR(handle);
}

/* Default exit sequence for state LEYENDO */
static void exseq_Sensor_Temperature_LEYENDO(Compostera* handle)
{
	/* Default exit sequence for state LEYENDO */
	handle->stateConfVector[4] = Compostera_last_state;
	handle->stateConfVectorPosition = 4;
}

/* Default exit sequence for state SUPERIOR */
static void exseq_Sensor_Temperature_SUPERIOR(Compostera* handle)
{
	/* Default exit sequence for state SUPERIOR */
	handle->stateConfVector[4] = Compostera_last_state;
	handle->stateConfVectorPosition = 4;
	exact_Sensor_Temperature_SUPERIOR(handle);
}

/* Default exit sequence for state ESTABLE */
static void exseq_Sensor_Temperature_ESTABLE(Compostera* handle)
{
	/* Default exit sequence for state ESTABLE */
	handle->stateConfVector[4] = Compostera_last_state;
	handle->stateConfVectorPosition = 4;
	exact_Sensor_Temperature_ESTABLE(handle);
}

/* Default exit sequence for state CERRADO */
static void exseq_Sensor_Lid_CERRADO(Compostera* handle)
{
	/* Default exit sequence for state CERRADO */
	handle->stateConfVector[5] = Compostera_last_state;
	handle->stateConfVectorPosition = 5;
}

/* Default exit sequence for state ABIERTO */
static void exseq_Sensor_Lid_ABIERTO(Compostera* handle)
{
	/* Default exit sequence for state ABIERTO */
	handle->stateConfVector[5] = Compostera_last_state;
	handle->stateConfVectorPosition = 5;
}

/* Default exit sequence for state INICIO */
static void exseq_Sensor_Lid_INICIO(Compostera* handle)
{
	/* Default exit sequence for state INICIO */
	handle->stateConfVector[5] = Compostera_last_state;
	handle->stateConfVectorPosition = 5;
}

/* Default exit sequence for region Humedad */
static void exseq_Humedad(Compostera* handle)
{
	/* Default exit sequence for region Humedad */
	/* Handle exit of all possible states (of compostera.Humedad) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Compostera_Humedad_HUMEDECIENDO :
		{
			exseq_Humedad_HUMEDECIENDO(handle);
			break;
		}
		case Compostera_Humedad_DESHUMEDECIENDO :
		{
			exseq_Humedad_DESHUMEDECIENDO(handle);
			break;
		}
		case Compostera_Humedad_ESPERANDO :
		{
			exseq_Humedad_ESPERANDO(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region Temperatura */
static void exseq_Temperatura(Compostera* handle)
{
	/* Default exit sequence for region Temperatura */
	/* Handle exit of all possible states (of compostera.Temperatura) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Compostera_Temperatura_ENFRIANDO :
		{
			exseq_Temperatura_ENFRIANDO(handle);
			break;
		}
		case Compostera_Temperatura_ESPERANDO :
		{
			exseq_Temperatura_ESPERANDO(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region Compostar */
static void exseq_Compostar(Compostera* handle)
{
	/* Default exit sequence for region Compostar */
	/* Handle exit of all possible states (of compostera.Compostar) at position 2... */
	switch(handle->stateConfVector[ 2 ])
	{
		case Compostera_Compostar_RELLENANDO :
		{
			exseq_Compostar_RELLENANDO(handle);
			break;
		}
		case Compostera_Compostar_ESPERANDO :
		{
			exseq_Compostar_ESPERANDO(handle);
			break;
		}
		case Compostera_Compostar_SONANDO :
		{
			exseq_Compostar_SONANDO(handle);
			break;
		}
		case Compostera_Compostar_MEZCLANDO :
		{
			exseq_Compostar_MEZCLANDO(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region Sensor_Humedad */
static void exseq_Sensor_Humedad(Compostera* handle)
{
	/* Default exit sequence for region Sensor_Humedad */
	/* Handle exit of all possible states (of compostera.Sensor_Humedad) at position 3... */
	switch(handle->stateConfVector[ 3 ])
	{
		case Compostera_Sensor_Humedad_LEYENDO :
		{
			exseq_Sensor_Humedad_LEYENDO(handle);
			break;
		}
		case Compostera_Sensor_Humedad_SUPERIOR :
		{
			exseq_Sensor_Humedad_SUPERIOR(handle);
			break;
		}
		case Compostera_Sensor_Humedad_ESTABLE :
		{
			exseq_Sensor_Humedad_ESTABLE(handle);
			break;
		}
		case Compostera_Sensor_Humedad_INFERIOR :
		{
			exseq_Sensor_Humedad_INFERIOR(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region Sensor_Temperature */
static void exseq_Sensor_Temperature(Compostera* handle)
{
	/* Default exit sequence for region Sensor_Temperature */
	/* Handle exit of all possible states (of compostera.Sensor_Temperature) at position 4... */
	switch(handle->stateConfVector[ 4 ])
	{
		case Compostera_Sensor_Temperature_LEYENDO :
		{
			exseq_Sensor_Temperature_LEYENDO(handle);
			break;
		}
		case Compostera_Sensor_Temperature_SUPERIOR :
		{
			exseq_Sensor_Temperature_SUPERIOR(handle);
			break;
		}
		case Compostera_Sensor_Temperature_ESTABLE :
		{
			exseq_Sensor_Temperature_ESTABLE(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region Sensor_Lid */
static void exseq_Sensor_Lid(Compostera* handle)
{
	/* Default exit sequence for region Sensor_Lid */
	/* Handle exit of all possible states (of compostera.Sensor_Lid) at position 5... */
	switch(handle->stateConfVector[ 5 ])
	{
		case Compostera_Sensor_Lid_CERRADO :
		{
			exseq_Sensor_Lid_CERRADO(handle);
			break;
		}
		case Compostera_Sensor_Lid_ABIERTO :
		{
			exseq_Sensor_Lid_ABIERTO(handle);
			break;
		}
		case Compostera_Sensor_Lid_INICIO :
		{
			exseq_Sensor_Lid_INICIO(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state HUMEDECIENDO. */
static void react_Humedad_HUMEDECIENDO(Compostera* handle)
{
	/* The reactions of state HUMEDECIENDO. */
	if (check_Humedad_HUMEDECIENDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Humedad_HUMEDECIENDO_tr0(handle);
	}  else
	{
		if (check_Humedad_HUMEDECIENDO_tr1_tr1(handle) == bool_true)
		{ 
			effect_Humedad_HUMEDECIENDO_tr1(handle);
		} 
	}
}

/* The reactions of state DESHUMEDECIENDO. */
static void react_Humedad_DESHUMEDECIENDO(Compostera* handle)
{
	/* The reactions of state DESHUMEDECIENDO. */
	if (check_Humedad_DESHUMEDECIENDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Humedad_DESHUMEDECIENDO_tr0(handle);
	}  else
	{
		if (check_Humedad_DESHUMEDECIENDO_tr1_tr1(handle) == bool_true)
		{ 
			effect_Humedad_DESHUMEDECIENDO_tr1(handle);
		} 
	}
}

/* The reactions of state ESPERANDO. */
static void react_Humedad_ESPERANDO(Compostera* handle)
{
	/* The reactions of state ESPERANDO. */
	if (check_Humedad_ESPERANDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Humedad_ESPERANDO_tr0(handle);
	}  else
	{
		if (check_Humedad_ESPERANDO_tr1_tr1(handle) == bool_true)
		{ 
			effect_Humedad_ESPERANDO_tr1(handle);
		} 
	}
}

/* The reactions of state ENFRIANDO. */
static void react_Temperatura_ENFRIANDO(Compostera* handle)
{
	/* The reactions of state ENFRIANDO. */
	if (check_Temperatura_ENFRIANDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Temperatura_ENFRIANDO_tr0(handle);
	}  else
	{
		if (check_Temperatura_ENFRIANDO_tr1_tr1(handle) == bool_true)
		{ 
			effect_Temperatura_ENFRIANDO_tr1(handle);
		} 
	}
}

/* The reactions of state ESPERANDO. */
static void react_Temperatura_ESPERANDO(Compostera* handle)
{
	/* The reactions of state ESPERANDO. */
	if (check_Temperatura_ESPERANDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Temperatura_ESPERANDO_tr0(handle);
	} 
}

/* The reactions of state RELLENANDO. */
static void react_Compostar_RELLENANDO(Compostera* handle)
{
	/* The reactions of state RELLENANDO. */
	if (check_Compostar_RELLENANDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Compostar_RELLENANDO_tr0(handle);
	}  else
	{
		if (check_Compostar_RELLENANDO_tr1_tr1(handle) == bool_true)
		{ 
			effect_Compostar_RELLENANDO_tr1(handle);
		} 
	}
}

/* The reactions of state ESPERANDO. */
static void react_Compostar_ESPERANDO(Compostera* handle)
{
	/* The reactions of state ESPERANDO. */
	if (check_Compostar_ESPERANDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Compostar_ESPERANDO_tr0(handle);
	} 
}

/* The reactions of state SONANDO. */
static void react_Compostar_SONANDO(Compostera* handle)
{
	/* The reactions of state SONANDO. */
	if (check_Compostar_SONANDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Compostar_SONANDO_tr0(handle);
	} 
}

/* The reactions of state MEZCLANDO. */
static void react_Compostar_MEZCLANDO(Compostera* handle)
{
	/* The reactions of state MEZCLANDO. */
	if (check_Compostar_MEZCLANDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Compostar_MEZCLANDO_tr0(handle);
	}  else
	{
		if (check_Compostar_MEZCLANDO_tr1_tr1(handle) == bool_true)
		{ 
			effect_Compostar_MEZCLANDO_tr1(handle);
		} 
	}
}

/* The reactions of state LEYENDO. */
static void react_Sensor_Humedad_LEYENDO(Compostera* handle)
{
	/* The reactions of state LEYENDO. */
	if (check_Sensor_Humedad_LEYENDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Sensor_Humedad_LEYENDO_tr0(handle);
	}  else
	{
		if (check_Sensor_Humedad_LEYENDO_tr1_tr1(handle) == bool_true)
		{ 
			effect_Sensor_Humedad_LEYENDO_tr1(handle);
		}  else
		{
			if (check_Sensor_Humedad_LEYENDO_tr2_tr2(handle) == bool_true)
			{ 
				effect_Sensor_Humedad_LEYENDO_tr2(handle);
			} 
		}
	}
}

/* The reactions of state SUPERIOR. */
static void react_Sensor_Humedad_SUPERIOR(Compostera* handle)
{
	/* The reactions of state SUPERIOR. */
	if (check_Sensor_Humedad_SUPERIOR_tr0_tr0(handle) == bool_true)
	{ 
		effect_Sensor_Humedad_SUPERIOR_tr0(handle);
	} 
}

/* The reactions of state ESTABLE. */
static void react_Sensor_Humedad_ESTABLE(Compostera* handle)
{
	/* The reactions of state ESTABLE. */
	if (check_Sensor_Humedad_ESTABLE_tr0_tr0(handle) == bool_true)
	{ 
		effect_Sensor_Humedad_ESTABLE_tr0(handle);
	} 
}

/* The reactions of state INFERIOR. */
static void react_Sensor_Humedad_INFERIOR(Compostera* handle)
{
	/* The reactions of state INFERIOR. */
	if (check_Sensor_Humedad_INFERIOR_tr0_tr0(handle) == bool_true)
	{ 
		effect_Sensor_Humedad_INFERIOR_tr0(handle);
	} 
}

/* The reactions of state LEYENDO. */
static void react_Sensor_Temperature_LEYENDO(Compostera* handle)
{
	/* The reactions of state LEYENDO. */
	if (check_Sensor_Temperature_LEYENDO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Sensor_Temperature_LEYENDO_tr0(handle);
	}  else
	{
		if (check_Sensor_Temperature_LEYENDO_tr1_tr1(handle) == bool_true)
		{ 
			effect_Sensor_Temperature_LEYENDO_tr1(handle);
		} 
	}
}

/* The reactions of state SUPERIOR. */
static void react_Sensor_Temperature_SUPERIOR(Compostera* handle)
{
	/* The reactions of state SUPERIOR. */
	if (check_Sensor_Temperature_SUPERIOR_tr0_tr0(handle) == bool_true)
	{ 
		effect_Sensor_Temperature_SUPERIOR_tr0(handle);
	} 
}

/* The reactions of state ESTABLE. */
static void react_Sensor_Temperature_ESTABLE(Compostera* handle)
{
	/* The reactions of state ESTABLE. */
	if (check_Sensor_Temperature_ESTABLE_tr0_tr0(handle) == bool_true)
	{ 
		effect_Sensor_Temperature_ESTABLE_tr0(handle);
	} 
}

/* The reactions of state CERRADO. */
static void react_Sensor_Lid_CERRADO(Compostera* handle)
{
	/* The reactions of state CERRADO. */
	if (check_Sensor_Lid_CERRADO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Sensor_Lid_CERRADO_tr0(handle);
	} 
}

/* The reactions of state ABIERTO. */
static void react_Sensor_Lid_ABIERTO(Compostera* handle)
{
	/* The reactions of state ABIERTO. */
	if (check_Sensor_Lid_ABIERTO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Sensor_Lid_ABIERTO_tr0(handle);
	} 
}

/* The reactions of state INICIO. */
static void react_Sensor_Lid_INICIO(Compostera* handle)
{
	/* The reactions of state INICIO. */
	if (check_Sensor_Lid_INICIO_tr0_tr0(handle) == bool_true)
	{ 
		effect_Sensor_Lid_INICIO_tr0(handle);
	}  else
	{
		if (check_Sensor_Lid_INICIO_tr1_tr1(handle) == bool_true)
		{ 
			effect_Sensor_Lid_INICIO_tr1(handle);
		} 
	}
}

/* Default react sequence for initial entry  */
static void react_Humedad__entry_Default(Compostera* handle)
{
	/* Default react sequence for initial entry  */
	enseq_Humedad_ESPERANDO_default(handle);
}

/* Default react sequence for initial entry  */
static void react_Temperatura__entry_Default(Compostera* handle)
{
	/* Default react sequence for initial entry  */
	enseq_Temperatura_ESPERANDO_default(handle);
}

/* Default react sequence for initial entry  */
static void react_Compostar__entry_Default(Compostera* handle)
{
	/* Default react sequence for initial entry  */
	enseq_Compostar_ESPERANDO_default(handle);
}

/* Default react sequence for initial entry  */
static void react_Sensor_Humedad__entry_Default(Compostera* handle)
{
	/* Default react sequence for initial entry  */
	enseq_Sensor_Humedad_LEYENDO_default(handle);
}

/* Default react sequence for initial entry  */
static void react_Sensor_Temperature__entry_Default(Compostera* handle)
{
	/* Default react sequence for initial entry  */
	enseq_Sensor_Temperature_LEYENDO_default(handle);
}

/* Default react sequence for initial entry  */
static void react_Sensor_Lid__entry_Default(Compostera* handle)
{
	/* Default react sequence for initial entry  */
	enseq_Sensor_Lid_INICIO_default(handle);
}


