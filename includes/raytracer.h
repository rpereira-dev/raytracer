#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "array_list.h"
# include <string.h>

# define DEFAULT_SCENE_NAME ("defaultName")

typedef struct	s_scene {
	char 			*name;
	char 			*rawpixels;
	t_array_list	lights;
	t_array_list	objects;
}				t_scene;

/** a scene object: light, camera, primitives... */ 
typedef struct	s_object {
	
}				t_object;


/** parse the given scene file and store the data to the scene address */
int parseSceneFile(t_scene *scene, char *filepath);

/** render the scene */
int renderScene(t_scene *scene);

/** export the scene to the given path */
int exportScene(t_scene *scene, char *filepath);

#endif