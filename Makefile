cod_fov_changer : src/main.cpp
	g++ -pthread -o cod_fov_changer src/main.cpp
	chmod +x cod_fov_changer
	@echo "Build completed"

clean :
	rm cod_fov_changer