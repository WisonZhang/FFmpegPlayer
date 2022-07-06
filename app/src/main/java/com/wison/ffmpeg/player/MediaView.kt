package com.wison.ffmpeg.player

import android.content.Context
import android.graphics.SurfaceTexture
import android.util.AttributeSet
import android.view.Surface
import android.view.TextureView
import android.widget.FrameLayout

/**
 * Created by ZhangWeiRong on 2022/7/3.
 */
class MediaView: FrameLayout, TextureView.SurfaceTextureListener {

    companion object {
        init {
            System.loadLibrary("player_core")
        }
    }

    private val mTextureView = TextureView(context)
    private var mPath: String? = null
    private var mSurface: Surface? = null

    constructor(context: Context) : super(context)

    constructor(context: Context, attrs: AttributeSet?) : super(context, attrs)

    constructor(context: Context, attrs: AttributeSet?, defStyleAttr: Int) : super(context, attrs, defStyleAttr)

    init {
        addView(mTextureView, LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT)
        mTextureView.surfaceTextureListener = this
    }

    fun setPath(path: String?) {
        mPath = path
    }

    fun play() {
        mPath ?: return
        mSurface ?: return
        playVideo(mPath!!, mSurface!!)
    }

    override fun onSurfaceTextureAvailable(surface: SurfaceTexture, width: Int, height: Int) {
        if (mSurface == null) {
            mSurface = Surface(surface)
        }
    }

    override fun onSurfaceTextureSizeChanged(surface: SurfaceTexture, width: Int, height: Int) {

    }

    override fun onSurfaceTextureDestroyed(surface: SurfaceTexture): Boolean {
        mSurface = null
        return false
    }

    override fun onSurfaceTextureUpdated(surface: SurfaceTexture) {

    }

    private external fun playVideo(path: String, surface: Surface)

}