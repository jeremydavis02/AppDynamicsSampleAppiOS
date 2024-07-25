//
//  Copyright (c) 2017 AppDynamics Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ADEumCommons.h"
#import "ADEumHTTPRequestTracker.h"

ADEUM_ASSUME_NONNULL_BEGIN

/**
 * The `ADEumNetworkRequestCallback` protocol defines the messages
 * sent to an object as part of creating network request beacons.  All methods
 * of this protocol are required.
 */
@protocol ADEumNetworkRequestCallback <NSObject>

/**
 * Called when a network request is intercepted by the agent.
 *
 * The request in question will be sent through this interface so that
 * it can be modified, in your code, prior to it being recorded as a beacon.
 *
 * Return `YES` to have the beacon, modified or not, recorded.  Return `NO` to
 * stop the beacon from being recorded for this occurance.
 *
 * Currently, only the URL property can be modified, in the future other 
 * properties will/may be added.  Calling the `-reportDone` on this object
 * will have no effect.
 *
 * @param networkRequest An ADEumHTTPRequestTracker object containing 
 * the request in question
 *
 * @warning This method will be performed synchronously so the operation
 * should return quickly.
 */
- (BOOL)networkRequestCallback:(ADEumHTTPRequestTracker *)networkRequest;

@end

ADEUM_ASSUME_NONNULL_END
