#pragma once

#include "image.h"

namespace wb {

Image* createImage(uint width, uint height, PixelFormat format);
Image* loadImage(CString path, PixelFormat format);
String imagePath(Image* image);

Image* copyImage(Image* image);
Image* resizeImage(Image* image, uint width, uint height);

} // namespace wb
