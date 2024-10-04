#import <Foundation/Foundation.h>
#import <MetalKit/MetalKit.h>


@interface Wrapper : NSObject
+ (void)setView:(MTKView *)view;
+ (void)initializeMetalApp;
+ (void)renderMetalApp;

@end
