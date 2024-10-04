// Wrapper.mm
#import "Wrapper.h"
#import "main_lib.h"  // Include the C++ functions
#import <MetalKit/MetalKit.h>  // Use Objective-C MetalKit

@implementation Wrapper

+ (void)setView:(MTKView* )view {
    setMTKView((__bridge void *)(view));  // Pass the MTKView as a void* to C++
}

+ (void)initializeMetalApp {
    initMetalApp();
}

+ (void)renderMetalApp {
    renderMetalApp();
}

@end
