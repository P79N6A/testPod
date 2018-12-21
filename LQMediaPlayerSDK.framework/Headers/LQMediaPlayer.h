//
//  LQMediaPlayer.h
//  LQMediaPlayer
//
//  Created by suzhou on 2018/8/13.
//  Copyright © 2018年 sina. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayer.h>
#import "LQMediaPlayerItem.h"
#import "LQMediaCache.h"

typedef enum {
    LQMediaPlayerItemServiceTypeDefault = 1,
    LQMediaPlayerItemServiceTypeNoServer = 2
}LQMediaPlayerItemServiceType;

typedef enum {
    LQ_MEDIA_PLAYER_ERROR_OPEN = 0,
    LQ_MEDIA_PLAYER_ERROR_UNREACH_NETWORK,
    LQ_MEDIA_PLAYER_ERROR_PLAY
}LQMediaErrorType;

typedef enum {
    LQMediaPlayerMovieScalingModeNone,       // No scaling
    LQMediaPlayerMovieScalingModeAspectFit,  // Uniform scale until one dimension fits
    LQMediaPlayerMovieScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    LQMediaPlayerMovieScalingModeFill        // Non-uniform scale. Both render dimensions will exactly match the visible bounds
}LQMediaPlayerMovieScalingMode;

typedef enum {
    LQ_MEDIA_PLAYER_STATE_IDLE = 0,
    LQ_MEDIA_PLAYER_STATE_INITIALIZED,            // initPlayer
    LQ_MEDIA_PLAYER_STATE_OPENING,                // item load
    LQ_MEDIA_PLAYER_STATE_OPENED,                 // item load finished
    LQ_MEDIA_PLAYER_STATE_SEEKING,                // seeking gap 0.2ms
    LQ_MEDIA_PLAYER_STATE_BUFFERING,              // loading
    LQ_MEDIA_PLAYER_STATE_PAUSED = 6,
    LQ_MEDIA_PLAYER_STATE_PLAY_WAIT,              // prepared
    LQ_MEDIA_PLAYER_STATE_PLAYING,
    LQ_MEDIA_PLAYER_STATE_PLAY_COMPLETE,
    LQ_MEDIA_PLAYER_STATE_CLOSING = 10,                 //10
    LQ_MEDIA_PLAYER_STATE_CLOSED,                 // stop
    LQ_MEDIA_PLAYER_STATE_REOPEN,
    //    LQ_MEDIA_PLAYER_STATE_PREOPEN,                //to protect clear cache files ok
    LQ_MEDIA_PLAYER_STATE_END
}LQMediaPlayerState;

typedef enum {
    LQMediaPlayerRotationNone,          // No rotation
    LQMediaPlayerRotationUpsideDown,
    LQMediaPlayerRotationLeft,
    LQMediaPlayerRotationRight,
}LQMediaPlayerRotationMode;

@class LQMediaPlayer;

@protocol LQMediaPlayerDelegate <NSObject>

@optional

//视频开始播放
- (void)onStatusPlaying:(LQMediaPlayer*)mediaPlayer;

//视频状体变成暂停
- (void)onStatusPaused:(LQMediaPlayer*)mediaPlayer;

//通知可以播放此视频
- (void)onOpenSucess:(LQMediaPlayer*)mediaPlayer;

//播放出错
- (void)onErrorReport:(LQMediaPlayer*)mediaPlayer code:(LQMediaErrorType)code arg:(void *)arg;

//播放准备完毕，可以直接调用play开始播放
- (void)onPrepared:(LQMediaPlayer*)mediaPlayer;

//通知视频时长
//- (void)onUpdateDuration:(LQMediaPlayer*)mediaPlayer duration:(long long)duration;

//当前播放进度通知，仅播放状态时有效
- (void)onUpdatePosition:(LQMediaPlayer*)mediaPlayer position:(long long)position;

//开始缓冲
- (void)onBufferingStart:(LQMediaPlayer*)mediaPlayer;

//缓冲进度
- (void)onBufferingUpdate:(LQMediaPlayer*)mediaPlayer percent:(long)percent;

//缓冲完毕
- (void)onBufferingOk:(LQMediaPlayer*)mediaPlayer;

//播放完毕
- (void)onComplete:(LQMediaPlayer*)mediaPlayer;

//通知seeking状态
- (void)onSeekingForward:(LQMediaPlayer*)mediaPlayer;

//通知seeking状态
- (void)onSeekingBackward:(LQMediaPlayer*)mediaPlayer;

//KPI相关埋点的回调
- (void)onMsgReport:(LQMediaPlayer*)mediaPlayer tag:(NSString*)tag qosMessage:(NSDictionary*)msg;

//VLOG问题查找日志相关的回调 tag:VLOG
- (void)onVLogReport:(LQMediaPlayer*)mediaPlayer tag:(NSString*)tag qosMessage:(NSDictionary*)msg;

//ELOG代码级别错误日志回调 tag:ELOG
- (void)onELogReport:(LQMediaPlayer*)mediaPlayer tag:(NSString*)tag qosMessage:(NSDictionary*)msg;

//极路由清晰度回调
- (void)onRouterQuality:(LQMediaPlayer*)mediaPlayer quality:(NSInteger)quality;

//AirPlay状态回调
- (void)onAirPlayActiveDidChange:(LQMediaPlayer*)mediaPlayer info:(NSInteger)info;

//通知视频宽高
- (void)onVideoSizeChanged:(LQMediaPlayer*)mediaPlayer videoSize:(CGSize)size;

//首帧画面渲染通知
- (void)onFirstFrameRender:(LQMediaPlayer*)mediaPlayer;

//通知播放器类型切换，ios未使用
//- (void)onDecodeTypeChange:(LQMediaPlayer*)mediaPlayer toType:(long)type;

//通知播放器类型统计上报，ios未使用
//- (void)onDecoderStatusReport:(LQMediaPlayer*)mediaPlayer bitFlag:(long)bitFlag info:(NSString *)info;

//仅开发测试使用
- (void)onShowPlayerMessage:(LQMediaPlayer*)mediaPlayer message:(NSString *)info;

//转码回调
- (void)OnTranscodeComplete:(LQMediaPlayer*)mediaPlayer;

- (void)OnTranscodeFail:(LQMediaPlayer*)mediaPlayer;

- (void)OnTranscodeProgress:(LQMediaPlayer*)mediaPlayer progress:(float)progress;

@end

@interface LQMediaPlayer : NSObject

/**
 @abstract 暂时未开放
 */
@property (nonatomic, readonly, assign) LQMediaPlayerItemServiceType serviceType;
/**
 @abstract 播放器消息代理
 */
@property (nonatomic, weak)     id<LQMediaPlayerDelegate>   delegate;
/**
 @abstract 播放器参数
 */
@property (nonatomic, retain)   LQMediaPlayerItem *         playerItem;
/**
 @abstract 播放器渲染的view，init之后获取
 */
@property (nonatomic, readonly) UIView*                     view;
/**
 @abstract 设置播放器图像适配模式
 */
@property (nonatomic, assign)   LQMediaPlayerMovieScalingMode   scalingMode;
/**
 @abstract 播放器当前状态
 */
@property (nonatomic, readonly) LQMediaPlayerState          playbackState;

/**
 @abstract 音量设置
 @discussion 范围0-16; 8=正常音量; 
 */
@property (nonatomic, assign)   long    volume;

/**
 @abstract 是否显示qos调试界面
 */
@property (nonatomic, assign)   BOOL    showQosDebugView;
/**
 @abstract 是否自动模式，默认=YES
 */
@property (nonatomic, assign)   BOOL    isAutoMode;

/**
 @abstract 视频渲染区旋转动画时长/单位 s
 @discussion default 0.3f
 */
@property (nonatomic, assign)   CGFloat   rotationDuration;

/**
 @abstract 视频渲染区旋转
 @discussion 相对于Player 的view做旋转，切换视频源之后旋转参数保留
 */
@property (nonatomic, assign)   LQMediaPlayerRotationMode   rotationMode;

/**
 @abstract 获取播放器当前版本
 @discussion 获取播放器当前版本
 @since Available in LQMediaPlayer 1.0.1 and later.
 */
+ (NSString*)getVersion;

#pragma mark - Player Controll

/**
 @abstract 设置播放信息
 @param item 当前播放器播放参数
 @discussion 必须要设置在prepareAsync和play方法之前，否则播放无效
 @see LQMediaPlayerItem
 */
- (void)setDataSource:(LQMediaPlayerItem *)item;

/**
 @abstract 预加载播放器
 @discussion 提前准备播放，可能加速首帧播放,必须要在setDataSource方法之后
 */
- (BOOL)prepareAsync;

/**
 @abstract 获取当前视频源长度
 @discussion 单位 ms
 */
- (long long)getDuration;

/**
 @abstract 获取当前视频播放进度
 @discussion 单位 ms
 */
- (long long)getPlayPostion;

/**
 @abstract 播放
 @discussion 开始播放，必须要在setDataSource方法之后
    *播放状态可以是 pause或者stop
 */
- (BOOL)play;

/**
 @abstract 暂停
 @discussion 暂停播放
 */
- (BOOL)pause;

/**
 @abstract 停止
 @discussion 停止播放器，之后可以销毁
 */
- (BOOL)stop;

/**
 @abstract seek
 @param msec 指定播放起始时间，单位 ms
 @discussion 从指定位置开始播放
 */
- (BOOL)seekTo:(long)msec;

/**
 @abstract 获取视屏尺寸
 @discussion 在开始播放之后有效
 */
- (CGSize)getVideoSize;

/**
 @abstract 重新加载播放器
 @discussion 在开始播放之后有效
 */
- (void)resetPlayer;

/**
 @abstract 重置视频渲染区
 @discussion 用背景色重新填充视频渲染区
 */
- (void)resetVideoRenderView;

/**
 @abstract 获取当前视频下载速度
 @discussion 在开始播放之后有效
 */
- (long)getDownloadSpeed;

/**
 @abstract 获取视频已经缓存的文件时长
 @discussion prepare之后有效
 */
- (long long)getCacheDuration;

-(NSString *)getPlayerStatusReport;

- (void)appDidBecomeActiveWillPlayNewVideo;

- (void)setPictureInPicturePlayback:(BOOL)enable;

#pragma mark - Quality monitoring

- (long)getAudioBytesPerSecond;

- (long)getVideoBytesPerSecond;

- (long)getMovieBitrate;

- (long)getBufferLength;

- (long)getVideoFrameRate;

/**
 @abstract 截图
 @param path 图片存储路径
 */
- (void)takeSnapShotToJPG:(NSString *)path;

/**
 @abstract 设置最大缓存空间
 @param size 视频缓存buffer大小
 @param time 视频缓存时间长度 单位 ms
 @param ptime 最大预加载视频时间长度 单位 ms
 @param path 缓存目录位置，绝对路径
 @param ua ?
 @discussion 从指定位置开始播放，暂时无效
 */
- (void)setMaxCacheSpace:(long)size
            maxCacheTime:(long)time
          maxPreloadTime:(long)ptime
          cacheDirectory:(NSString *)path
               userAgent:(NSString *)ua __attribute__((deprecated("方法未启用")));

/**
 @abstract 添加预加载的视频
 @param items 预加载视频对象列表
 @discussion 预加载视频功能可以设置提前解析视频源，可能加快视频打开速度， 暂时无效
 @see LQMediaPlayerPreloadVideo
 */
- (BOOL)addPreloadVideoItems:(NSArray<LQMediaPlayerPreloadVideo*> *)items __attribute__((deprecated("方法未启用")));

/**
 @abstract 指定视频源是否在预加载列表
 @param item 预加载视频对象
 @discussion 如果
 @return YES:在预加载列表；NO：未开始预加载
 @see addPreloadVideoItems
 */
- (BOOL)isCacheVideo:(LQMediaPlayerItem *)item __attribute__((deprecated("方法未启用")));

#pragma mark - Transcode About
/**
 @abstract 转码接口
 */
- (void)startTransCodeByPath:(NSString *)v_strVideoPath andSavePath:(NSString *)v_strSavePath __attribute__((deprecated("方法未启用")));

- (void)cancelTransCode __attribute__((deprecated("方法未启用")));

- (void)startSoftTransCodeByPath:(NSString *)v_strVideoPath andSavePath:(NSString *)v_strSavePath __attribute__((deprecated("方法未启用")));

- (void)cancelSoftTransCode __attribute__((deprecated("方法未启用")));

- (void)setTransCodeScaleW:(long)width H:(long)height __attribute__((deprecated("方法未启用")));

- (void)setTransCodeCropW:(long)width H:(long)height __attribute__((deprecated("方法未启用")));

- (void)setTransCodeRotateF:(long)f __attribute__((deprecated("方法未启用")));

@end


