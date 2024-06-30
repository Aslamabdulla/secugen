import 'secugen_platform_interface.dart';

class Secugen {
  Future<String?> getPlatformVersion() {
    return SecugenPlatform.instance.getPlatformVersion();
  }

  Future<void> initializeSGFPM() {
    return SecugenPlatform.instance.initializeSGFPM();
  }

  Future<void> openFingerprintDevice() {
    return SecugenPlatform.instance.openFingerprintDevice();
  }

  Future<void> captureFingerprintImage() {
    return SecugenPlatform.instance.captureFingerprintImage();
  }
}
