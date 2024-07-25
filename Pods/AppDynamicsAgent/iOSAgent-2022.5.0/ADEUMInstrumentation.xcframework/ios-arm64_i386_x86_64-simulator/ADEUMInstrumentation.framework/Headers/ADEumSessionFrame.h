//  Copyright © 2017 AppDynamics Technologies. All rights reserved.

#import <Foundation/Foundation.h>
#import "ADEumCommons.h"

ADEUM_ASSUME_NONNULL_BEGIN

/**
 * The Session Frame API allows you to create time-based named periods
 * of execution.  These Session Frames will appear in the UI.
 */
@interface ADEumSessionFrame : NSObject

/**
 * Updates the name of an existing Session Frame
 *
 * This is generally used when the best name for the Session Frame is not
 * known at the time of its creation.
 *
 * @param name This is the new name for the Session Frame that will appear in UI.
 *
 */
- (void)updateName:(NSString *)name;

/**
 * Ends an existing Session Frame
 *
 * This is called to indicate the end of this particular Session Frame.
 * The object cannot be used again once ended.
 *
 */
- (void)end;

@end

ADEUM_ASSUME_NONNULL_END

