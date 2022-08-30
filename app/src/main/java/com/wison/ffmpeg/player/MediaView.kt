package com.wison.ffmpeg.player

import android.content.Context
import android.graphics.Color
import android.graphics.SurfaceTexture
import android.media.AudioAttributes
import android.media.AudioFormat
import android.media.AudioManager
import android.media.AudioTrack
import android.os.Handler
import android.os.Looper
import android.util.AttributeSet
import android.util.Log
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

    private var mAudioTrack: AudioTrack? = null

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

    private fun initAudioTrack() {
        val attr = AudioAttributes.Builder()
            .setUsage(AudioAttributes.USAGE_MEDIA)
            .setContentType(AudioAttributes.CONTENT_TYPE_MUSIC)
            .build()
        val format = AudioFormat.Builder()
            .setSampleRate(44100)
            .setChannelMask(AudioFormat.CHANNEL_OUT_STEREO)
            .setEncoding(AudioFormat.ENCODING_PCM_16BIT)
            .build()
        val bufferSize = AudioTrack.getMinBufferSize(44100, AudioFormat.CHANNEL_OUT_STEREO, AudioFormat.ENCODING_PCM_16BIT)
        mAudioTrack = AudioTrack(attr, format, bufferSize, AudioTrack.MODE_STREAM, AudioManager.AUDIO_SESSION_ID_GENERATE)
    }

    private fun audioTrackPlay(buffer: ByteArray, length: Int) {
        mAudioTrack?.play()
        mAudioTrack?.write(buffer, 0, length)
    }

    private fun stopAudioTrack() {
        mAudioTrack?.stop()
        mAudioTrack?.release()
    }

    private external fun playVideo(path: String, surface: Surface): Long

    private external fun stopVideo(player: Long)

}