#!/bin/bash
folder="./translations"
if [ ! -d  $folder ]; then
    mkdir $folder
fi

lupdate ./app -ts -no-obsolete ./$folder/dde-widgets_zh_CN.ts
lupdate ./notification -ts -no-obsolete ./$folder/dde-widgets-notification_zh_CN.ts
lupdate ./memorymonitor -ts -no-obsolete ./$folder/dde-widgets-memorymonitor_zh_CN.ts
lupdate ./worldclock -ts -no-obsolete ./$folder/dde-widgets-worldclock_zh_CN.ts
#tx push -s -b m20
