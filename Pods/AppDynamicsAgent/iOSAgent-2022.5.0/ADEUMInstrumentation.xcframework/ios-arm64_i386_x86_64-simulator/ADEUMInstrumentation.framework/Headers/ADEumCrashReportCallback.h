//
//  Copyright (c) 2016 AppDynamics Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ADEumCommons.h"

ADEUM_ASSUME_NONNULL_BEGIN

/**
 * Represents the summary of a crash report.
 *
 * You can get one by registering a ADEumCrashReportCallback with
 * [ADEumAgentConfiguration crashReportCallback]
 */
@interface ADEumCrashReportSummary : NSObject

/** Uniquely defines the crash, can be used as key to find full crash report. */
@property (nonatomic, readonly) NSString *crashId;

/** The exception name, may be `nil` if no `NSException` occured. */
@property (nonatomic, readonly) NSString * ADEUM_NULLABLE exceptionName;

/** The exception reason, may be `nil` if no `NSException` occured. */
@property (nonatomic, readonly) NSString * ADEUM_NULLABLE exceptionReason;

/** The Mach exception signal name */
@property (nonatomic, readonly) NSString *signalName;

/** The Mach exception signal code */
@property (nonatomic, readonly) NSString *signalCode;

@end

/**
 * The `ADEumCrashReportCallback` protocol defines the messages sent to an object
 * as part of creating crash reports. All of the methods of this protocol are
 * required.
 */
@protocol ADEumCrashReportCallback <NSObject>

/**
 * Called when a crash report is about to be sent.
 *
 * Typically the summaries will have a size of 1, but if the app is crashing very early
 * during start up, summaries could be larger.
 *
 * @param summaries An array of ADEumCrashReportSummary objects.
 *
 * @warning This method will be scheduled on the *main thread*, so any long
 * operations should be performed asynchronously.
 *
 */
#if !defined(__IPHONE_8_0) || defined(__IPHONE_9_0)
- (void)onCrashesReported:(NSArray <ADEumCrashReportSummary *> *)summaries;
#else
// NOTE: This prototype is required for Swift 1.2/Xcode 6 support
// The logic works because __IPHONE_9_0 was added with Xcode 7.
- (void)onCrashesReported:(NSArray *)summaries;
#endif

@end

ADEUM_ASSUME_NONNULL_END
