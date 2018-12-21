//
//  LQMediaCache.h
//  LQMediaPlayer
//
//  Created by yingnan3 on 2018/9/26.
//  Copyright © 2018年 sina. All rights reserved.
//

#ifndef LQMediaCache_h
#define LQMediaCache_h
#import <Foundation/Foundation.h>


@class LQMediaCache;

@interface LQMediaCache : NSObject

/**
 @abstract cache 启动方法
 @param path cache存储目录
 @param size cache最大的存储空间（单位 M Byte）
 @discussion 可以不设置，默认路径，默认申请200M存储空间。
 @return YES:成功；NO：失败
 */
+ (BOOL)setCacheFilePath:(NSString *) path maxSize:(int)size;

/**
 @abstract cache预加载方法
 @param url 原始播放地址
 @param h265Url 原始h265播放地址
 @param vid 视频唯一标示
 @discussion 可以提前加载视频源，在prepare的时候可以大幅加速首帧渲染
 @return YES:成功；NO：失败
 */
+ (BOOL)addDownloadUrl:(NSString*)url h265Url:(NSString*)h265Url vid:(NSString*) vid;

/**
 @abstract 获取cahce 后的url
 @param url 原始播放地址
 @param h265Url 原始h265播放地址
 @param vid 视频唯一标示
 @discussion cache成功下载，可以获取到cache之后的加速播放url
 @return cache后的url，如cache失败，则为原始url
 */
+ (NSString*)getCacheUrl:(NSString*)url h265Url:(NSString*)h265Url vid:(NSString*) vid;

/**
 @abstract 清除方法
 @return YES:成功；NO：失败
 */
+ (BOOL)clearCache;

/**
 @abstract 获取cache磁盘占用
 @return 当前Cache占用的磁盘大小，单位M
 */
+ (float)currentCacheSize;

/**
 @abstract 将视频加入到cache中
 @param absolutePath 源视频绝对路径
 @param vid 视频唯一标示
 @discussion 可以将本地视频加到cache中，当播放时可以避免重新下载，冷启动之后全部清除
 @return YES:成功；NO：失败
 */
+ (BOOL)addFileToCache:(NSString*)absolutePath vid:(NSString*) vid;

/**
 @abstract 删除指定vid的本地cache
 @param vid 视频唯一标示
 @discussion 删除通过addFileToCache 方法添加到本地的cache视频，可以有效的减少本地cache占用
 */
+ (void)removeCacheByVid:(NSString *)vid;
@end
#endif /* LQMediaCache_h */
