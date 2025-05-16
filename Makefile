BUILD_TYPE ?= Release
BUILD_DIR = build
CMAKE_CACHE_FILE = $(BUILD_DIR)/CMakeCache.txt

.PHONY: all build cloud clean help configure dummy rebuild_vm add_deps_executables virtualize

all: build

configure: dummy
	@echo "Checking configuration status..."
	@IF NOT EXIST "$(CMAKE_CACHE_FILE)" ( \
		echo Initial configuration or CMakeCache.txt missing... & \
		echo Configuring Build System ... & \
		cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -G Ninja \
	) else ( \
		echo CMakeCache.txt found, skipping explicit CMake run. Ninja will re-run if needed. \
	)

build: configure
	@echo "Compiling & Linking..."
	ninja -C $(BUILD_DIR) 
	$(MAKE) add_deps_executables
	$(MAKE) virtualize

virtualize: 
	@echo "Running VxLang on virtualized executables..."
	virtualize.bat 

add_deps_executables: 
	@echo "Adding the required dependencies for executables"
	@IF NOT EXIST bin\\console\\$(BUILD_TYPE)\\libcurl.dll (COPY dll\\libcurl.dll bin\\console\\$(BUILD_TYPE))
	@IF NOT EXIST bin\\app_imgui\\$(BUILD_TYPE)\\libcurl.dll (COPY dll\\libcurl.dll bin\\app_imgui\\$(BUILD_TYPE))
	@IF NOT EXIST bin\\app_qt\\$(BUILD_TYPE)\\libcurl.dll (COPY dll\\libcurl.dll bin\\app_qt\\$(BUILD_TYPE))
ifeq ($(BUILD_TYPE), Release)
	@IF NOT EXIST bin\\app_qt\\$(BUILD_TYPE)\\Qt6Core.dll (windeployqt bin\\app_qt\\Release)
endif

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
	@echo 'make rebuild_vm                   re-run vxlang on existing VM executables'
	@echo 'make cloud                        run cloud as docker container'
	@echo 'make clean                        remove any generated files'
	@echo 'make configure                    (usually implicit) runs cmake for the unified build'
	@echo.
	@echo 'Example: make BUILD_TYPE=Debug'

