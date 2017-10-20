package com.tencent.ai.sampleapp.util;

import java.io.File;

/**
 * Created by cassliu on 2017/10/7.
 */
public class FileUtil {

    /**
     * 检查目录是否为空
     *
     * @param folder
     * @return
     */
    public static boolean isDirectoryEmpty(File folder) {
        return !folder.exists() || !folder.isDirectory() || folder.list().length <= 0;
    }
}
