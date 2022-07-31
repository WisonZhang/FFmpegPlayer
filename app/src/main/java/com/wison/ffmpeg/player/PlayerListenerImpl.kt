package com.wison.ffmpeg.player

import android.os.Handler
import android.os.Looper

/**
 * Created by ZhangWeiRong on 2022/7/6.
 */
class PlayerListenerImpl(private val mMediaView: MediaView): IPlayListener {

    private val mMainHandler = Handler(Looper.getMainLooper())

    override fun onVideoSize(videoWidth: Int, videoHeight: Int) {
        mMainHandler.post {
            mMediaView.setVideoSize(videoWidth, videoHeight)
        }
    }

}