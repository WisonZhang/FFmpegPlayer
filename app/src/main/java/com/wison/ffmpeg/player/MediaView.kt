package com.wison.ffmpeg.player

import android.content.Context
import android.graphics.Color
import android.graphics.SurfaceTexture
import android.os.Handler
import android.os.Looper
import android.util.AttributeSet
import android.view.Surface
import android.view.SurfaceView
import android.view.TextureView
import android.widget.FrameLayout
import android.widget.RelativeLayout

/**
 * Created by Wison on 2022/7/3.
 */
class MediaView: RelativeLayout, TextureView.SurfaceTextureListener {

    companion object {
        init {
            System.loadLibrary("player_engine")
        }
    }

    private val mTextureView = MediaTextureView(context)
    private val mSurfaceView = MediaSurfaceView(context)
    private val mListener = PlayerListenerImpl(this)
    private var mPath: String? = null
    private var mSurface: Surface? = null
    private var mPlayerPtr: Long = 0

    constructor(context: Context) : super(context)

    constructor(context: Context, attrs: AttributeSet?) : super(context, attrs)

    constructor(context: Context, attrs: AttributeSet?, defStyleAttr: Int) : super(context, attrs, defStyleAttr)

    init {
        setBackgroundColor(Color.BLACK)
        val lp = LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT)
        lp.addRule(CENTER_IN_PARENT, TRUE)

//        addView(mTextureView, lp)
        addView(mSurfaceView, lp)
//        mTextureView.surfaceTextureListener = this
    }

    fun setPath(path: String?) {
        mPath = path
    }

    fun setVideoSize(videoWidth: Int, videoHeight: Int) {
        mTextureView.setVideoSize(videoWidth, videoHeight)
        mSurfaceView.setVideoSize(videoWidth, videoHeight)
    }

    fun play() {
        mSurface = mSurfaceView.holder.surface
        mPath ?: return
        mSurface ?: return
        mPlayerPtr = playVideo(mPath!!, mSurface!!)
    }

    fun stop() {
        stopVideo(mPlayerPtr)
    }

    override fun onSurfaceTextureAvailable(surface: SurfaceTexture, width: Int, height: Int) {
        if (mSurface == null) {
            mSurface = Surface(surface)
        }
    }

    override fun onSurfaceTextureDestroyed(surface: SurfaceTexture): Boolean {
        mSurface = null
        return false
    }

    override fun onSurfaceTextureSizeChanged(surface: SurfaceTexture, width: Int, height: Int) {}

    override fun onSurfaceTextureUpdated(surface: SurfaceTexture) {}

    private external fun playVideo(path: String, surface: Surface): Long

    private external fun stopVideo(player: Long)

}