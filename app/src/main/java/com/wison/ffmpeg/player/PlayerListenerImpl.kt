package com.wison.ffmpeg.player

import android.os.Handler
import android.os.Looper
import android.util.Log

/**
 * Created by ZhangWeiRong on 2022/7/6.
 */
class PlayerListenerImpl(private val mMediaView: MediaView): IPlayListener {

    private val mMainHandler = Handler(Looper.getMainLooper())

    override fun onVideoSize(videoWidth: Int, videoHeight: Int) {
        mMainHandler.post {
            Log.i("wison", "videoWidth: $videoWidth; videoHeight: $videoHeight")
            mMediaView.setVideoSize(videoWidth, videoHeight)
        }
    }

}