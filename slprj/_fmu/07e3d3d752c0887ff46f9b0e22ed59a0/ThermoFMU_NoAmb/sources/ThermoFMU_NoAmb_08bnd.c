/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "ThermoFMU_NoAmb_model.h"
#if defined(__cplusplus)
extern "C" {
#endif


/*
equation index: 11
type: SIMPLE_ASSIGN
$START.T = T_0
*/
static void ThermoFMU_NoAmb_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  (data->modelData->realVarsData[0] /* T STATE(1) */).attribute .start = (data->simulationInfo->realParameter[2] /* T_0 PARAM */);
    (data->localData[0]->realVars[0] /* T STATE(1) */) = (data->modelData->realVarsData[0] /* T STATE(1) */).attribute .start;
    infoStreamPrint(LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[0].info /* T */.name, (modelica_real) (data->localData[0]->realVars[0] /* T STATE(1) */));
  TRACE_POP
}
OMC_DISABLE_OPT
int ThermoFMU_NoAmb_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating min-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* max ******************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating max-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* nominal **************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating nominal-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* start ****************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating primary start-values");
  ThermoFMU_NoAmb_eqFunction_11(data, threadData);
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  TRACE_POP
  return 0;
}

void ThermoFMU_NoAmb_updateBoundParameters_0(DATA *data, threadData_t *threadData);
extern void ThermoFMU_NoAmb_eqFunction_4(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void ThermoFMU_NoAmb_updateBoundParameters_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ThermoFMU_NoAmb_eqFunction_4(data, threadData);
  TRACE_POP
}
OMC_DISABLE_OPT
int ThermoFMU_NoAmb_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ThermoFMU_NoAmb_updateBoundParameters_0(data, threadData);
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

