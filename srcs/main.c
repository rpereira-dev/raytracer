#include "raytracer.h"

int main(int argc, char **argv) {
	
	//test arguments
	if (argc <= 1) {
		printf("Please give at least one file to parse as parameter.\n");
		printf("./raytracer [FILE_1] {FILE_2} ... {FILE_N}\n");
		return (EXIT_FAILURE);
	}

	//for each files, parse it, render it to a texture, export the texture as bmp

	//export file buffers
	char filepath[128];
	char *fileformat = ".rt";
	int fileformatlen = strlen(fileformat);
	int end = sizeof(filepath) - 1 - fileformatlen;

	//scene buffer
	t_scene scene;

	//scene counter
	int i;
	
	for (i = 1; i < argc; i++) {

		//try parse
		if (parseSceneFile(&scene, argv[i]) < 0) {
			printf("Parsing scene %s failed.\n", argv[i]);
			continue ;
		}

		//try render
		if (renderScene(&scene) < 0) {
			printf("Rendering scene %s failed.\n", argv[i]);
			continue ;
		}

		//generate export file's name
		strncpy(filepath, argv[i], end);
		strcat(filepath + end, fileformat);

		//export scene to filepath
		if (exportScene(&scene, filepath) < 0) {
			printf("Export scene %s failed.\n", argv[i]);
			continue ;
		}

		//everything went ok
		printf("Scene parsed, rendered and exported at %s\n", filepath);
	}
	return (0);
}
