/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "ThermoFMU_NoAmb_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int ThermoFMU_NoAmb_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[5] /* cg_rate variable */) = data->simulationInfo->inputVars[0];
  (data->localData[0]->realVars[7] /* pump_state variable */) = data->simulationInfo->inputVars[1];
  (data->localData[0]->realVars[8] /* sg variable */) = data->simulationInfo->inputVars[2];
  
  TRACE_POP
  return 0;
}

int ThermoFMU_NoAmb_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[5].attribute.start;
  data->simulationInfo->inputVars[1] = data->modelData->realVarsData[7].attribute.start;
  data->simulationInfo->inputVars[2] = data->modelData->realVarsData[8].attribute.start;
  
  TRACE_POP
  return 0;
}

int ThermoFMU_NoAmb_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[5].attribute.start = data->simulationInfo->inputVars[0];
  data->modelData->realVarsData[7].attribute.start = data->simulationInfo->inputVars[1];
  data->modelData->realVarsData[8].attribute.start = data->simulationInfo->inputVars[2];
  
  TRACE_POP
  return 0;
}

int ThermoFMU_NoAmb_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[5].info.name;
  names[1] = (char *) data->modelData->realVarsData[7].info.name;
  names[2] = (char *) data->modelData->realVarsData[8].info.name;
  
  TRACE_POP
  return 0;
}

int ThermoFMU_NoAmb_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int ThermoFMU_NoAmb_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ThermoFMU_NoAmb_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ThermoFMU_NoAmb_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[2] /* Q_beer variable */);
  data->simulationInfo->outputVars[1] = (data->localData[0]->realVars[3] /* Temperature variable */);
  
  TRACE_POP
  return 0;
}

int ThermoFMU_NoAmb_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ThermoFMU_NoAmb_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 7
type: SIMPLE_ASSIGN
density = 997.0 * sg
*/
void ThermoFMU_NoAmb_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  (data->localData[0]->realVars[6] /* density variable */) = (997.0) * ((data->localData[0]->realVars[8] /* sg variable */));
  TRACE_POP
}
/*
equation index: 8
type: SIMPLE_ASSIGN
$DER.T = ((-dH) * cg_rate * Vol_meters - pump_state * h * A_coil * (T - T_pump)) / (Vol_meters * Cp * density)
*/
void ThermoFMU_NoAmb_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->realVars[1] /* der(T) STATE_DER */) = DIVISION_SIM(((-(data->simulationInfo->realParameter[5] /* dH PARAM */))) * (((data->localData[0]->realVars[5] /* cg_rate variable */)) * ((data->localData[0]->realVars[4] /* Vol_meters variable */))) - (((data->localData[0]->realVars[7] /* pump_state variable */)) * (((data->simulationInfo->realParameter[6] /* h PARAM */)) * (((data->simulationInfo->realParameter[0] /* A_coil PARAM */)) * ((data->localData[0]->realVars[0] /* T STATE(1) */) - (data->simulationInfo->realParameter[3] /* T_pump PARAM */))))),(((data->localData[0]->realVars[4] /* Vol_meters variable */)) * ((data->simulationInfo->realParameter[1] /* Cp PARAM */))) * ((data->localData[0]->realVars[6] /* density variable */)),"Vol_meters * Cp * density",equationIndexes);
  TRACE_POP
}
/*
equation index: 9
type: SIMPLE_ASSIGN
Q_beer = density * Cp * Vol_meters * der(T)
*/
void ThermoFMU_NoAmb_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  (data->localData[0]->realVars[2] /* Q_beer variable */) = ((data->localData[0]->realVars[6] /* density variable */)) * (((data->simulationInfo->realParameter[1] /* Cp PARAM */)) * (((data->localData[0]->realVars[4] /* Vol_meters variable */)) * ((data->localData[0]->realVars[1] /* der(T) STATE_DER */))));
  TRACE_POP
}
/*
equation index: 10
type: SIMPLE_ASSIGN
Temperature = T
*/
void ThermoFMU_NoAmb_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  (data->localData[0]->realVars[3] /* Temperature variable */) = (data->localData[0]->realVars[0] /* T STATE(1) */);
  TRACE_POP
}

OMC_DISABLE_OPT
int ThermoFMU_NoAmb_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  ThermoFMU_NoAmb_functionLocalKnownVars(data, threadData);
  ThermoFMU_NoAmb_eqFunction_7(data, threadData);

  ThermoFMU_NoAmb_eqFunction_8(data, threadData);

  ThermoFMU_NoAmb_eqFunction_9(data, threadData);

  ThermoFMU_NoAmb_eqFunction_10(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int ThermoFMU_NoAmb_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/* forwarded equations */
extern void ThermoFMU_NoAmb_eqFunction_7(DATA* data, threadData_t *threadData);
extern void ThermoFMU_NoAmb_eqFunction_8(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  {
    ThermoFMU_NoAmb_eqFunction_7(data, threadData);
    threadData->lastEquationSolved = 7;
  }
  {
    ThermoFMU_NoAmb_eqFunction_8(data, threadData);
    threadData->lastEquationSolved = 8;
  }
}

int ThermoFMU_NoAmb_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  ThermoFMU_NoAmb_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "ThermoFMU_NoAmb_12jac.h"
#include "ThermoFMU_NoAmb_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks ThermoFMU_NoAmb_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   ThermoFMU_NoAmb_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   ThermoFMU_NoAmb_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   ThermoFMU_NoAmb_initializeDAEmodeData,
   ThermoFMU_NoAmb_functionODE,
   ThermoFMU_NoAmb_functionAlgebraics,
   ThermoFMU_NoAmb_functionDAE,
   ThermoFMU_NoAmb_functionLocalKnownVars,
   ThermoFMU_NoAmb_input_function,
   ThermoFMU_NoAmb_input_function_init,
   ThermoFMU_NoAmb_input_function_updateStartValues,
   ThermoFMU_NoAmb_data_function,
   ThermoFMU_NoAmb_output_function,
   ThermoFMU_NoAmb_setc_function,
   ThermoFMU_NoAmb_setb_function,
   ThermoFMU_NoAmb_function_storeDelayed,
   ThermoFMU_NoAmb_function_storeSpatialDistribution,
   ThermoFMU_NoAmb_function_initSpatialDistribution,
   ThermoFMU_NoAmb_updateBoundVariableAttributes,
   ThermoFMU_NoAmb_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   ThermoFMU_NoAmb_functionRemovedInitialEquations,
   ThermoFMU_NoAmb_updateBoundParameters,
   ThermoFMU_NoAmb_checkForAsserts,
   ThermoFMU_NoAmb_function_ZeroCrossingsEquations,
   ThermoFMU_NoAmb_function_ZeroCrossings,
   ThermoFMU_NoAmb_function_updateRelations,
   ThermoFMU_NoAmb_zeroCrossingDescription,
   ThermoFMU_NoAmb_relationDescription,
   ThermoFMU_NoAmb_function_initSample,
   ThermoFMU_NoAmb_INDEX_JAC_A,
   ThermoFMU_NoAmb_INDEX_JAC_B,
   ThermoFMU_NoAmb_INDEX_JAC_C,
   ThermoFMU_NoAmb_INDEX_JAC_D,
   ThermoFMU_NoAmb_INDEX_JAC_F,
   ThermoFMU_NoAmb_INDEX_JAC_H,
   ThermoFMU_NoAmb_initialAnalyticJacobianA,
   ThermoFMU_NoAmb_initialAnalyticJacobianB,
   ThermoFMU_NoAmb_initialAnalyticJacobianC,
   ThermoFMU_NoAmb_initialAnalyticJacobianD,
   ThermoFMU_NoAmb_initialAnalyticJacobianF,
   ThermoFMU_NoAmb_initialAnalyticJacobianH,
   ThermoFMU_NoAmb_functionJacA_column,
   ThermoFMU_NoAmb_functionJacB_column,
   ThermoFMU_NoAmb_functionJacC_column,
   ThermoFMU_NoAmb_functionJacD_column,
   ThermoFMU_NoAmb_functionJacF_column,
   ThermoFMU_NoAmb_functionJacH_column,
   ThermoFMU_NoAmb_linear_model_frame,
   ThermoFMU_NoAmb_linear_model_datarecovery_frame,
   ThermoFMU_NoAmb_mayer,
   ThermoFMU_NoAmb_lagrange,
   ThermoFMU_NoAmb_pickUpBoundsForInputsInOptimization,
   ThermoFMU_NoAmb_setInputData,
   ThermoFMU_NoAmb_getTimeGrid,
   ThermoFMU_NoAmb_symbolicInlineSystem,
   ThermoFMU_NoAmb_function_initSynchronous,
   ThermoFMU_NoAmb_function_updateSynchronous,
   ThermoFMU_NoAmb_function_equationsSynchronous,
   ThermoFMU_NoAmb_inputNames,
   ThermoFMU_NoAmb_dataReconciliationInputNames,
   ThermoFMU_NoAmb_dataReconciliationUnmeasuredVariables,
   ThermoFMU_NoAmb_read_input_fmu,
   NULL,
   NULL,
   -1,
   NULL,
   NULL,
   -1

};

#define _OMC_LIT_RESOURCE_0_name_data "Complex"
#define _OMC_LIT_RESOURCE_0_dir_data "C:/Users/20181234/AppData/Roaming/.openmodelica/libraries/Complex 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,7,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,80,_OMC_LIT_RESOURCE_0_dir_data);

#define _OMC_LIT_RESOURCE_1_name_data "Modelica"
#define _OMC_LIT_RESOURCE_1_dir_data "C:/Users/20181234/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,8,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,81,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_2_dir_data "C:/Users/20181234/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,16,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,89,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "ThermoFMU_NoAmb"
#define _OMC_LIT_RESOURCE_3_dir_data "D:/Personal/OneDrive/OrchTwin/Brewery_SiM"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,15,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,41,_OMC_LIT_RESOURCE_3_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,8,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir)}};
void ThermoFMU_NoAmb_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &ThermoFMU_NoAmb_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "ThermoFMU_NoAmb";
  data->modelData->modelFilePrefix = "ThermoFMU_NoAmb";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "D:/Personal/OneDrive/OrchTwin/Brewery_SiM";
  data->modelData->modelGUID = "{eac53829-e49e-4303-b0e9-931946015a64}";
  data->modelData->encrypted = 0;
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/ThermoFMU_NoAmb_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 1;
  data->modelData->nVariablesReal = 9;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 0;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 7;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 3;
  data->modelData->nOutputVars = 2;
  data->modelData->nAliasReal = 2;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 0;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 0;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 13;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 0;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 6;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  data->modelData->nDelayExpressions = 0;
  data->modelData->nBaseClocks = 0;
  data->modelData->nSpatialDistributions = 0;
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
  data->modelData->nSetcVars = 0;
  data->modelData->ndataReconVars = 0;
  data->modelData->nSetbVars = 0;
  data->modelData->nRelatedBoundaryConditions = 0;
  data->modelData->linearizationDumpLanguage = OMC_LINEARIZE_DUMP_LANGUAGE_MODELICA;
}

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}

