#!/bin/bash

rm "version"
rm -rf "LQMediaPlayerSDK.framework"
rm -rf "LQMediaPlayerSDK-dSYM"
rm -rf "LQMediaPlayerSDK-sim-dSYM"

cp "../../version" "./version"
cp -r "../LQMediaPlayerSDK.framework" "./LQMediaPlayerSDK.framework"
cp -r "../LQMediaPlayerSDK-dSYM" "./LQMediaPlayerSDK-dSYM"
cp -r "../LQMediaPlayerSDK-sim-dSYM" "./LQMediaPlayerSDK-sim-dSYM"

root_path="$(cd "$(dirname "$0")"; pwd)"
cd "$root_path"
echo "root_path: $root_path"

#git checkout master
#git reset --hard HEAD

sdk_version="$(head -1 version)"
git_author="$(git config user.name)"
git_email="$(git config user.email)"

echo "==> 当前版本号: $sdk_version"
echo "==> 当前版本号: $git_author"
echo "==> 当前版本号: $git_email"

echo "==> 生成podspec文件"
podspec_file_path="$root_path/LQMediaPlayerSDK.podspec"
echo "==> podspec_file_path: $podspec_file_path"

echo "Pod::Spec.new do |s|
    s.name = 'LQMediaPlayerSDK'
    s.version = '$sdk_version'
    s.license = 'Sina CopyRight'
    s.summary = '新浪视频云平台sdk'
    s.homepage = 'http://wiki.intra.sina.com.cn/pages/viewpage.action?pageId=105843426'
    s.author = { '$git_author' => '$git_email' }
    s.source = { :git => 'git@git.staff.sina.com.cn:sinaVideoPlatform/LQMediaPlayerSDK.git' , :tag => '$sdk_version'}
    s.platform = :ios, '8.0'
    s.preserve_paths      = 'LQMediaPlayerSDK.framework'
    s.public_header_files  = 'LQMediaPlayerSDK.framework/Headers/*.h'
    s.source_files  = 'LQMediaPlayerSDK.framework/Headers/*.h'
    s.vendored_frameworks  = 'LQMediaPlayerSDK.framework'
    s.libraries = 'stdc++'
    s.frameworks = 'AVFoundation','AudioToolbox','CoreMedia','AdSupport','QuartzCore','MediaPlayer','UIKit','Foundation','CoreGraphics'
end " > $podspec_file_path

echo "==> 代码上传gitlab"
git add .
git commit -m "auto publish : $sdk_version" --author="$git_author <$git_email>"
git push origin master
#
echo "==> 打tag"
git tag "$sdk_version"
git push origin "$sdk_version"
#
#echo "==> 上传podspec配置"
#export LANG=en_US.UTF-8
#/usr/local/bin/pod repo remove podspec
#/usr/local/bin/pod repo add podspec git@git.staff.sina.com.cn:sinaVideoPlatform/podspec.git
#/usr/local/bin/pod repo push podspec LQMediaPlayerSDK.podspec --allow-warnings --verbose

