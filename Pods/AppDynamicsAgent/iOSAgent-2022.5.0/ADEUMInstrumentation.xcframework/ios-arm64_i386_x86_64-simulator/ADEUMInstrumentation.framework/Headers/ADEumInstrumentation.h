// Copyright (c) 2022 AppDynamics Technologies. All rights reserved.

#import <UIKit/UIKit.h>

// Since the case of this file name does not match the case
// of the framework itself (ADEum... vs ADEUM...) we need to
// have a modulemap file, which we happen to have named
// adeuminstrumentation.modulemap, which tells the compiler
// the correct name of this header. Also the path to that
// modulemap file needs to be specified in the
// ADEUMInstrumentation library target settings. If you
// change the case of this header file name to match the
// case of the framework name (which might cause othe
// issues) you will need to also remove the .modulemap
// file we have and clear its path out of the target
// settings.

//! Project version number for ADEUMInstrumentation.
FOUNDATION_EXPORT double ADEUMInstrumentationVersionNumber;

//! Project version string for ADEUMInstrumentation.
FOUNDATION_EXPORT const unsigned char ADEUMInstrumentationVersionString[];

#import <ADEUMInstrumentation/ADEumInstrumentation_interfaces.h>
#import <ADEUMInstrumentation/ADEumCollectorChannel.h>
#import <ADEUMInstrumentation/ADEumHTTPRequestTracker.h>
#import <ADEUMInstrumentation/ADEumServerCorrelationHeaders.h>
