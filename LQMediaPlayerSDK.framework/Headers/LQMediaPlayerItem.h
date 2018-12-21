//
//  LQMediaPlayerItem.h
//  LQMediaPlayer
//
//  Created by suzhou on 2018/8/13.
//  Copyright © 2018年 sina. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    LQ_UNKNOWN_PLAYER = 0,
    LQ_HARDWARE_PLAYER = 2,
    LQ_SYSTEM_PLAYER = 4,   //invalid
    LQ_SOFTWARE_PLAYER = 8
}LQMediaPlayerType;

@interface LQMediaPlayerItem : NSObject

@property (nonatomic, copy) NSString *  path; //视频地址
@property (nonatomic, copy) NSString *  vid; //视频vid
@property (nonatomic, copy) NSString *  site; //视频site，极路由相关
@property (nonatomic, assign) NSInteger startPos; //开始播放位置
@property (nonatomic, assign) NSInteger defType; //视频清晰度
@property (nonatomic, assign) LQMediaPlayerType playerType __attribute__((deprecated("V1.1.23及之后版本废弃，不再生效"))); //解码器类型
@property (nonatomic, assign) NSInteger serviceType;
@property (nonatomic, assign) BOOL      isCaptionVideo;
@property (nonatomic, copy) NSString *  otherIdInfo;
@property (nonatomic, copy) NSString *  xxkey;
@property (nonatomic, assign) BOOL      is360Vr;  //360全景视频
@property (nonatomic, assign) BOOL      isLiveMedia; //是否为直播
@property (nonatomic, assign) BOOL      useAudioUnit;
@end

@interface LQMediaPlayerPreloadVideo : NSObject

@property (nonatomic, copy) NSString *vid;
@property (nonatomic, copy) NSString *path;
@property (nonatomic, copy) NSString *otherIdInfo;
@property (nonatomic, copy) NSString *site;
@property (nonatomic, assign) NSInteger defType;
@property (nonatomic, assign) NSInteger pos;
@property (nonatomic, assign) BOOL isCaptionVideo;
@property (nonatomic, assign) BOOL is360Vr;
@end
