Pod::Spec.new do |s|
    s.name = 'LQMediaPlayerSDK'
    s.version = '1.0.1'
    s.license = 'Sina CopyRight'
    s.summary = '新浪视频云平台sdk'
    s.homepage = 'http://wiki.intra.sina.com.cn/pages/viewpage.action?pageId=105843426'
    s.author = { 'haodong1' => 'haodong1@staff.sin.com.cn' }
    s.source = { :git => 'git@github.com:weihanyumo/testPod.git' , :tag => '1.0.1'}
    s.platform = :ios, '8.0'
    s.preserve_paths      = 'LQMediaPlayerSDK.framework'
    s.public_header_files  = 'LQMediaPlayerSDK.framework/Headers/*.h'
    s.source_files  = 'LQMediaPlayerSDK.framework/Headers/*.h'
    s.vendored_frameworks  = 'LQMediaPlayerSDK.framework'
    s.libraries = 'stdc++'
    s.frameworks = 'AVFoundation','AudioToolbox','CoreMedia','AdSupport','QuartzCore','MediaPlayer','UIKit','Foundation','CoreGraphics'
end 
