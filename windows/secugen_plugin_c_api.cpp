#include "include/secugen/secugen_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "secugen_plugin.h"

void SecugenPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  secugen::SecugenPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
