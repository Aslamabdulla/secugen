#include "secugen_plugin.h"

#include <windows.h>
#include <sgfplib.h>  // Include SecuGen SDK header

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace secugen {

static HSGFPM m_hFPM = NULL;  // SGFPM handle

// Helper function to check and handle SGFPM errors
void CheckError(DWORD error, const std::string& message) {
    if (error != SGFDX_ERROR_NONE) {
        std::ostringstream err_stream;
        err_stream << message << " Error code: " << error;
        throw std::runtime_error(err_stream.str());
    }
}

void InitializeSGFPM() {
    DWORD err = SGFPM_Create(&m_hFPM);
    CheckError(err, "Failed to create SGFPM instance");

    // Initialize SGFPM device (example using SGFPM_InitEx2)
    DWORD imageWidth = 300;
    DWORD imageHeight = 400;
    DWORD imageDpi = 500;
    char* licensePath = "path/to/license/file";  // Replace with actual path
    err = SGFPM_InitEx2(m_hFPM, imageWidth, imageHeight, imageDpi, licensePath);
    CheckError(err, "Failed to initialize SGFPM device");
}

void OpenFingerprintDevice() {
    DWORD devId = SG_DEV_AUTO;  // Auto-detect device
    DWORD err = SGFPM_OpenDevice(m_hFPM, devId);
    CheckError(err, "Failed to open SGFPM device");
}

void CaptureFingerprintImage(std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>>& result) {
    // Example function to capture fingerprint image
    if (m_hFPM == NULL) {
        result->Error("SGFPM_NotInitialized", "SGFPM not initialized");
        return;
    }

    DWORD err;
    BYTE* buffer = new BYTE[300 * 400];  // Replace with actual image size

    err = SGFPM_GetImage(m_hFPM, buffer);
    if (err != SGFDX_ERROR_NONE) {
        delete[] buffer;
        std::ostringstream err_stream;
        err_stream << "Failed to capture fingerprint image. Error code: " << err;
        result->Error("CaptureError", err_stream.str());
        return;
    }

    // Process captured image here
    // For simplicity, returning base64 encoded image as a string
    std::string base64Image = "base64_encoded_image_data";
    result->Success(flutter::EncodableValue(base64Image));

    delete[] buffer;
}

void SecugenPlugin::RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar) {
    auto channel =
        std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
            registrar->messenger(), "secugen",
            &flutter::StandardMethodCodec::GetInstance());

    auto plugin = std::make_unique<SecugenPlugin>();

    channel->SetMethodCallHandler(
        [plugin_pointer = plugin.get()](const auto& call, auto result) {
            plugin_pointer->HandleMethodCall(call, std::move(result));
        });

    registrar->AddPlugin(std::move(plugin));
}

SecugenPlugin::SecugenPlugin() {
    // Initialize SecuGen SDK when plugin instance is created
    InitializeSGFPM();
}

SecugenPlugin::~SecugenPlugin() {
    // Terminate SGFPM when plugin instance is destroyed
    if (m_hFPM) {
        SGFPM_Terminate(m_hFPM);
        m_hFPM = NULL;
    }
}

void SecugenPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
    
    if (method_call.method_name().compare("initializeSGFPM") == 0) {
        // Initialize SGFPM
        InitializeSGFPM();
        result->Success(flutter::EncodableValue(true));
    } else if (method_call.method_name().compare("openFingerprintDevice") == 0) {
        // Open SGFPM device
        OpenFingerprintDevice();
        result->Success(flutter::EncodableValue(true));
    } else if (method_call.method_name().compare("captureFingerprintImage") == 0) {
        // Capture fingerprint image
        CaptureFingerprintImage(result);
    } else {
        result->NotImplemented();
    }
}

}  // namespace secugen
