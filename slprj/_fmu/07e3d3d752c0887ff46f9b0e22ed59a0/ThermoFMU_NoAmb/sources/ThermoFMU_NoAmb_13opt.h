#if defined(__cplusplus)
  extern "C" {
#endif
  int ThermoFMU_NoAmb_mayer(DATA* data, modelica_real** res, short*);
  int ThermoFMU_NoAmb_lagrange(DATA* data, modelica_real** res, short *, short *);
  int ThermoFMU_NoAmb_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int ThermoFMU_NoAmb_setInputData(DATA *data, const modelica_boolean file);
  int ThermoFMU_NoAmb_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif