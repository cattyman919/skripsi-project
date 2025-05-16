echo off
setlocal enabledelayedexpansion

set build_type=Release
set vxlang=vxlang\\vxlang.exe

set target[0]=app_imgui
set target[1]=app_qt
set target[2]=console
set target[3]=encryption
set target[4]=Lilith_Client
set target[5]=quick_sort
set target[6]=size

echo.
for /l %%i in (0,1,6) do (
  set "target_path=bin\\!target[%%i]!\\!build_type!\\!target[%%i]!"

  echo Virtualizing !target[%%i]!

  if exist !target_path!_vm.vxm.exe (echo !target_path!_vm.vxm.exe already exist) else (if exist !target_path!_vm.exe (!vxlang! !target_path!_vm.exe) else (echo !target_path!_vm.exe does not exist. Try build it again))

  if exist !target_path!_cloud_vm.vxm.exe (echo !target_path!_cloud_vm.vxm.exe already exist) else (if exist !target_path!_cloud_vm.exe (!vxlang! !target_path!_cloud_vm.exe) else (echo !target_path!_cloud_vm.exe does not exist. Try build it again))

  REM if exist !target_path!_vm.exe (del !target_path!_vm.exe)
  REM if exist !target_path!_cloud_vm.exe (del !target_path!_cloud_vm.exe)

  echo.
)

endlocal
