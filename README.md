
WebRTC Plugin for Cordova
=================================

### NOTE: This project is not production ready.
This project aims to implement the full WebRTC API on Cordova.
As a mid-term goal, we aim to support all WebRTC sample from [here](https://github.com/webrtc/samples), as well as the AppRTCDemo TODO LINK.

- shim implementations:
	- WebRTC
		- RTCPeerConnection
		- RTCICECandidate
		- RTCSessionDescription
		- RTCDataChannel
	- getUserMedia (not really part of WebRTC, but needed to get handles for input media)
		- MediaStream (same as above)
		- MediaTrack

#### WebRTC samples working state
Note, the samples were only modified for its scripts only execute after cordova's *deviceReady* event is triggered.

- getUserMedia
	- Basic getUserMedia demo
- RTCPeerConnection
	- Audio-only peer connection
- RTCDataChannel
	- Transmit text

### Implementation details
To make this implementation work *almost* seamless with the WebRTC standard, we use some quirks that allow us to overlay the native WebRTC video views on the 

- Use MutationObserver to listen for changing <video> tags
- Fake blob with stream id

### Quirks

- You need to setAttribute
- Use pc.dispose() to clear up

### Current Limitations
- Canvas operations not supported over the WebRTC video elements.
- getUserMedia only returns front camera.
- getUserMedia overrides native implementation (if exists). Do not use it for anything else.
- Audio tracks will be enabled even if the video tag is not in the DOM.
- No MediaStream callbacks
- Cannot detect javascript object gc, thus cannot automatically free native WebRTC objects (use obj.dispose() for that).

### Migration
Dont forget for deviceReady before using WebRTC API
<webrtc-video> not to show the play thingy

## Supported Platforms
- __iOS6+__
- __Android 4.0+__ coming soon

## Installation
The plugin is not yet available on the Cordova Plugin Registry.
To install latest version, run the following on your cordova project:

```shell
#latest version
cordova plugin add git@github.com:remotium/cordova-plugin-webrtc.git
#specific branch
cordova plugin add git@github.com:remotium/cordova-plugin-webrtc.git@branch
```

## How to build
We use gulp to 

## Contributing

We use the github issue tracker and pull request frameworks to accept contributions.

### To do list
- All kinds of tests
- Support for other platforms
- Better object cleanup
- ...

## License

This software is released under the Apache 2.0 License.

© 2015 Remotium, Inc. All rights reserved