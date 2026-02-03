%% FMU Validation Test Script for ThermoDynamics.fmu
clear; close all; clc;

fmu_path = 'D:\Git_folders\DT_examplars\MicroBreweryDT\ThermoDynamics.fmu';

%% Step 1: Basic FMU Check - Unzip and inspect
fprintf('=== Step 1: Basic FMU Structure Check ===\n');
try
    % Check if FMU exists and can be read
    if ~isfile(fmu_path)
        error('FMU file not found: %s', fmu_path);
    end
    fprintf('✓ FMU file exists\n');
    
    % Quick unzip test (creates temp dir)
    temp_dir = [tempname '_fmu'];
    unzip(fmu_path, temp_dir);
    if isfile(fullfile(temp_dir, 'modelDescription.xml'))
        fprintf('✓ modelDescription.xml found\n');
    else
        error('No modelDescription.xml in FMU');
    end
    rmdir(temp_dir, 's'); % cleanup
catch ME
    fprintf('ERROR Step 1: %s\n', ME.message);
    return;
end

%% Step 2: Create and Test FMU Block
model_name = 'ThermoDynamics_Test';
fprintf('\n=== Step 2: FMU Block Test ===\n');

if bdIsLoaded(model_name)
    close_system(model_name, 0);
end

try
    new_system(model_name);
    open_system(model_name);
    
    % Add FMU block from Simulink library
    add_block('fmilib/Functional Mock-up Unit', [model_name '/ThermoDynamics']);
    set_param([model_name '/ThermoDynamics'], 'FMUName', fmu_path);
    
    % Basic model setup
    set_param(model_name, 'StopTime', '0.1');
    set_param(model_name, 'SolverType', 'Fixed-step');
    set_param(model_name, 'FixedStep', '0.01');
    
    fprintf('✓ FMU block loaded successfully\n');
    fprintf('Open model "%s" and check block parameters\n', model_name);
    
catch ME
    fprintf('ERROR Step 2 (Block Load): %s\n', ME.message);
    if bdIsLoaded(model_name)
        close_system(model_name, 0);
    end
    return;
end

%% Step 3: Simulation Test (manual trigger needed)
fprintf('\n=== Step 3: Ready for Simulation ===\n');
fprintf('1. Press Ctrl+T to Update Diagram\n');
fprintf('2. Press Ctrl+E to Simulate (1-second test)\n');
fprintf('3. Check for DLL/runtime errors\n');

fprintf('\n=== Test Complete ===\n');
% Model stays open for manual inspection/simulation
