BUILD_TYPE ?= Release

BUILD_DIR = build

NON_VM_TARGETS = app_imgui app_imgui_cloud app_qt app_qt_cloud console console_cloud quick_sort encryption size Lilith_Server
VM_TARGETS = app_imgui_vm app_imgui_cloud_vm app_qt_vm app_qt_cloud_vm console_vm console_cloud_vm quick_sort_vm encryption_vm size_vm Lilith_Client_vm

.PHONY: all build build_vm_executables build_vm cloud clean help configure dummy rebuild_vm

all: build build_vm

configure: dummy
	@echo "Configuring Build System (Unified)..."
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -G Ninja

build: configure
	@echo "Compiling & Linking Non-Virtualized Build..."
	ninja -C $(BUILD_DIR) $(NON_VM_TARGETS)

build_vm_executables: configure
	@echo "Compiling & Linking Virtualized Build Executables..."
	ninja -C $(BUILD_DIR) $(VM_TARGETS)

build_vm: build_vm_executables
	@echo "Running VxLang on virtualized executables..."
	virtualize.bat 

rebuild_vm: 
	@echo "Re-running VxLang on existing virtualized executables..."
	$(MAKE) clean_vxm_files 
	virtualize.bat

clean_vxm_files:
	@echo "Deleting existing .vxm.exe files..."
	@for %%T in ($(subst _vm,, $(VM_TARGETS))) do ( \
		IF EXIST "bin\%%T\$(BUILD_TYPE)\%%T_vm.vxm.exe" ( \
			echo Deleting bin\%%T\$(BUILD_TYPE)\%%T_vm.vxm.exe & \
			del /F /Q "bin\%%T\$(BUILD_TYPE)\%%T_vm.vxm.exe" \
		) \
		IF EXIST "bin\%%T\$(BUILD_TYPE)\%%T_cloud_vm.vxm.exe" ( \
			echo Deleting bin\%%T\$(BUILD_TYPE)\%%T_cloud_vm.vxm.exe & \
			del /F /Q "bin\%%T\$(BUILD_TYPE)\%%T_cloud_vm.vxm.exe" \
		) \
	)

cloud: 
	docker-compose --project-directory "server" up -d 

dummy:
	IF NOT EXIST src\performance\dummy.bin fsutil file createnew src\performance\dummy.bin 100000000

clean: 
	@echo "Cleaning build directory and bin folder..."
	IF EXIST $(BUILD_DIR) rd /s /q $(BUILD_DIR)
	IF EXIST bin rd /s /q bin

help:
	@echo.
	@echo 'make [BUILD_TYPE=Debug|Release]   build all non-VM and VM targets (VMs processed by vxlang)'
	@echo 'make build                        build only non-VM targets'
	@echo 'make build_vm_executables         build only VM target executables (before vxlang)'
	@echo 'make build_vm                     build VM target executables and run vxlang'
	@echo 'make rebuild_vm                   re-run vxlang on existing VM executables'
	@echo 'make cloud                        run cloud as docker container'
	@echo 'make clean                        remove any generated files'
	@echo 'make configure                    (usually implicit) runs cmake for the unified build'
	@echo.
	@echo 'Example: make BUILD_TYPE=Debug'

