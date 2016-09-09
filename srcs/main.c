#include "raytracer.h"

int main(int argc, char **argv) {
	
	//test arguments
	if (argc <= 1) {
		printf("Please give at least one file to parse as parameter.\n");
		printf("./raytracer [FILE_1] {FILE_2} ... {FILE_N}\n");
		return (EXIT_FAILURE);
	}

	//for each files, parse it, render it to a texture, export the texture as bmp

	//scene buffer
	t_scene scene;

	//scene counter
	int i;
	
	for (i = 1; i < argc; i++) {

		//try loading
		if (loadSceneFile(&scene, argv[i]) < 0) {
			printf("Parsing scene %s failed.\n", argv[i]);
			continue ;
		}

		//try render
		if (renderScene(&scene) < 0) {
			printf("Rendering scene %s failed.\n", argv[i]);
			continue ;
		}
		
		//export scene to filepath
		if (exportScene(&scene, argv[i]) < 0) {
			printf("Export scene %s failed.\n", argv[i]);
			continue ;
		}

		//everything went ok
		printf("Scene parsed, rendered and exported at %s\n", argv[i]);
	}
	return (0);
}
