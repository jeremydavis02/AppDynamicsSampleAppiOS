//  Copyright (c) 2015 AppDynamics Technologies. All rights reserved.

#import <Foundation/Foundation.h>
#import "ADEumCommons.h"

ADEUM_ASSUME_NONNULL_BEGIN

/**
 * If the SDK does not automatically discover your HTTP requests, use this class to explicitly
 * report them. Note that most users will not need to use this class; check the documentation
 * for the list of HTTP APIs that are automatically discovered.
 */
@interface ADEumHTTPRequestTracker : NSObject

/**
 * Begins tracking an HTTP request.
 *
 * Call this immediately before sending an HTTP request to track it manually.
 *
 * @param url The URL being requested.
 *
 * @warning `url` must not be `nil`.
 * @warning One of ADEumInstrumentation's initWithKey: methods must be called before this method.
 */
+ (ADEumHTTPRequestTracker *)requestTrackerWithURL:(NSURL *)url;

/**
 * Stops tracking an HTTP request.
 *
 * Immediately after receiving a response or an error, set the appropriate properties and call this method
 * to report the outcome of the HTTP request. You should not continue to use this object after calling
 * this method -- if you need to track another request, call requestTrackerWithURL:.
 */
- (void)reportDone;

/**
 * Sets the value of the specified key to the specified string value.
 *
 * ### Notes
 *
 * - All UserData interfaces are type specific and maintain a separate
 *   `key` name space. This means that both
 *   +setUserDataBoolean:value: and
 *   +setUserDataLong:value: can use a `key` of `@"foo"`.
 *
 * - UserData can be used to relay any information available to the
 *   programmer.
 *
 * - Unlike the global UserData methods, data attached to an HTTPRequestTracker
 *   are only reported for this particular network call.
 *
 * @param key The key with which to associate with the value.
 * @param value The non-nil NSString value to store.
 *
 * @warning Both the key and the value will if be truncated if they are longer than 2048 characters.
 */
- (void)setUserData:(NSString * ADEUM_NULLABLE)key value:(NSString *)value;

/**
 * Sets the value of the specified key to the specified signed 64-bit integer value.
 *
 * @param key The key with which to associate with the value.
 * @param value Signed 64-bit integer value to store.
 */
- (void)setUserDataLong:(NSString * ADEUM_NULLABLE)key value:(int64_t)value;

/**
 * Sets the value of the specified key to the specified Boolean value.
 *
 * @param key The key with which to associate with the value.
 * @param value The boolean value to store.
 */
- (void)setUserDataBoolean:(NSString * ADEUM_NULLABLE)key value:(BOOL)value;

/**
 * Sets the value of the specified key to the specified double value.
 *
 * @param key The key with which to associate with the value.
 * @param value The double value to store.
 *              The value has to be a finite real number.
 *              The use of `NAN`, `+INF` or `-INF` may lead to undefined behavior.
 */
- (void)setUserDataDouble:(NSString * ADEUM_NULLABLE)key value:(double)value;

/**
 * Sets the value of the specified key to the specified NSDate object.
 *
 * ### Note
 *
 * The Date value will be stored as a signed 64-bit integer representing
 * milliseconds since 1970 (epoch time) UTC.
 *
 * @param key The key with which to associate with the value.
 * @param value The non-nil NSDate object to store.
 */
- (void)setUserDataDate:(NSString * ADEUM_NULLABLE)key
                  value:(NSDate *)value;

/**
 * The URL for the network request
 *
 */
@property (copy, nonatomic) NSURL *url;

/**
 * An error describing the failure to receive a response, if one occurred.
 *
 * If the request was successful, this should be `nil`.
 */
@property (copy, nonatomic) NSError * ADEUM_NULLABLE error;

/**
 * The status code of response, if one was received.
 *
 * If a response was received, this should be an an integer. If an error occurred and a
 * response was not received, this should be `nil`.
 */
@property (copy, nonatomic) NSNumber * ADEUM_NULLABLE statusCode;

/**
 * A dictionary representing the keys and values from the server’s response header.
 *
 * If an error occurred and a response was not received, this should be `nil`.
 */
@property (copy, nonatomic) NSDictionary * ADEUM_NULLABLE allHeaderFields;

/**
 * A dictionary representing the keys and values from the client's request header.
 */
@property (copy, nonatomic) NSDictionary * ADEUM_NULLABLE allRequestHeaderFields;

/**
 * A string to identify the source of the instrumentation that generated this tracker.
 *
 * The default is "Manual HttpTracker".
 *
 * You should not have to modify this.
 */
@property (copy, nonatomic) NSString * ADEUM_NULLABLE instrumentationSource;

@end

ADEUM_ASSUME_NONNULL_END
