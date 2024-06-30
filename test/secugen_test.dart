// import 'package:flutter_test/flutter_test.dart';
// import 'package:secugen/secugen.dart';
// import 'package:secugen/secugen_platform_interface.dart';
// import 'package:secugen/secugen_method_channel.dart';
// import 'package:plugin_platform_interface/plugin_platform_interface.dart';

// class MockSecugenPlatform
//     with MockPlatformInterfaceMixin
//     implements SecugenPlatform {

//   @override
//   Future<String?> getPlatformVersion() => Future.value('42');
// }

// void main() {
//   final SecugenPlatform initialPlatform = SecugenPlatform.instance;

//   test('$MethodChannelSecugen is the default instance', () {
//     expect(initialPlatform, isInstanceOf<MethodChannelSecugen>());
//   });

//   test('getPlatformVersion', () async {
//     Secugen secugenPlugin = Secugen();
//     MockSecugenPlatform fakePlatform = MockSecugenPlatform();
//     SecugenPlatform.instance = fakePlatform;

//     expect(await secugenPlugin.getPlatformVersion(), '42');
//   });
// }
