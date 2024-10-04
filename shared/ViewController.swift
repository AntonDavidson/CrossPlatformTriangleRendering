import UIKit
import MetalKit

class ViewController: UIViewController {

    var metalView: MTKView!

    override func viewDidLoad() {
        super.viewDidLoad()

        // Create and configure MTKView
        guard let device = MTLCreateSystemDefaultDevice() else {
            fatalError("Metal is not supported on this device")
        }

        metalView = MTKView(frame: self.view.bounds, device: device)
        metalView.colorPixelFormat = .bgra8Unorm  // Must match pipeline descriptor
        metalView.clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0)
        self.view.addSubview(metalView)

        // Pass MTKView to C++
        Wrapper.setView(metalView)

        // Initialize Metal
        Wrapper.initializeMetalApp()

        // Start rendering
        Wrapper.renderMetalApp()
    }
}
