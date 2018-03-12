#!/bin/sh
# compress application.
/bin/rm -rf $CONFIGURATION_BUILD_DIR/Payload

/bin/ls $CONFIGURATION_BUILD_DIR

/bin/mkdir $CONFIGURATION_BUILD_DIR/Payload

/bin/cp -R $CONFIGURATION_BUILD_DIR/AISDKDemo.app $CONFIGURATION_BUILD_DIR/Payload

/bin/cp iTunesArtwork/iTunesArtwork.png $CONFIGURATION_BUILD_DIR/iTunesArtwork

cd $CONFIGURATION_BUILD_DIR

# zip up the application directory

/usr/bin/zip -r AISDKDemo.ipa Payload iTunesArtwork

# 备份符号表
#echo "Backup the .dSYM ..."

#/usr/bin/zip -r AISDKDemo.ipa.dSYM.zip  AISDKDemo.app.dSYM

/bin/ls $CONFIGURATION_BUILD_DIR

#cat $CONFIGURATION_BUILD_DIR

echo "Copy the .ipa to dir out/ ..."

# 将ipa文件copy到根目录下的result目录
/bin/rm -rf $SRCROOT/out

/bin/mkdir $SRCROOT/out

cp $CONFIGURATION_BUILD_DIR/AISDKDemo.ipa  $SRCROOT/out/AISDKDemo.ipa

echo "Clean the build dir ..."

/bin/rm -rf Payload

/bin/rm -rf iTunesArtwork

echo "Packet .ipa done."
