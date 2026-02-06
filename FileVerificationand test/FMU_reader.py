import fmpy
import os


def read_fmu_metadata_fmpy(fmu_path: str):
    md = fmpy.read_model_description(fmu_path)  # parses modelDescription.xml for you[web:34][web:39]

    print("FMI version:", md.fmiVersion)
    print("Model name:", md.modelName)
    print("GUID:", md.guid)
    print("Description:", md.description)
    print("Generation tool:", md.generationTool)

    print("\nVariables:")
    for v in md.modelVariables:
        print(f"  {v.name}: type={v.type}, causality={v.causality}, variability={v.variability}")

# Example
# current folder
path = os.getcwd()

model_name = "ThermoDynamics.fmu"
# model_name = 'MyModel.fmu'
full_path = os.path.join(path, model_name)
read_fmu_metadata_fmpy(full_path)
# print(type(full_path))
# print(full_path)
# fmpy.dump(full_path)

