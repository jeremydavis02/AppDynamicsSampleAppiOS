//  Copyright (c) 2015 AppDynamics Technologies. All rights reserved.

#import <Foundation/Foundation.h>
#import "ADEumCommons.h"

ADEUM_ASSUME_NONNULL_BEGIN

/**
 * If you are using ADEumHTTPRequestTracker to report custom HTTP requests, you can use
 * this class to correlate those requests with business transactions.
 *
 * To do so, call the generate method on this class to retrieve a list of headers, and
 * set those header values on each outgoing HTTP request. Also, ensure that you are
 * passing all response headers to ADEumHTTPRequestTracker.
 */
@interface ADEumServerCorrelationHeaders : NSObject

/**
 * Generate HTTP headers that should be set on outgoing requests.
 */
+ (NSDictionary *)generate;

@end

ADEUM_ASSUME_NONNULL_END
