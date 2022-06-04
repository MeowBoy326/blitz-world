
CHECKOUT_URL=https://github.com/blitz-research/glfw.git

CHECKOUT_DIR=$PWD/glfw-checkout

BUILD_TARGET=all
BUILD_CONFIG="-DCMAKE_BUILD_TYPE=Release -DGLFW_BUILD_EXAMPLES=1 -DGLFW_BUILD_TESTS=0 \
-DGLFW_BUILD_DOCS=0 -DGLFW_INSTALL=0 -G Ninja"

BUILD_DIR=$PWD/glfw-build/release

if test ! -d $CHECKOUT_DIR ; then
	echo "Checking out $CHECKOUT_URL to $CHECKOUT_DIR..."
	git clone $CHECKOUT_URL $CHECKOUT_DIR || exit 1
fi
	
cd $CHECKOUT_DIR

if test ! -d $BUILD_DIR ; then
	echo "Generating build dir $BUILD_DIR with ${BUILD_CONFIG}..."
	cmake -S . -B$BUILD_DIR $BUILD_CONFIG || exit 1
fi

echo "Building $BUILD_TARGET..."
cmake --build $BUILD_DIR --target $BUILD_TARGET || exit 1
echo "Done."
