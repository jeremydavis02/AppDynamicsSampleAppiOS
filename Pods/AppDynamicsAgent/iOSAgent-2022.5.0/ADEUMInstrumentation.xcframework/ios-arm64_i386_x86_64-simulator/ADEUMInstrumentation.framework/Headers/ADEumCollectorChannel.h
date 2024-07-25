//  Copyright (c) 2014 AppDynamics Technologies. All rights reserved.

#import <Foundation/Foundation.h>
#import "ADEumCommons.h"

ADEUM_ASSUME_NONNULL_BEGIN
/**
 * Protocol for customizing the connection between the agent SDK and the collector.
 */
@protocol ADEumCollectorChannel <NSObject>

/**
 * Sends a request synchronously and returns the response recieved, or an error.
 *
 * The semantics of this method are exactly equivalient to NSURLConnection's
 * sendSynchronousRequest:returningResponse:error: method.
 *
 * @param request The URL request to load.
 * @param response Out parameter for the URL response returned by the server.
 * @param error Out parameter used if an error occurs while processing the request. May be NULL.
 */
- (NSData * ADEUM_NULLABLE)sendSynchronousRequest:(NSURLRequest *)request
                                returningResponse:(NSURLResponse * ADEUM_NULLABLE * ADEUM_NULLABLE)response
                                            error:(NSError **)error;

@end

ADEUM_ASSUME_NONNULL_END
