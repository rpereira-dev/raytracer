#include "raytracer.h"


static int exportBMP(char * rgba, int width, int height, char * filepath) {

	if (rgba == NULL || width == 0 || height == 0 || filepath == NULL) {
		return (-1);
	}

	//if format error, return
	unsigned int imsize = width * height * 4;

	//header
	int hsize = 14 + 40;
	int fsize = imsize + hsize;
	char header[14] = {
							'B', 'M', //magic
							(fsize >> 0) & 0xFF, (fsize >> 8) & 0xFF, (fsize >> 16) & 0xFF, (fsize >> 24) & 0xFF, //file size
							' ', ' ', ' ', ' ', //signature (author)
							(hsize >> 0) & 0xFF, (hsize >> 8) & 0xFF, (hsize >> 16) & 0xFF, (hsize >> 24) & 0xFF, //header size
					};


	char postheader[40] = {
							40, 0, 0, 0, //size of the post header
							(width >> 0) & 0xFF, (width >> 8) & 0xFF, (width >> 16) & 0xFF, (width >> 24) & 0xFF, //image width
							(height >> 0) & 0xFF, (height >> 8) & 0xFF, (height >> 16) & 0xFF, (height >> 24) & 0xFF, //image height
							1, 1, //plane
							32, 0, //bit per pixel (bpp)
							0, 0, 0, 0, //compression (0 = uncompressed)
							(imsize >> 0) & 0xFF, (imsize >> 8) & 0xFF, (imsize >> 16) & 0xFF, (imsize >> 24) & 0xFF, //image size
							0, 0, 0, 0, //prefered res X in pixel per meter
							0, 0, 0, 0, //prefered res Y in pixel per meter
							0, 0, 0, 0, //color map enties used
							0, 0, 0, 0 //significant colors

	};

	//create buffer
	void * fbuffer = (void *)malloc(fsize);
	if (fbuffer == NULL) {
		return (-1);
	}

	//copy
	memcpy(fbuffer,											header,		sizeof(header));
	memcpy(fbuffer + sizeof(header),						postheader,	sizeof(postheader));
	memcpy(fbuffer + sizeof(header) + sizeof(postheader),	rgba,		imsize);

	//everthing is ok, create and trunc the file
	int fd = open(filepath, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0) {
		return (-1);
	}

	//write the image
	write(fd, fbuffer, fsize);

	//free
	free(fbuffer);
	//close
	close(fd);

	return (1);
}

/** export scene image */
int exportScene(t_scene *scene, char *filepath) {

	//generate export file's name
	char buffer[128];
	unsigned int i;

	for (i = 0 ; i < sizeof(buffer) - 5 ; i++) {
		char c = filepath[i];
		if (c == 0 || c == '.') {
			break ;
		}
		buffer[i] = c;
	}
	memcpy(buffer + i, ".bmp", 4);
	buffer[i + 4] = 0;

	//export as bmp
	printf("Exporting to : %s\n", buffer);
	return (exportBMP(scene->rawpixels, scene->width, scene->height, buffer));
}