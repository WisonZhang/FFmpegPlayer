package com.wison.ffmpeg.player

import android.content.Context
import android.util.AttributeSet
import android.view.SurfaceView

/**
 * Created by ZhangWeiRong on 2022/7/30.
 */
class MediaSurfaceView: SurfaceView {

    private var mVideoWidth = 0
    private var mVideoHeight = 0

    constructor(context: Context?) : super(context)

    constructor(context: Context?, attrs: AttributeSet?) : super(context, attrs)

    constructor(context: Context?, attrs: AttributeSet?, defStyleAttr: Int) : super(context, attrs, defStyleAttr)

    override fun onMeasure(widthMeasureSpec: Int, heightMeasureSpec: Int) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec)

        val width = MeasureSpec.getSize(widthMeasureSpec)
        val height = MeasureSpec.getSize(heightMeasureSpec)

        if (mVideoWidth == 0 || mVideoHeight == 0) {
            setMeasuredDimension(width, height)
            return
        }

        val renderWidth: Int
        val renderHeight: Int
        if (mVideoWidth > mVideoHeight) {
            renderWidth = width
            renderHeight = width * mVideoHeight / mVideoWidth
        } else {
            renderWidth = height * mVideoWidth / mVideoHeight
            renderHeight = height
        }

        setMeasuredDimension(renderWidth, renderHeight)
    }

    fun setVideoSize(videoWidth: Int, videoHeight: Int) {
        mVideoWidth = videoWidth
        mVideoHeight = videoHeight
        requestLayout()
    }

}