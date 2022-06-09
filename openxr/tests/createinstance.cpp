
#include <openxr/openxr.h>

#include <core/core.hh>

using namespace wb;

int main() {

    XrInstance instance;
    {
        XrInstanceCreateInfo info{};
        info.type = XR_TYPE_INSTANCE_CREATE_INFO;
        info.next = nullptr;
        info.createFlags = 0;
        strcpy(info.applicationInfo.applicationName, "Testapp");
        info.applicationInfo.applicationVersion = 1;
        strcpy(info.applicationInfo.engineName, "mak3d");
        info.applicationInfo.engineVersion = 1;
        info.applicationInfo.apiVersion = 0x0001000000000000L;
        info.enabledApiLayerCount = 0;
        info.enabledApiLayerNames = nullptr;
        info.enabledExtensionCount = 0;
        info.enabledExtensionNames = nullptr;

        verify(xrCreateInstance(&info, &instance) == 0);
        debug() << "### Successfully created xrInstance!";
    }

    XrSystemId systemId;
    {
        XrSystemGetInfo info{};
        info.type = XR_TYPE_SYSTEM_GET_INFO;
        info.next = nullptr;
        info.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;

        verify(xrGetSystem(instance, &info, &systemId) == 0);
        debug() << "### Successfully created systemId";
    }

    {
        XrSystemProperties props{};
        verify(xrGetSystemProperties(instance, systemId, &props) == 0);
        debug() << "### System properties:" << props.systemName << "width:" << props.graphicsProperties.maxSwapchainImageWidth << "Height:" << props.graphicsProperties.maxSwapchainImageHeight << "Layers" << props.graphicsProperties.maxLayerCount;
    }

    {
        verify(xrDestroyInstance(instance) == 0);
        debug() << "### Successfully destroyed xrInstance!";
    }

    return 0;
}