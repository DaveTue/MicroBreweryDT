/* Initialization */
#include "ThermoFMU_model.h"
#include "ThermoFMU_11mix.h"
#include "ThermoFMU_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void ThermoFMU_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void ThermoFMU_eqFunction_7(DATA *data, threadData_t *threadData);


/*
equation index: 2
type: SIMPLE_ASSIGN
T = $START.T
*/
void ThermoFMU_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->realVars[0] /* T STATE(1) */) = (data->modelData->realVarsData[0] /* T STATE(1) */).attribute .start;
  TRACE_POP
}
extern void ThermoFMU_eqFunction_10(DATA *data, threadData_t *threadData);


/*
equation index: 4
type: SIMPLE_ASSIGN
Vol_meters = 0.001 * Volume
*/
void ThermoFMU_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->realVars[4] /* Vol_meters variable */) = (0.001) * ((data->simulationInfo->realParameter[6] /* Volume PARAM */));
  TRACE_POP
}
extern void ThermoFMU_eqFunction_8(DATA *data, threadData_t *threadData);


/*
equation index: 6
type: SIMPLE_ASSIGN
Q_beer = density * Cp * Vol_meters * $DER.T
*/
void ThermoFMU_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[2] /* Q_beer variable */) = ((data->localData[0]->realVars[6] /* density variable */)) * (((data->simulationInfo->realParameter[2] /* Cp PARAM */)) * (((data->localData[0]->realVars[4] /* Vol_meters variable */)) * ((data->localData[0]->realVars[1] /* der(T) STATE_DER */))));
  TRACE_POP
}
OMC_DISABLE_OPT
void ThermoFMU_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ThermoFMU_eqFunction_7(data, threadData);
  ThermoFMU_eqFunction_2(data, threadData);
  ThermoFMU_eqFunction_10(data, threadData);
  ThermoFMU_eqFunction_4(data, threadData);
  ThermoFMU_eqFunction_8(data, threadData);
  ThermoFMU_eqFunction_6(data, threadData);
  TRACE_POP
}

int ThermoFMU_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  ThermoFMU_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No ThermoFMU_functionInitialEquations_lambda0 function */

int ThermoFMU_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

