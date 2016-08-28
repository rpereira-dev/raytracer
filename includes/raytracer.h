#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "array_list.h"
# include <string.h>

# define DEFAULT_SCENE_NAME ("defaultName")

/** a generic scene object. */ 
typedef struct	s_object {
	t_vec3 origin;
	t_vec3 color;
}				t_object;

typedef struct	s_scene {
	char 			*name; //scene name
	t_vec3			origin; //scene origin (to draw a scene into another)
	t_array_list	lights; //light of this scene
	t_array_list	objects; //objects of this scene (sphere, planes...)
	t_array_list 	scenes; //others scenes holds by this scene
	char 			*rawpixels;
}				t_scene;

/** parse the given scene file and store the data to the scene address */
int parseSceneFile(t_scene *scene, char *filepath);

/** render the scene */
int renderScene(t_scene *scene);

/** export the scene to the given path */
int exportScene(t_scene *scene, char *filepath);

#endif