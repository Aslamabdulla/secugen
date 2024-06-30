import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'secugen_method_channel.dart';

abstract class SecugenPlatform extends PlatformInterface {
  /// Constructs a SecugenPlatform.
  SecugenPlatform() : super(token: _token);

  static final Object _token = Object();

  static SecugenPlatform _instance = MethodChannelSecugen();

  /// The default instance of [SecugenPlatform] to use.
  ///
  /// Defaults to [MethodChannelSecugen].
  static SecugenPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [SecugenPlatform] when
  /// they register themselves.
  static set instance(SecugenPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  /// Retrieves the platform version from the native side.
  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }

  /// Initializes the SGFPM SDK on the native platform.
  Future<void> initializeSGFPM() {
    throw UnimplementedError('initializeSGFPM() has not been implemented.');
  }

  /// Opens a SecuGen fingerprint device.
  Future<void> openFingerprintDevice() {
    throw UnimplementedError('openFingerprintDevice() has not been implemented.');
  }

  /// Captures a fingerprint image using the SecuGen SDK.
  Future<void> captureFingerprintImage() {
    throw UnimplementedError('captureFingerprintImage() has not been implemented.');
  }
}
