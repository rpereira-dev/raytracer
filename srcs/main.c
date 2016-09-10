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

		printf("-----------------------------------------------\n");
		printf("Loading scene %s ...\n", argv[i]);

		//try loading
		if (loadSceneFile(&scene, argv[i]) < 0) {
			printf("Parsing scene %s failed.\n", argv[i]);
			continue ;
		}

		printf("Loaded\n");

		printf("Rendering scene %s ... \n", argv[i]);

		//try render
		if (renderScene(&scene) < 0) {
			printf("Rendering scene %s failed.\n", argv[i]);
			continue ;
		}

		printf("Rendered\n");

		printf("Exporting scene %s ...\n", argv[i]);

		//export scene to filepath
		if (exportScene(&scene, argv[i]) < 0) {
			printf("Export scene %s failed.\n", argv[i]);
			continue ;
		}

		printf("Exported\n");
	}
	return (0);
}
