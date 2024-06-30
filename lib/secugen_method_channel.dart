import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'secugen_platform_interface.dart';

/// An implementation of [SecugenPlatform] that uses method channels.
class MethodChannelSecugen extends SecugenPlatform {
  /// The method channel used to interact with the native platform.
  final MethodChannel methodChannel = const MethodChannel('secugen');

  @override
  Future<void> initializeSGFPM() async {
    try {
      await methodChannel.invokeMethod<void>('initializeSGFPM');
    } on PlatformException catch (e) {
      throw 'Failed to initialize SGFPM: ${e.message}';
    }
  }

  @override
  Future<void> openFingerprintDevice() async {
    try {
      await methodChannel.invokeMethod<void>('openFingerprintDevice');
    } on PlatformException catch (e) {
      throw 'Failed to open fingerprint device: ${e.message}';
    }
  }

  @override
  Future<void> captureFingerprintImage() async {
    try {
      await methodChannel.invokeMethod<void>('captureFingerprintImage');
    } on PlatformException catch (e) {
      throw 'Failed to capture fingerprint image: ${e.message}';
    }
  }

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
