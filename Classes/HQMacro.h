//
//  HQMacro.h
//  HQMacroDemo
//
//  Created by 刘欢庆 on 2017/4/24.
//  Copyright © 2017年 刘欢庆. All rights reserved.
//

#ifndef HQMacro_h
#define HQMacro_h

/** Nib加载 */
#define kNib(name) [UINib nibWithNibName:name bundle:nil]

/** keyWindow */
#define kWindow [UIApplication sharedApplication].keyWindow

/** Log */
#if DEBUG
#define HQLogError(frmt, ...) NSLog(@"❌[%@:%@ %d]  %@ \n", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent],   \
NSStringFromSelector(_cmd), \
__LINE__,   \
[NSString stringWithFormat:(frmt), ##__VA_ARGS__])

#define HQLogInfo(frmt, ...) NSLog(@"✅[%@:%@ %d]  %@ \n", \
[[NSString stringWithUTF8String:__FILE__] lastPathComponent],   \
NSStringFromSelector(_cmd), \
__LINE__,   \
[NSString stringWithFormat:(frmt), ##__VA_ARGS__])
#else
#define HQLogError(frmt, ...)
#define HQLogInfo(frmt, ...)
#endif

/** 16进制 颜色转换 */
#define COLOR_WITH_HEX(HEX) [UIColor colorWithRed:((HEX & 0xFF0000) >> 16)/255.0 green:((HEX & 0xFF00) >> 8)/255.0 blue:(HEX & 0xFF)/255.0 alpha:1]
#define COLOR_WITH_HEX_ALPHA(HEX,ALPHA) [UIColor colorWithRed:((HEX & 0xFF0000) >> 16)/255.0 green:((HEX & 0xFF00) >> 8)/255.0 blue:(HEX & 0xFF)/255.0 alpha:ALPHA]

/** weakify strongify */
#ifndef hq_weak
#if DEBUG
#if __has_feature(objc_arc)
#define hq_weak(object) __weak __typeof(object) weak##_##object = object;
#else
#define hq_weak(object) __block __typeof(object) weak##_##object = object;
#endif
#else
#if __has_feature(objc_arc)
#define hq_weak(object) __weak __typeof(object) weak##_##object = object;
#else
#define hq_weak(object) __block __typeof(object) weak##_##object = object;
#endif
#endif
#endif

#ifndef hq_strong
#if DEBUG
#if __has_feature(objc_arc)
#define hq_strong(object) __typeof(object) object = weak##_##object;
#else
#define hq_strong(object) __typeof(object) object = block##_##object;
#endif
#else
#if __has_feature(objc_arc)
#define hq_strong(object) __typeof(object) object = weak##_##object;
#else
#define hq_strong(object) __typeof(object) object = block##_##object;
#endif
#endif
#endif


/** 屏幕类型 */
#define IPHONE4  (SCREEN_HEIGHT == (480))
#define IPHONE6P (SCREEN_HEIGHT == (736))
#define IPHONEX  (SCREEN_HEIGHT == (812))

/** 屏幕尺寸 */
#define SCREEN_STATUS (IPHONEX?44.0f:20.0f)
#define SCREEN_TABBAR (IPHONEX?83.0f:49.0f)

#define SCREEN_TOP (SCREEN_STATUS+44.0f)
#define SCREEN_WIDTH [UIScreen mainScreen].bounds.size.width
#define SCREEN_HEIGHT [UIScreen mainScreen].bounds.size.height

/** GCD的同步封装 */
#define ASYNC_START  dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
#define ASYNC_DONE   dispatch_async(dispatch_get_main_queue(), ^{
#define ASYNC_END   }); });

/** 固件版本 */
#define IsIOS7 ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0)
#define IsIOS8 ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
#define IsIOS9 ([[[UIDevice currentDevice] systemVersion] floatValue] >= 9.0)
#define IsIOS10 ([[[UIDevice currentDevice] systemVersion] floatValue] >= 10.0)

#define hq_main_async_safe(block)\
    if ([NSThread isMainThread]) {\
        block();\
    } else {\
        dispatch_async(dispatch_get_main_queue(), block);\
    }


#define HQDesignBaseWidth  414.0
#define HQDesignBaseHeight 736.0

#define HQScreenWidthRatio  (SCREEN_WIDTH / HQDesignBaseWidth)
#define HQScreenHeightRatio  (SCREEN_HEIGHT / HQDesignBaseHeight)

#define HQRectMake(x, y, width, height) CGRectMake(x * HQScreenWidthRatio, y * HQScreenHeightRatio, width * HQScreenWidthRatio, height * HQScreenHeightRatio)

#define HQSizeMake(width, height) CGSizeMake(width * HQScreenWidthRatio, height * HQScreenHeightRatio)
#endif /* HQMacro_h */
