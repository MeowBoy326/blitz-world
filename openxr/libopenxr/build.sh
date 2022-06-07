
CHECKOUT_URL=https://github.com/blitz-research/OpenXR-SDK.git

CHECKOUT_DIR=$PWD/openxr-checkout

BUILD_CONFIG="-DCMAKE_BUILD_TYPE=Release -DDYNAMIC_LOADER=OFF -G Ninja"
#BUILD_CONFIG="-DCMAKE_BUILD_TYPE=Release -DDYNAMIC_LOADER=ON -G Ninja"

BUILD_DIR=$PWD/openxr-build/release

if test ! -d $CHECKOUT_DIR ; then
	echo "Checking out $CHECKOUT_URL to $CHECKOUT_DIR..."
	git clone $CHECKOUT_URL $CHECKOUT_DIR || exit 1
fi
	
cd $CHECKOUT_DIR

if test ! -d $BUILD_DIR ; then
	echo "Generating build dir $BUILD_DIR with ${BUILD_CONFIG}..."
	cmake -S . -B$BUILD_DIR $BUILD_CONFIG || exit 1
fi

echo "Building..."
cmake --build $BUILD_DIR || exit 1
echo "Done."
