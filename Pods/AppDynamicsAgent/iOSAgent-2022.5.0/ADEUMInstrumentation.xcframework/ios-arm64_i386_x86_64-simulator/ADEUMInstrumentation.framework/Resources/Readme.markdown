## About the AppDynamics iOS SDK

The AppDynamics iOS SDK is a framework that allows you to monitor the
performance and activities of an iOS application as it runs.

It will automatically detect and instrument HTTP requests that the
enclosing application sends via `NSURLConnection` or `NSURLSessions`
or any framework that uses these objects.

The SDK also provides a facility to track any application crashes that
occur.

The SDK includes APIs to instrument specific methods in your own code,
to measure durations of operations in your application (like
application start up, for example), or to report an arbitrary metric.

If you have an on-premise deployment, please note that some of the
features described here require a minimum EUM server deployment version.
Please refer to the [Mobile Agent Version and Deployment Support Matrix](https://docs.appdynamics.com/display/latest/Mobile+Agent+Version+and+Deployment+Support+Matrix)
for more information.

## Quick install
There are two ways to include the AppDynamics iOS SDK in your
application.

### CocoaPods
If your project uses [CocoaPods](https://cocoapods.org/) then you can simply add the
following to your `Podfile`:

```
pod 'AppDynamicsAgent'
```

Then run the this command:

```
pod install
```

### Manual Method
Follow these steps:

1. Link your project against `ADEUMInstrumentation.xcframework`. The
   easiest way to do this is to drag the
   `ADEUMInstrumentation.xcframework` bundle into your project's
   Frameworks group in Xcode.

2. Add a call to initialize the SDK in the
   `-[UIApplicationDelegate application:didFinishLaunchingWithOptions:]`
   method. This method will be called when your application starts
   up. It looks something like:

        - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
            [ADEumInstrumentation initWithKey:@"<#YOUR APP KEY HERE#>"];
            // other tasks
            return YES;
        }
If you don't know your app key, see the [documentation][docs].

3. Link your project against the following libraries:
   - SystemConfiguration.framework
   - CoreTelephony.framework
   - libz.dylib

4. Add `-ObjC` to the `Other Linker Flags` in your Build Settings.

## Instrumenting methods
While the AppDynamics iOS SDK instruments some system method
automatically, you can also use it to instrument methods in your own
code. When you do this, you'll be able to see how often the
instrumented method is invoked, and how long it takes to run. To do
this, add a call at the beginning and end of the method you'd like to
instrument:

```
- (void)startTimerWithName {
    id tracker = [ADEumInstrumentation beginCall:self selector:_cmd];

    // Implementation of method here ...

    [ADEumInstrumentation endCall:tracker];
}
```

## Timing events
Sometimes you want to time an event in your application that spans
multiple methods. You can do this by calling the SDK when the event
starts, and then again when it ends. For example, to track the time a
user spends viewing a screen, the instrumentation looks like:

```
- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [ADEumInstrumentation startTimerWithName:@"View Lifetime"];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    [ADEumInstrumentation stopTimerWithName:@"View Lifetime"];
}
```

## Reporting metrics
If you'd like to report some other type of data, you can use a
metric. The only requirement is that the metric value must be an
integer. Reporting a metric looks like this:

```
[ADEumInstrumentation reportMetricWithName:@"My custom metric" value:<#VALUE HERE#>];
```

## Reporting custom HTTP requests
While the SDK can automatically discover HTTP requests made through
the Objective-C system libraries, you might be using some other HTTP
library that the SDK doesn't automatically instrument. In that case,
you can explicitly report your HTTP requests.

Suppose you have a method like this for making HTTP requests:

```
- (NSData *)sendRequest:(NSURL *)url error:(NSError **)error {
    // implementation omitted

    NSData *result = nil;
    if (errorOccurred) {
        *error = theError;
    } else {
        result = responseBody;
    }
    return result;
}
```

Here's how you would augment this method to report requests to the SDK:

```
- (NSData *)sendRequest:(NSURL *)url error:(NSError **)error {
    ADEumHTTPRequestTracker *tracker = [ADEumHTTPRequestTracker requestTrackerWithURL:url];
    // implementation omitted

    NSData *result = nil;
    if (errorOccurred) {
        *error = theError;
        tracker.error = theError;
    } else {
        tracker.statusCode = theStatusCode;
        tracker.allHeaderFields = theResponseHeaders;
        result = responseBody;
    }
    [tracker reportDone];
    return result;
}
```

## Automatic Instrumentation Notes
Automatic instrumentation is achieved by using:

1. Wrapper objects that are subclassed from `NSProxy`.
1. The use of ObjectiveC Categories to extend classes of interest.
1. Method "swizzling" that interpose methods of interest.

All mechanisms used are well documented, safe and "stackable" when
used correctly. In the interest of full disclosure, here is a list of
objects and methods that we swizzle:

1. `NSURLConnection`:
   1. `-initWithRequest:delegate:`
   1. `-initWithRequest:delegate:startImmediately:`
   1. `-start`
   1. `+sendSynchronousRequest:returningResponse:error:`
   1. `+connectionWithRequest:delegate:`
   1. `+sendAsynchronousRequest:queue:completionHandler:`
1. `NSURLSession`:
   1. `+sharedSession`
   1. `+sessionWithConfiguration:`
   1. `+sessionWithConfiguration:delegate:delegateQueue:`
1. `NSURLRequest`:
   1. `-initWithURL:cachePolicy:timeoutInterval:`
   1. `-mutableCopyWithZone:`
1. `UIApplication`:
   1. `-setDelegate:`
   1. `-sendAction:to:from:forEvent:`
   1. `-sendEvent`
1. `UIApplicationDelegate`:
   1. `applicationWillResignActive:`
   1. `applicationDidBecomeActive:`
   1. `applicationWillEnterForeground:`
   1. `applicationDidEnterBackground`
1. `UIViewController`:
   1. `-viewDidAppear:`
   1. `-viewWillDisappear:`
   1. `-loadView`
1. `WKWebView`:
   1. `-initWithFrame:configuration:`
   1. `-initWithCoder:`

## Further Documentation

For a more detailed description of how to use SDK, or for
troubleshooting information, please see the
[official documentation][docs]

[docs]: http://docs.appdynamics.com/ "AppDynamics Documentation"
