#include "imageutils.h"
#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
//#define STBIR_DEFAULT_FILTER_DOWNSAMPLE STBIR_FILTER_BOX
//#define STBIR_DEFAULT_FILTER_UPSAMPLE STBIR_FILTER_BOX
//#define STBIR_DEFAULT_FILTER_DOWNSAMPLE STBIR_FILTER_TRIANGLE
//#define STBIR_DEFAULT_FILTER_UPSAMPLE STBIR_FILTER_TRIANGLE
#define STBIR_DEFAULT_FILTER_DOWNSAMPLE STBIR_FILTER_CATMULLROM
#define STBIR_DEFAULT_FILTER_UPSAMPLE STBIR_FILTER_CATMULLROM
//#define STBIR_DEFAULT_FILTER_DOWNSAMPLE STBIR_FILTER_CUBICBSPLINE
//#define STBIR_DEFAULT_FILTER_UPSAMPLE STBIR_FILTER_CUBICBSPLINE
#include <stb/stb_image_resize.h>

namespace wb {

namespace {

StringMap<Image*> g_imageCache;
Map<Image*, String> g_imagePaths;

} // namespace

Image* createImage(uint width, uint height, PixelFormat format) {

	uint pitch = width * bytesPerPixel(format);
	void* data = malloc(pitch * height);

	Image* image = new Image(data, width, height, pitch, format);

	image->deleted.connect([data] { free(data); });

	return image;
}

Image* loadImage(CString path, PixelFormat format) {

	auto it = g_imageCache.find(path);
	if (it != g_imageCache.end()) return it->second;

	uint bpp = bytesPerPixel(format);
	int width, height, n;
	void (*freeFunc)(void*);
	void* data;

	if (format == PixelFormat::r32f) {

		ushort* sdata = (ushort*)stbi_load_16(path.c_str(), &width, &height, &n, 1);
		if (!sdata) panic("Can't load image " + path);

		float* fdata = (float*)malloc(width * 4 * height);
		for (int y = 0; y < height; ++y) {
			const ushort* src = sdata + y * width;
			float* dst = fdata + y * width;
			for (int x = 0; x < width; ++x) { *dst++ = *src++ / 65536.0f; }
		}
		stbi_image_free(sdata);
		freeFunc = &free;
		data = fdata;

	} else {

		data = stbi_load(path.c_str(), &width, &height, &n, bpp);
		if (!data) panic("Can't load image " + path);

		freeFunc = &stbi_image_free;
	}

	Image* image = new Image(data, width, height, width * bpp, format);

	image->deleted.connect([path, image, freeFunc] {
		g_imagePaths.erase(image);
		g_imageCache.erase(path);
		freeFunc(image->data);
	});

	g_imagePaths.insert(std::make_pair(image, path));
	g_imageCache.insert(std::make_pair(path, image));

	return image;
}

String imagePath(Image* image) {
	auto it = g_imagePaths.find(image);
	return it != g_imagePaths.end() ? it->second : "";
}

Image* copyImage(Image* image) {

	auto newImage = createImage(image->width, image->height, image->format);

	uint rowSize = image->width * bytesPerPixel(image->format);

	for (uint y = 0; y < image->height; ++y) {
		memcpy(newImage->data + newImage->pitch * y, image->data + image->pitch * y, rowSize);
	}

	return newImage;
}

Image* resizeImage(Image* image, uint width, uint height) {

	uint channels = 0;

	switch (image->format) {
	case PixelFormat::alpha8:
	case PixelFormat::intensity8:
	case PixelFormat::r32f:
		channels = 1;
		break;
	case PixelFormat::intensityAlpha16:
		channels = 2;
		break;
	case PixelFormat::rgb24:
	case PixelFormat::srgb24:
		channels = 3;
		break;
	case PixelFormat::rgba32:
	case PixelFormat::srgba32:
		channels = 4;
		break;
		break;
	case PixelFormat::depth32f:
	case PixelFormat::rgba64f:
		panic("TODO");
	}

	Image* newImage = createImage(width, height, image->format);

	if (image->format == PixelFormat::r32f) {
		stbir_resize_float((float*)image->data, image->width, image->height, image->pitch, (float*)newImage->data,
						   newImage->width, newImage->height, newImage->pitch, channels);
	} else {
		stbir_resize_uint8(image->data, image->width, image->height, image->pitch, newImage->data, newImage->width,
						   newImage->height, newImage->pitch, channels);
	}

	return newImage;
}

} // namespace wb
