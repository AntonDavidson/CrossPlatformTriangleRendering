# CrossPlatformTriangleRendering

Your code sets up a cross-platform rendering pipeline using OpenGL for Android and Metal for iOS. It includes utility functions for shader management, buffer setup, and rendering logic. The OpenGL code handles vertex buffer and shader setup for drawing a triangle, while the Metal code initializes GPU resources and renders a triangle using Metal's pipeline state, command queue, and buffer management. The project is structured with conditional compilation to ensure the appropriate platform-specific rendering logic is executed on each platform.

# Android
#### To launch the project on adroid open in android studio.
# Android Example
<img src="https://raw.githubusercontent.com/AntonDavidson/CrossPlatformTriangleRendering/refs/heads/main/android_triangle.gif" alt="Description of GIF" width="300" height="500">

# iOS
### To launch the project on iOS, follow these steps:

Copy Shared Files: Copy the contents of the shared folder into the main project directory within your Xcode project. This ensures all necessary cross-platform files are included.

Replace ViewController.swift: Replace the existing ViewController.swift file with the provided one, which includes the necessary setup and rendering logic.

Configure Header Search Paths:

In Xcode, go to Project Settings > Build Settings.
Add the path to the metal-cpp folder in the Header Search Paths to ensure all Metal headers are found.
Add Required Frameworks:

Navigate to Build Phases > Link Binary With Libraries.
Add the following frameworks:
Metal
Foundation
MetalKit
QuartzCore
Build and Run:

After configuring the settings, build the project in Xcode.
Run the project on an iOS device or simulator to launch the app with full Metal rendering support.

# iOS Example
<img src="https://raw.githubusercontent.com/AntonDavidson/CrossPlatformTriangleRendering/refs/heads/main/ios_triangle.gif" alt="Description of GIF" width="300" height="500">
