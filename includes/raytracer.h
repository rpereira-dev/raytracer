#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "array_list.h"
# include "vec2.h"
# include "vec3.h"
# include "vec4.h"
# include "mat4.h"
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

/** a generic scene object. */ 
typedef struct	s_scene_object {
	t_vec3 pos;
	t_vec3 color;
}				t_scene_object;

typedef struct	s_light {
	t_vec3 pos;
	t_vec3 color;
}				t_light;

typedef struct	s_camera {
	t_vec3	pos;
	float	fov;
	float 	near;
	float	far;
}				t_camera;

typedef struct	s_scene {
	char 			*name; //scene name
	t_vec3			origin; //scene origin (to draw a scene into another)
	t_camera		camera;
	t_array_list 	scenes; //others scenes holds by this scene
	t_array_list	lights; //light of this scene
	t_array_list	objects; //objects of this scene (sphere, planes...)
	char 			*rawpixels;
	int 			width;
	int 			height;
}				t_scene;

/** parse the given scene file and store the data to the scene address */
int loadSceneFile(t_scene * scene, char * filepath);

/** render the scene */
int renderScene(t_scene * scene);

/** export the scene to the given path */
int exportScene(t_scene * scene, char * filepath);

#endif