#ifndef SECUGEN_PLUGIN_H_
#define SECUGEN_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <sgfplib.h>  // Include SecuGen SDK header

namespace secugen {

class SecugenPlugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar);

  SecugenPlugin();
  ~SecugenPlugin();

 private:
  // Helper functions for SecuGen SDK integration
  static void InitializeSGFPM();
  static void OpenFingerprintDevice();
  static void CaptureFingerprintImage(std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>>& result);

  // Method call handler
  void HandleMethodCall(const flutter::MethodCall<flutter::EncodableValue>& method_call,
                        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

  // SGFPM handle
  static HSGFPM m_hFPM;
};

}  // namespace secugen

#endif  // SECUGEN_PLUGIN_H_
