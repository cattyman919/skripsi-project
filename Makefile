all: build

build:
	IF NOT EXIST src\performance\dummy.bin fsutil file createnew src\performance\dummy.bin 100000000
	@echo "Generating Build System Ninja..."
	cmake -B build
	@echo "Compiling \& Linking Project..."
	ninja -C build

cloud: build
	docker-compose --project-directory "server" up -d 

clean:
	rd /s /q build
