#include "raytracer.h"

/** prepare the scene for tests */
static void prepareScene(t_scene * scene) {
	//scene origin
	vec3_set(&(scene->origin), 0, 0, 0);
	
	//objects
	scene->scenes = array_list_new(16, sizeof(t_scene));
	scene->lights = array_list_new(16, sizeof(t_light));
	scene->objects = array_list_new(16, sizeof(t_scene_object));
	
	//image
	scene->width = 640;
	scene->height = 480;
	scene->rawpixels = (char*)malloc(scene->width * scene->height * 4);
	
	//camera
	vec3_set(&(scene->camera.pos), 0, 0, 0);
	mat4_identity(&(scene->camera.mview));
	mat4_identity(&(scene->camera.mproj));
	mat4_identity(&(scene->camera.mviewproj));
	scene->camera.fov = 70;
	scene->camera.near = 0.01f;
	scene->camera.far = 1000;
}

static int intersectSphere(t_vec3 * ray, void * object, float * distance) {
	t_sphere * sphere = (t_sphere*)object;
	(void)ray;
	(void)sphere;
	(void)distance;
	return (0);
}

static void castRay(t_scene * scene, t_vec3 * ray, t_vec4 * color) {
	(void)scene;
	(void)ray;

	/** intersection functions */
	static int (*intersectObject[])(t_vec3 * ray, void * object, float * distance) = {intersectSphere};

	//intersection distance
	float distance;

	//for each scene object
	ARRAY_LIST_ITER_START(&(scene->objects), t_scene_object *, object, i) {

		//if the ray intersect the object
		if (intersectObject[object->typeID](ray, object, &distance)) {
			vec4_set4(color, (t_vec4 *)&(object->color));
		}
	}
	ARRAY_LIST_ITER_END(&(scene->objects), t_scene_object *, object, i);
	
	color->r = 1.0f;
	color->g = 0.0f;
	color->b = 0.0f;
	color->a = 1.0f;
}

static void generateRay(t_camera * camera, t_vec3 * ray, int pxx, int pxy) {
	(void)camera;
	(void)ray;
	(void)pxx;
	(void)pxy;
}

/** render the given scene (the camera used is the one hold by the scene) */
int renderScene(t_scene * scene) {

	//prepare the scene for tests
	prepareScene(scene);

	// pixel's (x, y), for each pixels...
	t_vec3 ray;
	int pxx, pxy;
	int index;
	t_vec4 color;
//	float aspect = scene->width / (float)scene->height;
	for (pxy = 0 ; pxy < scene->height; pxy++) {
		for (pxx = 0 ; pxx < scene->width; pxx++) {
			//generate ray
			generateRay(&(scene->camera), &ray, pxx, pxy);

			//cast ray
			castRay(scene, &ray, &color);

			//set the pixel
			vec4_mult(&color, &color, 255.0f),
			scene->rawpixels[index++] = (int)color.b;
			scene->rawpixels[index++] = (int)color.g;
			scene->rawpixels[index++] = (int)color.r;
			scene->rawpixels[index++] = (int)color.a;
		}
	}

	return (0);
}