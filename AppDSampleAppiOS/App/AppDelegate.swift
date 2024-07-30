//
//  AppDelegate.swift
//  AppDSampleAppiOS

import UIKit
import ADEUMInstrumentation
import CoreLocation

/**
  AppDynamics iOS Sample App

  Quick Start

  The best way to find a sample code snippet for each
  usage scenario is to:
 
  1) Build the app in Xcode, running it on the iOS Simulator
  2) Find the scenario of interest in the app UI
  3) Click the "Code" button in the app UI to see an example
     of how to instrument the scenario.
  4) Use the app to exercise the scenario, in order to see
     live instrumentation logging in the Xcode Console, and
     to help understand the results seen in your Controller.
 
  Please read the README.md file for more information!
 
**/

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, CLLocationManagerDelegate {

    let locationManager = CLLocationManager() // Create a location manager
    
    func locationManagerDidChangeAuthorization(_ manager: CLLocationManager) {
                switch manager.authorizationStatus {
                case .authorizedWhenInUse, .authorizedAlways:
                    // Start updating location
                    locationManager.startUpdatingLocation()
                case .denied, .restricted:
                    // Handle the case where location services are not authorized
                    print("Location services not authorized.")
                default:
                    break
                }
            }
        
        // CLLocationManagerDelegate function to handle location updates
        func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
            if let location = locations.last {
                let latitude = location.coordinate.latitude
                let longitude = location.coordinate.longitude
                ADEumInstrumentation.setUserDataDouble("Latitude", value: latitude)
                ADEumInstrumentation.setUserDataDouble("Longitude", value: longitude)
            } else {
                let no_location_error = NSError(domain: "", code: 100, userInfo: [NSLocalizedDescriptionKey: "No location available yet"])
                ADEumInstrumentation.reportError(no_location_error, withSeverity: .info)
            }
        }
        
        func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
            ADEumInstrumentation.reportError(error, withSeverity: .warning)
        }
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        
        printLog("Lifecycle event: didFinishLaunchingWithOptions")
        
        // Note: To find the directory where you can inspect
        // live instrumentation data in JSON format prior to
        // it being sent to the network and flushed, search in
        // the Xcode console window log output for the string
        // "Path to beacons on disk:"

        // Example: App Start
        //
        // (Must also include "import ADEUMInstrumentation"
        // above.) There is a simple option, or an advanced
        // option. You should choose one of the two. For
        // this example app, the simple option is commented
        // out just below, but you could change that.
        
        // Option 1: Simple option, no configuration object

        // Change this to the App Key provided for your account.
        // ADEumInstrumentation.initWithKey("ABC-DEF-GHI")

        // Option 2: Advanced option, showing configuration

        // Change this to the App Key provided for your account.
        let config = ADEumAgentConfiguration(appKey: "AD-AAB-ADF-UWF")

        // Configure the iOS Agent to report the metrics and screenshots

        // to the SaaS EUM Server in Americas
        config.collectorURL = "https://col.eum-appdynamics.com "
        config.screenshotURL = "https://image.eum-appdynamics.com "
        config.interactionCaptureMode = ADEumInteractionCaptureMode.ADEumInteractionCaptureModeAll
        ADEumInstrumentation.initWith(config)
        ADEumInstrumentation.setUserData("Awesome Architect", value: "Jeremy")
        ADEumInstrumentation.setUserDataBoolean("isAwesome", value: true)
        ADEumInstrumentation.setUserDataLong("Ranking", value: 1)
        ADEumInstrumentation.setUserDataDouble("Satisfaction Level", value: 100.00)
        ADEumInstrumentation.setUserDataDate("Date of Awesome", value: Date())
        // Request location authorization
        locationManager.requestWhenInUseAuthorization()
        
        // Set up location manager
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBest
        locationManager.requestWhenInUseAuthorization() // Request location permission
        locationManager.startUpdatingLocation()
        // Check if we have a location available
        if let location = locationManager.location {
            let latitude = location.coordinate.latitude
            let longitude = location.coordinate.longitude
            ADEumInstrumentation.setUserDataDouble("Latitude", value: latitude)
            ADEumInstrumentation.setUserDataDouble("Longitude", value: longitude)
        } else {
            let no_location_error = NSError(domain: "", code: 100, userInfo: [NSLocalizedDescriptionKey: "No location available yet"])
            ADEumInstrumentation.reportError(no_location_error, withSeverity: .info)
        }

        // end example

        // Example: Excluded URL patterns
        //
        // If needed, you can prevent instrumentation of
        // selected URLs. To do this, you would set the
        // value of the 'excludedUrlPatterns' property on
        // the ADEumAgentConfiguration instance at agent
        // initialization time, to hold a set of excluded
        // regular expression patterns that you specify.
        // Note that substrings are also matched, so the
        // pattern does not need to cover the entire URL
        // syntax from front to back:
        //
        // ... instantiate ADEumAgentConfiguration 'config'
        //     object (see App Start sample code) ...
        // let pattern1 = "privatehost1"
        // let pattern2 = "privatehost2"
        // let patternsToExclude = Set([pattern1, pattern2])
        // config.excludedUrlPatterns = patternsToExclude
        // ADEumInstrumentation.initWith(config)

        // end example

        return true
    }

    // MARK: UISceneSession Lifecycle

    func application(_ application: UIApplication, configurationForConnecting connectingSceneSession: UISceneSession, options: UIScene.ConnectionOptions) -> UISceneConfiguration {
        // Called when a new scene session is being created.
        // Use this method to select a configuration to create the new scene with.
        return UISceneConfiguration(name: "Default Configuration", sessionRole: connectingSceneSession.role)
    }

    func application(_ application: UIApplication, didDiscardSceneSessions sceneSessions: Set<UISceneSession>) {
        // Called when the user discards a scene session.
        // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
        // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
    }
    
    // Example: Periodic screenshots
    
    /*
     Periodic screenshots come automatically built in when you
     instrument an app with AppDynamics. Therefore, you don't
     have to add any code to get this feature!
     
     However, there is code you can use to control some
     aspects.
     
     For example, if you want to disable the feature
     completely, you can do so at initialization time by
     setting the screenshotsEnabled flag to false in your
     application(didFinishLaunchingWithOptions:) function:
     
     let config = ADEumAgentConfiguration(appKey: "ABC-DEF-GHI")
     config.screenshotsEnabled = false
     ... other configuration settings ...
     ADEumInstrumentation.initWith(config)

     Alternatively, if you have left the feature enabled,
     you can disable the feature temporarily as needed.
     
     For example, you might want to disable periodic
     screenshots when you know that your app may be about
     to display sensitive data.
     
     To temporarily block periodic screenshots, call the
     blockScreenshots() function. This can later be
     undone by calling unblockScreenshots():
     
     import ADEUMInstrumentation
     ...
     ADEumInstrumentation.blockScreenshots()
     // show sensitive data
     ...
     // sensitive data no longer shown
     ADEumInstrumentation.unblockScreenshots()
     
     */
    // end example


    func applicationWillResignActive(_ application: UIApplication) {
        printLog("App lifecycle event: applicationWillResignActive")
    }
    
    func applicationDidEnterBackground(_ application: UIApplication) {
        printLog("App lifecycle event: applicationDidEnterBackground")
    }

    func applicationWillTerminate(_ application: UIApplication) {
        printLog("App lifecycle event: applicationWillTerminate")
    }


}

