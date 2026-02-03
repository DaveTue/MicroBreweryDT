/* Algebraic */
#include "ThermoFMU_NoAmb_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void ThermoFMU_NoAmb_eqFunction_9(DATA* data, threadData_t *threadData);
extern void ThermoFMU_NoAmb_eqFunction_10(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  {
    ThermoFMU_NoAmb_eqFunction_9(data, threadData);
    threadData->lastEquationSolved = 9;
  }
  {
    ThermoFMU_NoAmb_eqFunction_10(data, threadData);
    threadData->lastEquationSolved = 10;
  }
}
/* for continuous time variables */
int ThermoFMU_NoAmb_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  ThermoFMU_NoAmb_function_savePreSynchronous(data, threadData);
  
  functionAlg_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ALGEBRAICS);
#endif

  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
