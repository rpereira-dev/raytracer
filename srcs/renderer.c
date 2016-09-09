#include "raytracer.h"

	char 			*name; //scene name
	t_vec3			origin; //scene origin (to draw a scene into another)
	t_array_list 	scenes; //others scenes holds by this scene
	t_array_list	lights; //light of this scene
	t_array_list	objects; //objects of this scene (sphere, planes...)
	char 			*rawpixels;


/** prepare the scene for tests */
static void prepareScene(t_scene * scene) {
	vec3_set(&(scene->origin), 0, 0, 0);
	scene->scenes = array_list_new(16, sizeof(t_scene));
	scene->lights = array_list_new(16, sizeof(t_light));
	scene->objects = array_list_new(16, sizeof(t_scene_object));
	scene->width = 640;
	scene->height = 480;
	scene->rawpixels = (char*)malloc(scene->width * scene->height * 4);
}

/** render the given scene (the camera used is the one hold by the scene) */
int renderScene(t_scene * scene) {

	//prepare the scene for tests
	prepareScene(scene);


	// pixel's (x, y), for each pixels...
	int px, py;
	for (pxx = 0 ; pxx < scene->width; pxx++) {
		for (pxy = 0 ; pxy < scene->width; pxy++) {
			//generate ray

			//cast ray
		}
	}

	return (0);
}