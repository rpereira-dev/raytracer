#include "raytracer.h"

# define BUFFER_SIZE (4096)
# define FILE_REALLOC (4096)
# define DEFAULT_SCENE_NAME ("defaultName")
# define COMMENT_CHAR ('#')

static void readAllFile(char * filepath, char ** dst, int * flength) {
	int fd = open(filepath, O_RDONLY);
	if (fd < 0) {
		return ;
	}

	char *file = (char*)malloc(FILE_REALLOC);
	if (file == NULL) {
		close(fd);
		return ;
	}
	int file_capacity = FILE_REALLOC;
	int file_length = 0;
	char buffer[BUFFER_SIZE];

	while (1) {

		//read
		int n = read(fd, buffer, BUFFER_SIZE);

		//if eof, stop
		if ((int)n <= 0) {
			break ;
		}

		//copy chars
		int i;
		int quotes = 0;
		for (i = 0 ; i < n ; i++) {

			if (buffer[i] == '"' || buffer[i] == '\'') {
				quotes = !quotes;
			}

			//skip whitespaces
			if (!quotes && (buffer[i] == ' ' || buffer[i] == '\t')) {
				continue ;
			}

			//skip comments
			if (buffer[i] == COMMENT_CHAR) {
				while (++i < n && buffer[i] != '\n' && buffer[i] != '\r');
			}

			if (buffer[i] == '\r') {
				continue ;
			}

			//check file size
			if (file_length >= file_capacity) {
				file = (char*)realloc(file, file_length + FILE_REALLOC);
				if (file == NULL) {
					close(fd);
					return ;
				}
			}

			//copy char
			file[file_length++] = buffer[i];
		}
	}

	close(fd);

	*dst = file;
	*flength = file_length;
}

//represent an attribute
typedef struct	s_fattr {
	int typeID;
	char * name;
	int flags;
	int extra;
}				t_fattr;

enum e_attr_ids {
	ATTR_NONE,
	ATTR_STRING,
	ATTR_CHAR,
	ATTR_SCALAR,
	ATTR_OBJECT
};

enum e_attr_flags {
	ATTR_O_OPTIONAL = 1 << 0
};

//an object
typedef struct	t_fobject {
	char * name;
	int attr_count;
	t_fattr * attrs;
}				t_fobject;

enum e_object_ids {
	OBJ_NONE,
	OBJ_COLOR,
	OBJ_POSITION,
	OBJ_SCENE,
	OBJ_CAMERA,
	OBJ_LIGHT,
	OBJ_OBJECT
};

t_fobject objects[] = {
	{NULL,			0,		NULL},

	{"color",		4,		(t_fattr[]){{ATTR_SCALAR, "r", 0, 0},
										{ATTR_SCALAR, "g", 0, 0},
										{ATTR_SCALAR, "b", 0, 0},
										{ATTR_SCALAR, "a", ATTR_O_OPTIONAL, 0}
									}},

	{"position",	4,		(t_fattr[]){{ATTR_SCALAR, "x", 0, 0},
										{ATTR_SCALAR, "y", 0, 0},
										{ATTR_SCALAR, "z", 0, 0},
										{ATTR_SCALAR, "w", ATTR_O_OPTIONAL, 0}
									}},

	{"scene",		4,		(t_fattr[]){{ATTR_STRING, "name", ATTR_O_OPTIONAL, 0},
										{ATTR_OBJECT, "camera", ATTR_O_OPTIONAL, OBJ_CAMERA},
										{ATTR_OBJECT, "light", ATTR_O_OPTIONAL, OBJ_LIGHT},
										{ATTR_OBJECT, "object", ATTR_O_OPTIONAL, OBJ_OBJECT}
									}},


	{"camera",		4,		(t_fattr[]){{ATTR_STRING, "type", ATTR_O_OPTIONAL, 0},
										{ATTR_SCALAR, "near", ATTR_O_OPTIONAL, 0},
										{ATTR_SCALAR, "far", ATTR_O_OPTIONAL, 0},
										{ATTR_SCALAR, "fov", ATTR_O_OPTIONAL, 0},
									}},

	{"light",		4,		(t_fattr[]){{ATTR_STRING, "type", ATTR_O_OPTIONAL, 0},
										{ATTR_SCALAR, "intensity", ATTR_O_OPTIONAL, 0},
										{ATTR_OBJECT, "color", ATTR_O_OPTIONAL, OBJ_COLOR},
										{ATTR_OBJECT, "position", ATTR_O_OPTIONAL, OBJ_POSITION},
									}},

	{"object",		4,		(t_fattr[]){{ATTR_STRING, "type", ATTR_O_OPTIONAL, 0},
										{ATTR_SCALAR, "intensity", ATTR_O_OPTIONAL, 0},
										{ATTR_OBJECT, "color", ATTR_O_OPTIONAL, OBJ_COLOR},
										{ATTR_OBJECT, "position", ATTR_O_OPTIONAL, OBJ_POSITION},
									}},
};

/**
static int parseString() {

}

static int parseChar() {
	
}

static int parseScalar() {
	
}

static int parseVec3() {
	
}
*/

typedef struct	s_object {
	int objID;
	void * data;
}				t_object;

static void parseNextObject(t_array_list * objs, char * file, int flength, int *lnum, int *cursor) {
	(void)objs;
	(void)file;
	(void)flength;
	(void)lnum;
	(void)cursor;
	(*cursor) += 10000;
}

static void parseFile(t_scene * scene, char * file, int flength) {
	(void)scene;

	int cursor = 0;
	int lnum = 1;
	t_array_list objects = array_list_new(16, sizeof(t_object));
	while (cursor < flength) {
		parseNextObject(&objects, file, flength, &lnum, &cursor);
	}
}

int loadSceneFile(t_scene *scene, char *filepath) {
	char * file = NULL;
	int flength = 0;

	//read file
	readAllFile(filepath, &file, &flength);
	if (file == NULL || flength == 0) {
		return (-1);
	}

	//parse file
	parseFile(scene, file, flength);
	(void)scene;
	return (0);
}